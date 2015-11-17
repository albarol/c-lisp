
CC = clang
CFLAGS = -w --std=c11
INCLUDE = -I./ext/mpc -I./

SOURCES = $(wildcard *.c) ext/mpc/mpc.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -lm -ledit $(LIBS) $(INCLUDE) -o build/repl

clean:
	rm -rf repl

.PHONY: all
