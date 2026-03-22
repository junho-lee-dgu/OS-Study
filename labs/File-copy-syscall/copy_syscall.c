#include <fcntl.h>      // open
#include <unistd.h>     // read, write, close
#include <stdio.h>      // perror
#include <stdlib.h>     // exit

#define BUFFER_SIZE 64

int main(int argc, char *argv[]) {
    int src_fd, dst_fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        /*
        argv[0] = 프로그램 이름
        argv[1] = source.txt
        argv[2] = copied.txt
        */
        write(2, "Usage: ./copy_syscall <source> <destination>\n", 45);
        return 1;
    }

    src_fd = open(argv[1], O_RDONLY); //원본 파일을 읽기 전용으로 열기
    if (src_fd < 0) {
        perror("open source");
        return 1;
    }
    /*
    O_WRONLY : 쓰기 전용으로 열기
    O_CREAT : 파일이 없으면 새로 만들기
    O_TRUNC : 파일이 이미 있으면 내용 비우고 시작
    0644 : 파일 권한
    */
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (dst_fd < 0) {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    /*
    원본 파일에서
    최대 64바이트를 읽어
    buffer에 저장하고
    실제 읽은 바이트 수를 bytes_read에 넣는다

    그리고 읽은 바이트 수가 0보다 크면 계속 반복한다.
    */
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t total_written = 0;

        while (total_written < bytes_read) //partial write 대비
        {
            ssize_t bytes_written = write(dst_fd,
                                          buffer + total_written,
                                          bytes_read - total_written);

            if (bytes_written < 0) {
                perror("write");
                close(src_fd);
                close(dst_fd);
                return 1;
            }

            total_written += bytes_written;
        }
    }

    if (bytes_read < 0) {
        perror("read");
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    if (close(src_fd) < 0) {
        perror("close source");
        close(dst_fd);
        return 1;
    }

    if (close(dst_fd) < 0) {
        perror("close destination");
        return 1;
    }

    return 0;
}