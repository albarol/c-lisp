
#include "types.h"

clisp_chunk_t*
clisp_chunk_new(clisp_chunk_type_t type) {
    clisp_chunk_t* chunk = malloc(sizeof(clisp_chunk_t));
    chunk->type = type;
    return chunk;
}

void
clisp_chunk_delete(clisp_chunk_t* chunk) {
    switch (chunk->type) {

        case CLISP_STRING:
        case CLISP_SYMBOL:
        case CLISP_ERROR:
            free(chunk->value.string);
            break;

        case CLISP_FUNCTION:
            clisp_chunk_delete(chunk->value.func.args);
            clisp_chunk_delete(chunk->value.func.body);
            break;

        case TOKEN_QEXPRESSION:
        case CLISP_ATOM:
            for (int i = 0; i < chunk->count; i++) {
                clisp_chunk_delete(chunk->tokens[i]);
            }
            break;

        default:
            break;
    }
    free(chunk);
}

clisp_chunk_t*
clisp_chunk_copy(clisp_chunk_t* metadata) {
    clisp_chunk_t* copy_token= malloc(sizeof(clisp_chunk_t));
    copy_token->type = metadata->type;

    switch (metadata->type) {

        case CLISP_FUNCTION_C:
            copy_token->value.builtin = metadata->value.builtin;
            break;

        case CLISP_FUNCTION:
            copy_token->value.func.env = clisp_env_copy(metadata->value.func.env);
            copy_token->value.func.args = clisp_chunk_copy(metadata->value.func.args);
            copy_token->value.func.body = clisp_chunk_copy(metadata->value.func.body);
            break;

        case CLISP_NUMBER:
            copy_token->value.number = metadata->value.number;
            break;

        case CLISP_ERROR:
        case CLISP_SYMBOL:
        case CLISP_STRING:
            copy_token->value.string = malloc(strlen(metadata->value.string));
            strcpy(copy_token->value.string, metadata->value.string);
            break;


        case TOKEN_QEXPRESSION:
        case CLISP_ATOM:
            copy_token->count = metadata->count;
            copy_token->tokens = malloc(sizeof(clisp_chunk_t*) * metadata->count);
            for (int i = 0; i < copy_token->count; i++) {
                copy_token->tokens[i] = clisp_chunk_copy(metadata->tokens[i]);
            }
            break;
    }
    return copy_token;
}

clisp_chunk_t*
clisp_chunk_number(float num) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_NUMBER);
    chunk->value.number = num;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_symbol(char* symbol) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_SYMBOL);

    chunk->value.string = malloc(strlen(symbol) + 1);
    strcpy(chunk->value.string, symbol);

    return chunk;
}

clisp_chunk_t*
clisp_chunk_str(char* str) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_STRING);

    chunk->value.string = malloc(strlen(str) + 1);
    strcpy(chunk->value.string, str);

    return chunk;
}

clisp_chunk_t*
clisp_chunk_error(char* error, ...) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_ERROR);

    va_list args;
    va_start(args, error);

    chunk->value.string = malloc(512);
    vsnprintf(chunk->value.string, 511, error, args);

    chunk->value.string = realloc(chunk->value.string, strlen(chunk->value.string) + 1);
    va_end(args);

    return chunk;
}

clisp_chunk_t*
clisp_chunk_sexpr(void) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_ATOM);
    chunk->count = 0;
    chunk->tokens = NULL;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_qexpr(void) {
    clisp_chunk_t* chunk = clisp_chunk_new(TOKEN_QEXPRESSION);
    chunk->count = 0;
    chunk->tokens = NULL;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_builtin(clisp_builtin_t function) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION_C);
    chunk->value.builtin = function;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_function(clisp_chunk_t* args, clisp_chunk_t* body) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION);
    chunk->value.func.args = args;
    chunk->value.func.body = body;
    return chunk;
}