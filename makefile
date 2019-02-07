CC=gcc
CFLAGS=-g -Wall -std=c99 -D_XOPEN_SOURCE=500
RM=rm

all: clean disk

disk: mydisk.c mydisk.h
		$(CC) $(CFLAGS) -o disk mydisk.c

clean:
		$(RM) -rf disk *.dSYM
