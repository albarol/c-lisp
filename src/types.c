
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

        case CLISP_LIST:
            if (chunk->value.list->count > 0) {
                clisp_expr_delete(chunk->value.list);
            }
            break;

        case CLISP_FUNCTION:
            clisp_env_delete(chunk->value.func.env);
            clisp_chunk_delete(chunk->value.func.args);
            clisp_chunk_delete(chunk->value.func.body);
            break;

//        case TOKEN_QEXPRESSION:
//        case CLISP_ATOM:
//            for (int i = 0; i < chunk->value.expr.count; i++) {
//                clisp_chunk_delete(chunk->value.expr.chunks[i]);
//            }
//            break;

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


//        case TOKEN_QEXPRESSION:
//        case CLISP_ATOM:
//            copy_token->value.expr.count = metadata->value.expr.count;
//            copy_token->value.expr.chunks = malloc(sizeof(clisp_chunk_t*) * metadata->value.expr.count);
//            for (int i = 0; i < copy_token->value.expr.count; i++) {
//                copy_token->value.expr.chunks[i] = clisp_chunk_copy(metadata->value.expr.chunks[i]);
//            }
//            break;

        default:
            break;
    }
    return copy_token;
}

int
clisp_chunk_cmp(clisp_chunk_t* first, clisp_chunk_t* second) {

    if (first->type != second->type) {
        return 0;
    }

    switch (first->type) {

        case CLISP_BOOL:
        case CLISP_NUMBER:
            return (first->value.number == second->value.number);

        case CLISP_ERROR:
        case CLISP_SYMBOL:
        case CLISP_STRING:
            return (strcmp(first->value.string, second->value.string) == 0);

        case CLISP_LIST:
            if (first->value.list->count != second->value.list->count) { return 0; }
            for (int i = 0; i < first->value.list->count; i++) {
                if (!clisp_chunk_cmp(first->value.list->chunks[i], second->value.list->chunks[i])) {
                    return 0;
                }
            }
            return 1;

        case CLISP_FUNCTION_C:
            return first->value.builtin.body == second->value.builtin.body;

        case CLISP_FUNCTION:
            return clisp_chunk_cmp(first->value.func.args, second->value.func.args)
                   && clisp_chunk_cmp(first->value.func.body, second->value.func.body);

//        case TOKEN_QEXPRESSION:
//        case CLISP_ATOM:
//            if (first->value.expr.count != second->value.expr.count) { return 0; }
//            for (int i = 0; i < first->value.expr.count; i++) {
//                if (!clisp_chunk_cmp(first->value.expr.chunks[i], second->value.expr.chunks[i])) {
//                    return 0;
//                }
//            }
//            return 1;

        default:
            break;
    }
    return 0;
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
clisp_chunk_list(void) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_LIST);
    chunk->value.list = malloc(sizeof(clisp_chunk_expr_t));
    chunk->value.list->count = 0;
    chunk->value.list->chunks = NULL;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_bool(int num) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_BOOL);
    chunk->value.number = (num == 1) ? 1 : 0;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_builtin(clisp_builtin_t function) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION_C);
    chunk->value.builtin.body = function;
    chunk->value.builtin.expr = NULL;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_function(clisp_chunk_t* args, clisp_chunk_t* body) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION);
    chunk->value.func.env = clisp_env_new();
    chunk->value.func.args = args;
    chunk->value.func.body = body;
    //chunk->value.func.count = args->value.expr.count;
    return chunk;
}