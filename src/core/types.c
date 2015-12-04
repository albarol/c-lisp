#include <types.h>

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

        case CLISP_EXPR:
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

        default:
            break;
    }
    free(chunk);
}



clisp_chunk_t*
clisp_chunk_copy(clisp_chunk_t* metadata) {
    clisp_chunk_t* chunk = malloc(sizeof(clisp_chunk_t));
    chunk->type = metadata->type;

    switch (metadata->type) {

        case CLISP_BOOL:
            chunk->value.boolean = metadata->value.boolean;
            break;

        case CLISP_FUNCTION_C:
            chunk->value.builtin.body = metadata->value.builtin.body;
            chunk->value.builtin.ftype = metadata->value.builtin.ftype;
            break;

        case CLISP_FUNCTION:
            chunk->value.func.env = clisp_env_copy(metadata->value.func.env);
            chunk->value.func.args = clisp_chunk_copy(metadata->value.func.args);
            chunk->value.func.body = clisp_chunk_copy(metadata->value.func.body);
            break;

        case CLISP_NUMBER:
            chunk->value.number = metadata->value.number;
            break;

        case CLISP_ERROR:
        case CLISP_SYMBOL:
        case CLISP_STRING:
            chunk->value.string = malloc(strlen(metadata->value.string) + 1);
            strcpy(chunk->value.string, metadata->value.string);
            break;

        case CLISP_LIST:
        case CLISP_EXPR:
            chunk->value.list = clisp_expr_new();
            chunk->value.list->count = metadata->value.list->count;
            chunk->value.list->chunks = malloc(sizeof(clisp_chunk_t*) * metadata->value.list->count);
            for (int i = 0; i < chunk->value.list->count; i++) {
                chunk->value.list->chunks[i] = clisp_chunk_copy(metadata->value.list->chunks[i]);
            }
            break;
        default: break;
    }
    return chunk;
}

bool
clisp_chunk_cmp(clisp_chunk_t* first, clisp_chunk_t* second) {

    if (first->type != second->type) {
        return false;
    }

    switch (first->type) {

        case CLISP_BOOL:
            return (first->value.boolean == second->value.boolean);

        case CLISP_NUMBER:
            return (first->value.number == second->value.number);

        case CLISP_ERROR:
        case CLISP_SYMBOL:
        case CLISP_STRING:
            return (strcmp(first->value.string, second->value.string) == 0);

        case CLISP_EXPR:
        case CLISP_LIST:
            if (first->value.list->count != second->value.list->count) { return 0; }
            for (int i = 0; i < first->value.list->count; i++) {
                if (!clisp_chunk_cmp(first->value.list->chunks[i], second->value.list->chunks[i])) {
                    return false;
                }
            }
            return true;

        case CLISP_FUNCTION_C:
            return first->value.builtin.body == second->value.builtin.body;

        case CLISP_FUNCTION:
            return clisp_chunk_cmp(first->value.func.args, second->value.func.args)
                   && clisp_chunk_cmp(first->value.func.body, second->value.func.body);

        default:
            break;
    }
    return false;
}


clisp_chunk_t*
clisp_chunk_nil() {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_NIL);
    return chunk;
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
    chunk->value.list = malloc(sizeof(clisp_expr_t));
    chunk->value.list->count = 0;
    chunk->value.list->chunks = NULL;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_bool(bool value) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_BOOL);
    chunk->value.boolean = value;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_builtin(clisp_builtin_t function, clisp_function_type ftype) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION_C);
    chunk->value.builtin.ftype = ftype;
    chunk->value.builtin.body = function;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_function(clisp_chunk_t* args, clisp_chunk_t* body) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_FUNCTION);
    chunk->value.func.env = clisp_env_new();
    chunk->value.func.args = args;
    chunk->value.func.body = body;
    return chunk;
}

clisp_chunk_t*
clisp_chunk_expr() {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_EXPR);
    chunk->value.list = malloc(sizeof(clisp_expr_t));
    chunk->value.list->count = 0;
    chunk->value.list->chunks = NULL;
    return chunk;
}