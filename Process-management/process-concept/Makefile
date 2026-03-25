CC=gcc
CFLAGS=-Wall -Wextra -O0 -g
TARGET=mem_layout

all: $(TARGET)

$(TARGET): src/mem_layout.c
	$(CC) $(CFLAGS) -o $(TARGET) src/mem_layout.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)