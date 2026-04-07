#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * fork_exec_wait_demo.c
 *
 * 목적:
 *  - fork()로 자식을 만든 뒤
 *  - 자식이 exec 계열 함수로 다른 프로그램으로 "갈아끼워지는" 흐름을 확인
 *  - 부모는 waitpid()로 자식 종료를 기다리고 exit status를 회수
 *
 * 사용법:
 *  1) 인자 없이 실행 -> 기본적으로 ls -l 실행
 *     ./fork_exec_wait_demo
 *
 *  2) 인자를 주면 해당 명령 실행
 *     ./fork_exec_wait_demo /bin/echo hello
 *     ./fork_exec_wait_demo /usr/bin/whoami
 */

static void print_wait_status(int status) {
    if (WIFEXITED(status)) {
        printf("[parent] child exited normally, exit status = %d\n",
               WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        printf("[parent] child killed by signal %d\n", WTERMSIG(status));
    }
    else if (WIFSTOPPED(status)) {
        printf("[parent] child stopped by signal %d\n", WSTOPSIG(status));
    }
    else {
        printf("[parent] child ended in an unhandled state\n");
    }
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        /*
         * 자식 프로세스:
         * 아직은 부모를 복제한 같은 프로그램을 실행 중인 상태.
         * 이제 exec 계열 함수를 호출하면 현재 프로세스의 메모리 이미지가
         * 다른 프로그램으로 교체됨.
         */
        printf("[child ] before exec: PID=%d, PPID=%d\n", getpid(), getppid());

        if (argc >= 2) {
            /*
             * argv[1]부터를 새로운 프로그램의 argv로 사용.
             * 예: ./fork_exec_wait_demo /bin/echo hello
             */
            execvp(argv[1], &argv[1]);
        }
        else {
            /* 기본 동작: 현재 디렉터리 목록 보기 */
            execlp("ls", "ls", "-l", NULL);
        }

        /*
         * exec 계열 함수가 성공하면 이 아래 코드는 실행되지 않음.
         * 여기까지 왔다면 exec가 실패한 것.
         */
        perror("exec failed");
        exit(127);
    }
    else {
        int status = 0;
        pid_t waited_pid;

        printf("[parent] PID=%d created child PID=%d\n", getpid(), pid);
        printf("[parent] waiting for child termination...\n");

        waited_pid = waitpid(pid, &status, 0);
        if (waited_pid < 0) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        printf("[parent] waitpid returned PID=%d\n", waited_pid);
        print_wait_status(status);
        printf("[parent] parent resumes after child completion\n");
    }

    return 0;
}