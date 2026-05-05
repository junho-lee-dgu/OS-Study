#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];                  // fd[0]: read end, fd[1]: write end
    pid_t pid;
    const char *msg = "Hello from parent through pipe!";

    // 1) pipe 생성
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // 2) 자식 생성
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    // 3) 자식 프로세스
    if (pid == 0) {
        char buffer[128];

        // 자식은 읽기만 할 것이므로 write end 닫기
        close(fd[1]);

        printf("[child ] PID=%d, PPID=%d\n", getpid(), getppid());
        printf("[child ] waiting to read from pipe...\n");

        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n < 0) {
            perror("read failed");
            close(fd[0]);
            exit(1);
        }

        buffer[n] = '\0';
        printf("[child ] received message: %s\n", buffer);

        close(fd[0]);
        exit(0);
    }

    // 4) 부모 프로세스
    else {
        // 부모는 쓰기만 할 것이므로 read end 닫기
        close(fd[0]);

        printf("[parent] PID=%d, child PID=%d\n", getpid(), pid);
        printf("[parent] writing message into pipe...\n");
        sleep(3); //blocking read

        ssize_t n = write(fd[1], msg, strlen(msg));
        if (n < 0) {
            perror("write failed");
            close(fd[1]);
            exit(1);
        }

        printf("[parent] wrote %zd bytes\n", n);

        close(fd[1]);   // 다 썼으면 닫기

        wait(NULL);     // 자식 종료 회수
        printf("[parent] child completed\n");
    }

    return 0;
}