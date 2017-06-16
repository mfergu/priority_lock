CC=gcc
CFLAGS=-Wall -g -pthread
BINS=test

test: plock.c main.c
	$(CC) $(CFLAGS) -o test plock.c main.c
