
#include "token.h"


clisp_token_t*
clisp_token_number(long num) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_NUMBER;
    token->number = num;
    return token;
}

clisp_token_t*
clisp_token_error(char* error) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_ERROR;
    token->error = malloc(strlen(error) + 1);
    strcpy(token->error, error);
    return token;
}

clisp_token_t*
clisp_token_symbol(char* symbol) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_SYMBOL;
    token->symbol = malloc(strlen(symbol) + 1);
    strcpy(token->symbol, symbol);
    return token;
}

clisp_token_t*
clisp_token_sexpr(void) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_SEXPRESSION;
    token->count = 0;
    token->tokens = NULL;
    return token;
}

clisp_token_t*
clisp_token_qexpr(void) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_QEXPRESSION;
    token->count = 0;
    token->tokens = NULL;
    return token;
}

clisp_token_t*
clisp_token_function(clisp_function_t function) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_FUNCTION;
    token->function = function;
    return token;
}


void
clisp_token_del(clisp_token_t* token) {

    switch (token->type) {

        case TOKEN_FUNCTION:
        case TOKEN_NUMBER:
            break;

        case TOKEN_ERROR:
            free(token->error);
            break;

        case TOKEN_SYMBOL:
            free(token->symbol);
            break;

        case TOKEN_QEXPRESSION:
        case TOKEN_SEXPRESSION:
            for (int i = 0; i < token->count; i++) {
                clisp_token_del(token->tokens[i]);
            }
            break;
    }

    free(token);
}

clisp_token_t*
clisp_token_append(clisp_token_t* super, clisp_token_t* child) {
    super->count++;
    super->tokens = realloc(super->tokens, sizeof(clisp_token_t*) * super->count);
    super->tokens[super->count - 1] = child;
    return super;
}

clisp_token_t*
clisp_token_pop(clisp_token_t* token, int position) {

    clisp_token_t* item = token->tokens[position];

    memmove(&token->tokens[position], &token->tokens[position + 1],
            sizeof(clisp_token_t*) * (token->count-position-1));

    token->count--;

    token->tokens = realloc(token->tokens, sizeof(clisp_token_t*) * (token->count));
    return item;
}


clisp_token_t*
clisp_token_take(clisp_token_t* token, int position) {
    clisp_token_t* item = clisp_token_pop(token, position);
    clisp_token_del(token);
    return item;
}


clisp_token_t*
clisp_token_join(clisp_token_t* first, clisp_token_t* second) {
    while (second->count) {
        first = clisp_token_append(first, clisp_token_pop(second, 0));
    }

    clisp_token_del(second);
    return first;
}


clisp_token_t*
clisp_token_copy(clisp_token_t* token) {

    clisp_token_t* copy_token= malloc(sizeof(clisp_token_t));
    copy_token->type = token->type;

    switch (token->type) {
        case TOKEN_FUNCTION:
            copy_token->function = token->function;
            break;

        case TOKEN_NUMBER:
            copy_token->number = token->number;
            break;

        case TOKEN_ERROR:
            copy_token->error = malloc(strlen(token->error));
            strcpy(copy_token->error, token->symbol);
            break;

        case TOKEN_SYMBOL:
            copy_token->symbol = malloc(strlen(token->symbol));
            strcpy(copy_token->symbol, token->symbol);
            break;

        case TOKEN_QEXPRESSION:
        case TOKEN_SEXPRESSION:
            copy_token->count = token->count;
            copy_token->tokens = malloc(sizeof(clisp_token_t*) * token->count);
            for (int i = 0; i < copy_token->count; i++) {
                copy_token->tokens[i] = clisp_token_copy(token->tokens[i]);
            }
            break;
    }
    return copy_token;
}
