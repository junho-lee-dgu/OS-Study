CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

all: pipe_demo

pipe_demo: src/pipe_demo.c
	$(CC) $(CFLAGS) -o pipe_demo src/pipe_demo.c

run-pipe: pipe_demo
	./pipe_demo

clean:
	rm -f pipe_demo