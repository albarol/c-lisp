
#include <builtin/math.h>
#include <types.h>

clisp_chunk_t*
clisp_builtin_math(clisp_expr_t* expr, clisp_env_t* env, char* op) {

    clisp_expr_assert(expr, 1 <= expr->count <= 2,
                      "Incorrect number of Arguments. Got: %li, Expected: %s", expr->count, "1 or 2");
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_NUMBER);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_NUMBER);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);

    if ((strcmp(op, "-") == 0) && expr->count == 0) {
        first->value.number = -first->value.number;
    }
    else {
        clisp_expr_assert(expr, expr->count == 1,
                          "Incorrect number of Arguments. Got: 1, Expected: 2");
        clisp_chunk_t* second = clisp_expr_pop(expr, 0);

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
                first = clisp_chunk_error("Division By Zero!");
            } else {
                first->value.number /= second->value.number;
            }
        }

        clisp_expr_delete(expr);
        clisp_chunk_delete(second);
    }

    return first;
}


clisp_chunk_t*
clisp_builtin_math_add(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "+");
}

clisp_chunk_t*
clisp_builtin_math_sub(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "-");
}

clisp_chunk_t*
clisp_builtin_math_mul(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "*");
}

clisp_chunk_t*
clisp_builtin_math_div(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "/");
}

clisp_chunk_t*
clisp_builtin_math_mod(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "%");
}

clisp_chunk_t*
clisp_builtin_math_pow(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math(expr, env, "^");
}

clisp_chunk_t*
clisp_builtin_math_round(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(roundf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_floor(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(floorf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}


clisp_chunk_t* clisp_builtin_math_ceil(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(ceilf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_sqrt(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(sqrtf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_log(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(log10f(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_log10(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(logf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_sin(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(sinf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_cos(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(cosf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_tan(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = clisp_chunk_number(tanf(chunk->value.number));

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_pi(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 0);
    clisp_expr_delete(expr);

    return clisp_chunk_number(3.141592653589793f);
}