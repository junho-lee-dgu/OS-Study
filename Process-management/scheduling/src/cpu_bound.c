/*
왜 CPU-bound인가?
- 거의 전부가 계산
- 디스크를 기다리지도 않고, 네트워크를 기다리지도 않음
- 즉 CPU burst 긺
*/

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    volatile unsigned long long sum = 0;
    pid_t pid = getpid();

    printf("[cpu_bound] PID = %d\n", pid);
    printf("[cpu_bound] Starting heavy computation...\n");

    for (unsigned long long i = 0; i < 800000000ULL; i++) {
        sum += (i % 7) * (i % 13);
    }

    printf("[cpu_bound] Done. sum = %llu\n", sum);
    return 0;
}