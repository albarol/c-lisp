#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

static char input[2048];

int main(int argc, char** argv) {

    puts("Lisp version 0.0.1\n");
    puts("Press Ctrl+c to Exit\n");

    while (1) {

        char* input = readline("lisp> ");

        add_history(input);

        printf("No you're a %s\n", input);

        free(input);

    }

    return 0;

}
