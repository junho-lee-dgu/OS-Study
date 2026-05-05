#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

typedef struct {
    int counter;
    char message[128];
} shared_data;

int main(void) {
    shared_data *data = mmap(NULL, sizeof(shared_data),
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS,
                             -1, 0);

    if (data == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    data->counter = 0;
    strcpy(data->message, "Initial message");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        munmap(data, sizeof(shared_data));
        exit(1);
    }

    if (pid == 0) {
        sleep(1);  // wait for parent to write first

        printf("[child ] before update: counter=%d, message=%s\n",
               data->counter, data->message);

        data->counter += 5;
        strcpy(data->message, "Updated by child");

        printf("[child ] after update : counter=%d, message=%s\n",
               data->counter, data->message);

        munmap(data, sizeof(shared_data));
        exit(0);
    } else {
        data->counter = 10;
        strcpy(data->message, "Written by parent");

        printf("[parent] wrote       : counter=%d, message=%s\n",
               data->counter, data->message);

        wait(NULL);

        printf("[parent] after child : counter=%d, message=%s\n",
               data->counter, data->message);

        munmap(data, sizeof(shared_data));
    }

    return 0;
}