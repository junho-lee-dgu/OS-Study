#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * fork_demo.c
 *
 * 목적:
 *  - fork()가 "새 프로그램 실행"이 아니라
 *    "현재 프로세스를 복제하여 새 프로세스를 만드는 것"임을 확인
 *  - 부모/자식의 PID, PPID, fork() 반환값 차이를 관찰
 *  - 같은 코드가 왜 두 번 흐르는지 체감
 */

int main(void) {
    setbuf(stdout, NULL);

    printf("=== fork_demo: before fork ===\n");
    printf("[before fork] current PID = %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        /* 자식 프로세스 영역 */
        printf("[child ] PID=%d, PPID=%d, fork return=%d\n",
               getpid(), getppid(), pid);

        usleep(100000);  /* 출력 순서 차이를 보기 위한 짧은 지연 */
        printf("[child ] after fork: same source line, different process\n");
    }
    else {
        /* 부모 프로세스 영역 */
        printf("[parent] PID=%d, child PID=%d, fork return=%d\n",
               getpid(), pid, pid);
        printf("[parent] after fork: parent continues concurrently\n");
    }

    /* 부모/자식 모두 도달 가능한 공통 코드 */
    printf("[common ] this line is printed by PID=%d\n", getpid());

    if (pid > 0) {
        /*
         * 실습 출력이 셸 프롬프트와 섞이지 않도록 부모가 마지막에 자식을 정리.
         * 핵심은 fork 관찰이고, 여기의 wait는 출력 정리용 + 자원 회수용 보조 장치.
         */
        wait(NULL);
    }

    return 0;
}
