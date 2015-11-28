
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_math(clisp_env_t* env, clisp_chunk_t* chunk, char* op) {

    for (int i = 0; i < chunk->value.expr.count; i++) {
        clisp_chunk_t* item = chunk->value.expr.chunks[i];

        if (item->type != CLISP_NUMBER) {
            clisp_chunk_delete(chunk);
            return clisp_chunk_error("Cannot operate on non-number!");
        }
    }

    clisp_chunk_t* first = clisp_expr_pop(chunk, 0);

    if ((strcmp(op, "-") == 0) && chunk->value.expr.count == 0) {
        first->value.number = -first->value.number;
    }

    while (chunk->value.expr.count > 0) {

        clisp_chunk_t* second = clisp_expr_pop(chunk, 0);

        if (strcmp(op, "+") == 0) { first->value.number += second->value.number; }
        if (strcmp(op, "-") == 0) { first->value.number -= second->value.number; }
        if (strcmp(op, "*") == 0) { first->value.number *= second->value.number; }
        if (strcmp(op, "%") == 0) { first->value.number = fmod(first->value.number, second->value.number); }
        if (strcmp(op, "^") == 0) {
            float base = first->value.number;
            for (int i = 1; i < second->value.number; i++) {
                first->value.number *= base;
            }
        }
        if (strcmp(op, "/") == 0) {
            if (second->value.number == 0) {
                clisp_chunk_delete(first);
                clisp_chunk_delete(second);
                first = clisp_chunk_error("Division By Zero!");
                break;
            }
            first->value.number /= second->value.number;
        }

        clisp_chunk_delete(second);
    }

    clisp_chunk_delete(chunk);
    return first;
}


clisp_chunk_t*
clisp_builtin_math_add(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "+");
}

clisp_chunk_t*
clisp_builtin_math_sub(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "-");
}

clisp_chunk_t*
clisp_builtin_math_mul(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "*");
}

clisp_chunk_t*
clisp_builtin_math_div(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "/");
}

clisp_chunk_t*
clisp_builtin_math_mod(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "%");
}

clisp_chunk_t*
clisp_builtin_math_pow(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "^");
}