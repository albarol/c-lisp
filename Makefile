
CC = clang
CFLAGS = -Wall -std=c99 -v
INCLUDE = -I./ext/mpc -I./

SOURCES = $(wildcard *.c) ext/mpc/mpc.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -lm -ledit $(LIBS) $(INCLUDE) -o build/repl

clean:
	rm -rf repl

.PHONY: all
