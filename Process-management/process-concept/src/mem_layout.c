#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_init = 42;
int global_uninit;
static int static_init = 7;

void sample_function(void) {
    // empty
}

int main(void) {
    int local_var = 10;
    static int local_static = 99;
    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL) {
        perror("malloc failed");
        return 1;
    }

    *heap_var = 1234;

    printf("=== Process Basic Info ===\n");
    printf("PID   : %d\n", getpid());
    printf("PPID  : %d\n", getppid());

    printf("\n=== Addresses ===\n");
    printf("sample_function (code/text) : %p\n", (void *)sample_function);
    printf("global_init     (data)      : %p\n", (void *)&global_init);
    printf("global_uninit   (bss/data)  : %p\n", (void *)&global_uninit);
    printf("static_init     (data)      : %p\n", (void *)&static_init);
    printf("local_static    (data)      : %p\n", (void *)&local_static);
    printf("heap_var ptr    (stack)     : %p\n", (void *)&heap_var);
    printf("heap target     (heap)      : %p\n", (void *)heap_var);
    printf("local_var       (stack)     : %p\n", (void *)&local_var);

    printf("\n=== Values ===\n");
    printf("global_init   = %d\n", global_init);
    printf("global_uninit = %d\n", global_uninit);
    printf("static_init   = %d\n", static_init);
    printf("local_static  = %d\n", local_static);
    printf("local_var     = %d\n", local_var);
    printf("*heap_var     = %d\n", *heap_var);

    free(heap_var);
    //return 0;

    printf("\nPress Enter to exit...\n");
    getchar();
    return 0;
}