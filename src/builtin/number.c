
#include <builtin/number.h>

clisp_chunk_t*
clisp_builtin_number_check_type(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(chunk->type == CLISP_NUMBER);

    clisp_chunk_free(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_number_check_property(clisp_expr_t* expr, clisp_env_t* env, char* op) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = NULL;

    if (strcmp(op, "zero") == 0) {
        result = clisp_chunk_bool(chunk->value.number == 0);
    }
    else if (strcmp(op, "positive") == 0) {
        result = clisp_chunk_bool(chunk->value.number > 0);
    }
    else if (strcmp(op, "negative") == 0) {
        result = clisp_chunk_bool(chunk->value.number < 0);
    }
    else if (strcmp(op, "even") == 0) {
        int number = (int)chunk->value.number;
        result = clisp_chunk_bool((number & 1) == 0);
    }
    else if (strcmp(op, "odd") == 0) {
        int number = (int)chunk->value.number;
        result = clisp_chunk_bool((number & 1) == 1);
    }

    clisp_chunk_free(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_number_is_zero(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_check_property(expr, env, "zero");
}

clisp_chunk_t*
clisp_builtin_number_is_positive(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_check_property(expr, env, "positive");
}

clisp_chunk_t*
clisp_builtin_number_is_negative(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_check_property(expr, env, "negative");
}

clisp_chunk_t*
clisp_builtin_number_is_even(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_check_property(expr, env, "even");
}

clisp_chunk_t*
clisp_builtin_number_is_odd(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_check_property(expr, env, "odd");
}

clisp_chunk_t*
clisp_builtin_number_ordering(clisp_expr_t* expr, clisp_env_t* env, char* op) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_NUMBER);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_NUMBER);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_pop(expr, 0);

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

    clisp_chunk_free(first);
    clisp_chunk_free(second);
    return clisp_chunk_bool(result == 1 ? true : false);
}

clisp_chunk_t*
clisp_builtin_number_ordering_gt(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_ordering(expr, env, ">");
}

clisp_chunk_t*
clisp_builtin_number_ordering_lt(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_ordering(expr, env, "<");
}

clisp_chunk_t*
clisp_builtin_number_ordering_gte(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_ordering(expr, env, ">=");
}

clisp_chunk_t*
clisp_builtin_number_ordering_lte(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_number_ordering(expr, env, "<=");
}