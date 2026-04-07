#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * zombie_demo.c
 *
 * 목적:
 *  - 자식이 먼저 종료되었는데 부모가 wait()를 늦게 호출하면
 *    잠시 zombie 상태가 생길 수 있음을 관찰
 *  - wait()가 단순한 "기다림"이 아니라 종료 상태 회수(reaping)라는 점 이해
 *
 * 관찰 팁:
 *  - 프로그램 실행 직후 다른 터미널에서 아래 명령 사용
 *      ps -o pid,ppid,state,cmd | grep zombie_demo
 *      ps -el | grep Z
 */

int main(void) {
    setbuf(stdout, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("[child ] PID=%d exiting immediately\n", getpid());
        exit(42);
    }
    else {
        int status = 0;

        printf("[parent] PID=%d, child PID=%d\n", getpid(), pid);
        printf("[parent] sleeping before wait() to create a zombie window...\n");

        /*
         * 이 시간 동안 자식은 이미 종료되었지만,
         * 부모가 아직 wait()를 호출하지 않았으므로 zombie 상태가 잠시 보일 수 있음.
         */
        sleep(15);

        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("[parent] child reaped, exit status=%d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}