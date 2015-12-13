
#include <stdio.h>
#include <mpc.h>
#include <editline/readline.h>

#include "types.h"
#include "builtin.h"
#include <parser.h>
#include <utils.h>

#ifdef HAVE_PRELUDE
#include "stl.h"
#endif

static char input[2048];

int main(int argc, char** argv) {

    puts("Welcome to CLisp, version 0.5.0\n");
    puts("Press Ctrl+c to Exit");

#ifdef HAVE_PRELUDE
    printf("\nLoaded libraries\n");
    printf("  * prelude.clisp\n");
#endif
    putchar('\n');

    clisp_env_t* env = clisp_env_new();
    clisp_builtin_load_functions(env);

#ifdef HAVE_PRELUDE
    char* lines = strtok(stl_prelude_clisp, "\n");
    while (lines != NULL) {
        clisp_process(lines, env, false);
        lines = strtok (NULL, "\n");
    }
    free(lines);
#endif

    if (argc > 1) {
        char command[1024];
        strcpy(command, "(load \"");
        strcat(command, argv[1]);
        strcat(command, "\")");
        clisp_process(command, env, true);
    } else {
        while (1) {
            char* input = readline("> ");
            add_history(input);
            clisp_process(input, env, true);
            free(input);
        }
    }

    return 0;
}
