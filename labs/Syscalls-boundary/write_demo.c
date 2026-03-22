#include <unistd.h>

int main(void) {
    write(1, "Hello from write!\n", 18);
    return 0;
}