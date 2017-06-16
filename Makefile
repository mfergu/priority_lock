CC=gcc
CFLAGS=-Wall -g -pthread
BINS=test 

test: plock.c test2.c
	$(CC) $(CFLAGS) -o test plock.c test2.c

