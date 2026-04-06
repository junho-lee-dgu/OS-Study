CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

all: cpu_bound io_bound

cpu_bound: src/cpu_bound.c
	$(CC) $(CFLAGS) -o cpu_bound src/cpu_bound.c

io_bound: src/io_bound.c
	$(CC) $(CFLAGS) -o io_bound src/io_bound.c

run-cpu: cpu_bound
	./cpu_bound

run-io: io_bound
	./io_bound

clean:
	rm -f cpu_bound io_bound