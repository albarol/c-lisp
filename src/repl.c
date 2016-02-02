
#include <stdio.h>
#include <mpc.h>
#include <editline/readline.h>

#include "types.h"
#include "builtin.h"
#include <parser.h>
#include <utils.h>

#ifdef HAVE_PRELUDE
#include <stl.h>
#endif

void
load_script(char* filename, clisp_env_t* env) {
    char command[1024];
    strcpy(command, "(load \"");
    strcat(command, filename);
    strcat(command, "\")");
    clisp_process(command, env, false);
}

int
main(int argc, char** argv) {

    puts("Welcome to CLisp, version 0.6.0\n");
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

    bool enterRepl = true;
    switch (argc) {
        case 2: {
            load_script(argv[1], env);
            enterRepl = false;
            break;
        }
        case 3: {
            if (strcmp("-i", argv[1]) == 0) {
                printf("Loaded file: %s\n\n", argv[2]);
                load_script(argv[2], env);
            }
            else {
                printf("the \"%s\" is an invalid argument.", argv[1]);
                exit(EXIT_SUCCESS);
            }
            break;
        }
        default: break;
    }

    if (enterRepl) {
        while (1) {
            char* input = readline("> ");
            add_history(input);
            clisp_process(input, env, true);
            free(input);
        }
    }

    return 0;
}
