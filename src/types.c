
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
            free(chunk->str);
            break;

        case CLISP_SYMBOL:
            free(chunk->symbol);
            break;

        case CLISP_ERROR:
            free(chunk->error);
            break;

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
clisp_chunk_number(float num) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_NUMBER);
    chunk->number = num;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_symbol(char* symbol) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_SYMBOL);

    chunk->symbol = malloc(strlen(symbol) + 1);
    strcpy(chunk->symbol, symbol);

    return chunk;
}

clisp_chunk_t*
clisp_chunk_str(char* str) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_STRING);

    chunk->str = malloc(strlen(str) + 1);
    strcpy(chunk->str, str);

    return chunk;
}

clisp_chunk_t*
clisp_chunk_error(char* error, ...) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_ERROR);

    va_list args;
    va_start(args, error);

    chunk->error = malloc(512);
    vsnprintf(chunk->error, 511, error, args);

    chunk->error = realloc(chunk->error, strlen(chunk->error) + 1);
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