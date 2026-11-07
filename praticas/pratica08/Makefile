CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
all: main
main: *.c
	$(CC) $(CFLAGS) *.c -o main -lm
clean:
	rm -f main *.o
.PHONY: all clean
