
#include <builtin/bool.h>

clisp_chunk_t*
clisp_builtin_bool_check_type(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(chunk->type == CLISP_BOOL);

    clisp_chunk_free(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_bool_not(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);

    clisp_chunk_assert_type(chunk, chunk->type, CLISP_BOOL);
    clisp_chunk_t* result = clisp_chunk_bool(!chunk->value.boolean);

    clisp_chunk_free(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_bool_logical(clisp_expr_t* expr, clisp_env_t* env, char* op) {
    clisp_expr_assert_count(expr, 2);

    for (int i = 0; i < expr->count; i++) {
        clisp_expr_assert_type(expr, expr->chunks[i]->type, CLISP_BOOL);
    }

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_take(expr, 0);

    clisp_chunk_t* result = NULL;
    if (strcmp(op, "and") == 0) {
        result = clisp_chunk_bool(first->value.boolean && second->value.boolean);
    }
    else if (strcmp(op, "or") == 0) {
        result = clisp_chunk_bool(first->value.boolean || second->value.boolean);
    }
    else if (strcmp(op, "xor") == 0) {
        result = clisp_chunk_bool(first->value.boolean ^ second->value.boolean);
    }
    else if (strcmp(op, "nand") == 0) {
        result = clisp_chunk_bool(!(first->value.boolean && second->value.boolean));
    }
    else if (strcmp(op, "nor") == 0) {
        result = clisp_chunk_bool(!(first->value.boolean || second->value.boolean));
    }

    clisp_chunk_free(first);
    clisp_chunk_free(second);
    return result;
}

clisp_chunk_t*
clisp_builtin_bool_and(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_logical(expr, env, "and");
}

clisp_chunk_t*
clisp_builtin_bool_or(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_logical(expr, env, "or");
}

clisp_chunk_t*
clisp_builtin_bool_xor(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_logical(expr, env, "xor");
}

clisp_chunk_t*
clisp_builtin_bool_nand(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_logical(expr, env, "nand");
}

clisp_chunk_t*
clisp_builtin_bool_nor(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_logical(expr, env, "nor");
}

clisp_chunk_t*
clisp_builtin_bool_compare(clisp_expr_t* expr, clisp_env_t* env, char* op) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_take(expr, 0);

    int result = 0;
    if (strcmp(op, "eq") == 0) {
        result = clisp_chunk_cmp(first, second);
    }

    if (strcmp(op, "ne") == 0) {
        result = !clisp_chunk_cmp(first, second);
    }

    clisp_chunk_free(first);
    clisp_chunk_free(second);
    return clisp_chunk_bool((bool)result);
}

clisp_chunk_t*
clisp_builtin_bool_equal(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_compare(expr, env, "eq");
}

clisp_chunk_t*
clisp_builtin_bool_not_equal(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_bool_compare(expr, env, "ne");
}