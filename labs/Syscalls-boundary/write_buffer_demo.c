#include <unistd.h>

int main(void) {
    write(1, "A", 1);
    sleep(2);
    write(1, "B\n", 2);
    return 0;
}