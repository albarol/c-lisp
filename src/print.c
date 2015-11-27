
#include "print.h"

void
clisp_print_write(clisp_token_t* token) {
    switch(token->type) {
        case CLISP_NUMBER:
            if (clisp_utils_isint(token->number)) {
                printf("%.0f", token->number);
            } else {
                printf("%.2f", token->number);
            }
            break;
        case CLISP_ERROR: printf("Error: %s", token->error); break;
        case CLISP_SYMBOL: printf("%s", token->symbol); break;
        case CLISP_STRING: clisp_print_write_str(token); break;
        case CLISP_ATOM: clisp_print_write_expr(token, '(', ')'); break;
        case TOKEN_QEXPRESSION: clisp_print_write_expr(token, '{', '}'); break;
        case CLISP_FUNCTION:
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
    if (token->count == 0) {
        return;
    }

    putchar(open);

    for (int i = 0; i < token->count; i++) {

        clisp_print_write(token->tokens[i]);

        if (i != (token->count - 1)) {
            putchar(' ');
        }
    }

    putchar(close);
}

void
clisp_print_write_str(clisp_token_t* token) {
    char* escaped = malloc(strlen(token->str) + 1);
    strcpy(escaped, token->str);

    escaped = mpcf_escape(escaped);

    printf("\"%s\"", escaped);
    free(escaped);
}

char*
clisp_print_type_name(clisp_chunk_type type) {
    switch (type) {
        case CLISP_FUNCTION: return "Function";
        case CLISP_NUMBER: return "Number";
        case CLISP_ERROR: return "Error";
        case CLISP_SYMBOL: return "Symbol";
        case CLISP_STRING: return "String";
        case CLISP_ATOM: return "S-Expression";
        case TOKEN_QEXPRESSION: return "Q-Expression";
        default: return "Unknown";
    }
}
