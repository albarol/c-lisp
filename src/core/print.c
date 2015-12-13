
#include "print.h"
#include "types.h"

void
clisp_print_write(clisp_chunk_t* chunk) {
    switch(chunk->type) {
        case CLISP_NUMBER:
            printf("%g", chunk->value.number);
            break;
        case CLISP_BOOL:
            if (chunk->value.boolean == 1) {
                printf("#t");
            } else {
                printf("#f");
            }
            break;
        case CLISP_ERROR: printf("Error: %s", chunk->value.string); break;
        case CLISP_SYMBOL: printf("%s", chunk->value.string); break;
        case CLISP_STRING: clisp_print_write_str(chunk); break;
        case CLISP_LIST: clisp_print_write_expr(chunk->value.list, '[', ']'); break;
        case CLISP_FUNCTION_C:
            printf("<builtin>");
            break;
        case CLISP_FUNCTION:
            printf("(fn ");
            clisp_print_write(chunk->value.func.args);
            putchar(' ');
            clisp_print_write(chunk->value.func.body);
            putchar(')');
            break;
        case CLISP_EXPR:
            clisp_print_write_expr(chunk->value.list, '(', ')');
            break;
        default:
            break;
    }
}

void
clisp_print_writeln(clisp_chunk_t* token) {
    clisp_print_write(token);
    putchar('\n');
}

void
clisp_print_write_expr(clisp_expr_t* expr, char open, char close) {
    putchar(open);

    for (int i = 0; i < expr->count; i++) {

        clisp_print_write(expr->chunks[i]);

        if (i != (expr->count - 1)) {
            putchar(' ');
        }
    }

    putchar(close);
}


void
clisp_print_write_str(clisp_chunk_t* token) {
//    char* escaped = malloc(strlen(token->value.string) + 1);
//    strcpy(escaped, token->value.string);
//
//    escaped = mpcf_escape(escaped);
//
//    printf("\"%s\"", escaped);
//    free(escaped);
    printf("%s", token->value.string);
}

char*
clisp_print_type_name(clisp_chunk_type_t type) {
    switch (type) {
        case CLISP_NIL: return "Nil";
        case CLISP_FUNCTION_C:
        case CLISP_FUNCTION:
            return "Function";
        case CLISP_NUMBER: return "Number";
        case CLISP_ERROR: return "Error";
        case CLISP_SYMBOL: return "Symbol";
        case CLISP_STRING: return "String";
        case CLISP_LIST: return  "List";
        case CLISP_BOOL: return "Boolean";
        case CLISP_EXPR: return "Expression";
        case CLISP_TYPE: return "Any type";
        default: return "Unkown";
    }
}
