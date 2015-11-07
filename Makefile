CC=gcc-4.8
CCFLAGS=-Wall -std=c99
LIBS=-ledit

default_target:
	$(CC) $(CCFLAGS) repl.c $(LIBS) -o repl

.PHONY: default_target
