#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * proc_tree_demo.c
 *
 * 목적:
 *  - 부모가 여러 자식을 만드는 구조를 관찰
 *  - 일부 자식이 다시 자식을 만들어 "process tree" 느낌을 더 분명하게 확인
 *  - pstree -p, ps -f 등으로 부모-자식 관계를 직접 관찰
 *
 * 관찰 팁:
 *  - 이 프로그램을 실행한 뒤 다른 터미널에서 pstree -p 또는 ps -f 명령 사용
 *  - sleep()을 넣어 두었기 때문에 관찰할 시간이 확보됨
 */

int main(void) {
    setbuf(stdout, NULL);

    printf("[root  ] parent PID=%d\n", getpid());

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            /* 각 child 프로세스가 들어오는 영역 */
            printf("[child %d] PID=%d, PPID=%d created\n", i + 1, getpid(), getppid());

            /*
             * 두 번째 child는 grandchild를 하나 더 생성하여
             * 단순 형제 관계뿐 아니라 트리 깊이도 관찰할 수 있게 함.
             */
            if (i == 1) {
                pid_t gpid = fork();

                if (gpid < 0) {
                    perror("grandchild fork failed");
                    exit(EXIT_FAILURE);
                }
                else if (gpid == 0) {
                    printf("[grand ] PID=%d, PPID=%d created by child 2\n",
                           getpid(), getppid());
                    sleep(8);
                    printf("[grand ] PID=%d exiting\n", getpid());
                    exit(21);
                }
                else {
                    int gstatus = 0;
                    printf("[child 2] created grandchild PID=%d\n", gpid);
                    sleep(10);
                    waitpid(gpid, &gstatus, 0);
                    printf("[child 2] reaped grandchild PID=%d, exit=%d\n",
                           gpid,
                           WIFEXITED(gstatus) ? WEXITSTATUS(gstatus) : -1);
                    exit(12);
                }
            }

            /* child 1, child 3은 잠시 살아 있으면서 관찰 대상이 됨 */
            sleep(10 + i);
            printf("[child %d] PID=%d exiting\n", i + 1, getpid());
            exit(10 + i);
        }
    }

    /*
     * 부모 프로세스는 자신의 직계 자식 3개를 회수한다.
     * grandchild는 그 부모(child 2)가 회수한다.
     */
    for (int count = 0; count < 3; count++) {
        int status = 0;
        pid_t wpid = wait(&status);

        if (wpid < 0) {
            perror("wait failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("[root  ] reaped child PID=%d, exit=%d\n",
                   wpid, WEXITSTATUS(status));
        }
        else {
            printf("[root  ] child PID=%d ended abnormally\n", wpid);
        }
    }

    printf("[root  ] all direct children have been reaped\n");
    return 0;
}
