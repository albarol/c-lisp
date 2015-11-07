
CC = gcc
CFLAGS = -Wall -std=c99
INCLUDE = -I./ext/mpc

SOURCES = $(wildcard *.c) ext/mpc/mpc.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -lm -ledit $(LIBS) $(INCLUDE) -o repl

clean:
	rm -rf build/

.PHONY: all
