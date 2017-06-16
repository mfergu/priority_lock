CC=clang
CFLAGS=-std=c11 -Weverything -g -pthread
BINS=test

test: plock.c main.c
	$(CC) $(CFLAGS) -o test plock.c main.c
