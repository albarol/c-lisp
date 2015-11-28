
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_ord(clisp_env_t* env, clisp_chunk_t* chunk, char* op) {
    clisp_assert_count(chunk, 2);

    clisp_chunk_t* first = chunk->value.expr.chunks[0];
    clisp_chunk_t* second = chunk->value.expr.chunks[1];


    clisp_assert_type(chunk, first->type, CLISP_NUMBER);
    clisp_assert_type(chunk, second->type, CLISP_NUMBER);

    int result = 0;
    if (strcmp(op, ">") == 0) {
        result = (first->value.number > second->value.number);
    }
    else if (strcmp(op, "<") == 0) {
        result = (first->value.number < second->value.number);
    }
    else if (strcmp(op, ">=") == 0) {
        result = (first->value.number >= second->value.number);
    }
    else if (strcmp(op, "<=") == 0) {
        result = (first->value.number <= second->value.number);
    }

    clisp_chunk_delete(chunk);
    return clisp_chunk_number(result);
}

clisp_chunk_t*
clisp_builtin_ord_gt(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, ">");
}

clisp_chunk_t*
clisp_builtin_ord_lt(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, "<");
}

clisp_chunk_t*
clisp_builtin_ord_gte(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, ">=");
}

clisp_chunk_t*
clisp_builtin_ord_lte(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, "<=");
}