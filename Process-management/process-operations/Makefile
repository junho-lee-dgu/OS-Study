CC = gcc
CFLAGS = -Wall -Wextra -O0 -g

TARGETS = fork_demo fork_exec_wait_demo proc_tree_demo zombie_demo

all: $(TARGETS)

fork_demo: src/fork_demo.c
	$(CC) $(CFLAGS) -o $@ $<

fork_exec_wait_demo: src/fork_exec_wait_demo.c
	$(CC) $(CFLAGS) -o $@ $<

proc_tree_demo: src/proc_tree_demo.c
	$(CC) $(CFLAGS) -o $@ $<

zombie_demo: src/zombie_demo.c
	$(CC) $(CFLAGS) -o $@ $<

run-fork: fork_demo
	./fork_demo

run-exec: fork_exec_wait_demo
	./fork_exec_wait_demo

run-tree: proc_tree_demo
	./proc_tree_demo

run-zombie: zombie_demo
	./zombie_demo

clean:
	rm -f $(TARGETS)