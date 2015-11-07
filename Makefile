
CC = clang
CFLAGS = -Wall -std=c99
INCLUDE = -I./ext/mpc -I./

SOURCES = $(wildcard *.c) ext/mpc/mpc.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -lm -ledit $(LIBS) $(INCLUDE) -o repl

clean:
	rm -rf repl

.PHONY: all
