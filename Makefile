CC=gcc
filewait: filewait.c
	$(CC) -o $@ $<
