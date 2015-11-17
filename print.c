
#include "print.h"

void
clisp_print_write(clisp_token_t* token) {
    switch(token->type) {
        case TOKEN_NUMBER: printf("%li", token->number); break;
        case TOKEN_ERROR: printf("Error: %s", token->error); break;
        case TOKEN_SYMBOL: printf("%s", token->symbol); break;
        case TOKEN_SEXPRESSION: clisp_print_write_expr(token, '(', ')'); break;
        case TOKEN_QEXPRESSION: clisp_print_write_expr(token, '{', '}'); break;
        case TOKEN_FUNCTION: printf("<function>"); break;
    }
}

void
clisp_print_writeln(clisp_token_t* token) {
    clisp_print_write(token);
    putchar('\n');
}

void
clisp_print_write_expr(clisp_token_t* token, char open, char close) {
    putchar(open);

    for (int i = 0; i < token->count; i++) {

        clisp_print_write(token->tokens[i]);

        if (i != (token->count - 1)) {
            putchar(' ');
        }
    }

    putchar(close);
}
