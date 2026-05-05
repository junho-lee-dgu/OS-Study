CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

all: pipe_demo mmap_shared_demo tcp_echo_server tcp_echo_client

pipe_demo: src/pipe_demo.c
	$(CC) $(CFLAGS) -o pipe_demo src/pipe_demo.c

mmap_shared_demo: src/mmap_shared_demo.c
	$(CC) $(CFLAGS) -o mmap_shared_demo src/mmap_shared_demo.c

tcp_echo_server: src/tcp_echo_server.c
	$(CC) $(CFLAGS) -o tcp_echo_server src/tcp_echo_server.c

tcp_echo_client: src/tcp_echo_client.c
	$(CC) $(CFLAGS) -o tcp_echo_client src/tcp_echo_client.c

run-pipe: pipe_demo
	./pipe_demo

run-mmap: mmap_shared_demo
	./mmap_shared_demo

run-server: tcp_echo_server
	./tcp_echo_server

run-client: tcp_echo_client
	./tcp_echo_client

clean:
	rm -f pipe_demo mmap_shared_demo tcp_echo_server tcp_echo_client