#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUF_SIZE 1024

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(1);
    }

    printf("[server] listening on 127.0.0.1:%d\n", PORT);
    printf("[server] waiting for client...\n");

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept failed");
        close(server_fd);
        exit(1);
    }

    printf("[server] client connected\n");

    ssize_t n = recv(client_fd, buffer, BUF_SIZE - 1, 0);
    if (n < 0) {
        perror("recv failed");
        close(client_fd);
        close(server_fd);
        exit(1);
    }

    buffer[n] = '\0';
    printf("[server] received: %s\n", buffer);

    if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
        perror("send failed");
        close(client_fd);
        close(server_fd);
        exit(1);
    }

    printf("[server] echoed message back to client\n");

    close(client_fd);
    close(server_fd);
    return 0;
}