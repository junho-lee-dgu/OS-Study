#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    const char *msg = "hello from client";

    if (argc > 1) {
        msg = argv[1];
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sock_fd);
        exit(1);
    }

    printf("[client] connected to server\n");

    if (send(sock_fd, msg, strlen(msg), 0) < 0) {
        perror("send failed");
        close(sock_fd);
        exit(1);
    }

    printf("[client] sent: %s\n", msg);

    ssize_t n = recv(sock_fd, buffer, BUF_SIZE - 1, 0);
    if (n < 0) {
        perror("recv failed");
        close(sock_fd);
        exit(1);
    }

    buffer[n] = '\0';
    printf("[client] received echo: %s\n", buffer);

    close(sock_fd);
    return 0;
}