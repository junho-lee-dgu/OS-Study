/*
- "순수 I/O-bound"를 lab 수준에서 만들기는 환경 차이가 있어서 어려움
- WSL2, cache, filesystem buffering 때문에 결과가 변동성이 있을 수 있음

-> 짧은 계산 + 반복 파일 쓰기 + 주기적 동기화를 섞어서 CPU를 오래 붙잡기 보다
자주 커널 I/O 경로로 들어가게 하는 형태로 만듦

왜?
순수 디스크 I/O만 하는 이상적 예제를 만들 수 없음
- 계산 짧고 
- 자주 write() 호출하고 
- fsync()로 커널/저장장치 경로를 더 타게 하고 
- usleep()으로 waiting 성격도 일부 드러나게 함
-> 훨씬 "기다림이 많은 프로세스"에 가깝게 만듦
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
    pid_t pid = getpid();
    int fd = open("assets/io_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    printf("[io_bound] PID = %d\n", pid);
    printf("[io_bound] Starting write-heavy workload...\n");

    char buffer[256];
    for (int i = 0; i < 20000; i++) {
        int len = snprintf(buffer, sizeof(buffer), "line %d from pid %d\n", i, pid);
        if (write(fd, buffer, len) < 0) {
            perror("write failed");
            close(fd);
            return 1;
        }

        if (i % 200 == 0) {
            fsync(fd);      // 디스크 반영 요구
            usleep(2000);   // 잠깐 대기
        }
    }

    close(fd);
    printf("[io_bound] Done.\n");
    return 0;
}