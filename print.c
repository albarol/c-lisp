
#include "print.h"

void
clisp_print_write(clisp_token_t* token) {
    switch(token->type) {
        case TOKEN_NUMBER:
            if (clisp_utils_isint(token->number)) {
                printf("%.0f", token->number);
            } else {
                printf("%.2f", token->number);
            }
            break;
        case TOKEN_ERROR: printf("Error: %s", token->error); break;
        case TOKEN_SYMBOL: printf("%s", token->symbol); break;
        case TOKEN_SEXPRESSION: clisp_print_write_expr(token, '(', ')'); break;
        case TOKEN_QEXPRESSION: clisp_print_write_expr(token, '{', '}'); break;
        case TOKEN_FUNCTION:
            if(token->builtin) {
                printf("<function>");
            } else {
                printf("(\\ ");
                clisp_print_write(token->formals);
                putchar(' ');
                clisp_print_write(token->body);
                putchar(')');
            }
            break;
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

char*
clisp_print_type_name(clisp_token_type_t type) {
    switch (type) {
        case TOKEN_FUNCTION: return "Function";
        case TOKEN_NUMBER: return "Number";
        case TOKEN_ERROR: return "Error";
        case TOKEN_SYMBOL: return "Symbol";
        case TOKEN_SEXPRESSION: return "S-Expression";
        case TOKEN_QEXPRESSION: return "Q-Expression";
        default: return "Unknown";
    }
}
