#include <builtin/math.h>

clisp_chunk_t*
clisp_builtin_math_arithmetic(clisp_expr_t* expr, clisp_env_t* env, char* op) {

    clisp_expr_assert(expr, expr->count == 1 || expr->count == 2,
                      "Incorrect number of arguments. Got: %li, Expected: 1 or 2", expr->count);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_NUMBER);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);

    if ((strcmp(op, "-") == 0) && expr->count == 0) {
        first->value.number = -first->value.number;
    }
    else {
        clisp_expr_assert(expr, expr->count == 1,
                          "Incorrect number of arguments. Got: 1, Expected: 2");

        clisp_chunk_t* second = clisp_expr_take(expr, 0);
        clisp_chunk_assert_type(second, second->type, CLISP_NUMBER);


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
                clisp_chunk_free(first);
                first = clisp_chunk_error("Division By Zero!");
            } else {
                first->value.number /= second->value.number;
            }
        }

        clisp_chunk_free(second);
    }

    return first;
}


clisp_chunk_t*
clisp_builtin_math_add(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "+");
}

clisp_chunk_t*
clisp_builtin_math_sub(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "-");
}

clisp_chunk_t*
clisp_builtin_math_mul(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "*");
}

clisp_chunk_t*
clisp_builtin_math_div(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "/");
}

clisp_chunk_t*
clisp_builtin_math_mod(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "%");
}

clisp_chunk_t*
clisp_builtin_math_pow(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_arithmetic(expr, env, "^");
}


clisp_chunk_t*
clisp_builtin_math_functions(clisp_expr_t* expr, clisp_env_t* env, char* fn) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_NUMBER);

    clisp_chunk_t* result = NULL;

    if (strcmp(fn, "round") == 0) {
        result = clisp_chunk_number(roundf(chunk->value.number));
    }
    else if (strcmp(fn, "floor") == 0) {
        result = clisp_chunk_number(floorf(chunk->value.number));
    }
    else if (strcmp(fn, "ceil") == 0) {
        result = clisp_chunk_number(ceilf(chunk->value.number));
    }
    else if (strcmp(fn, "sqrt") == 0) {
        result = clisp_chunk_number(sqrtf(chunk->value.number));
    }
    else if (strcmp(fn, "log") == 0) {
        result = clisp_chunk_number(logf(chunk->value.number));
    }
    else if (strcmp(fn, "log10") == 0) {
        result = clisp_chunk_number(log10f(chunk->value.number));
    }
    else if (strcmp(fn, "cos") == 0) {
        result = clisp_chunk_number(cosf(chunk->value.number));
    }
    else if (strcmp(fn, "sin") == 0) {
        result = clisp_chunk_number(sinf(chunk->value.number));
    }
    else if (strcmp(fn, "tan") == 0) {
        result = clisp_chunk_number(tanf(chunk->value.number));
    }
    else if (strcmp(fn, "abs") == 0) {
        result = clisp_chunk_number(fabsf(chunk->value.number));
    }

    clisp_chunk_free(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_math_round(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "round");
}

clisp_chunk_t*
clisp_builtin_math_floor(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "floor");
}


clisp_chunk_t* clisp_builtin_math_ceil(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "ceil");
}

clisp_chunk_t*
clisp_builtin_math_sqrt(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "sqrt");
}

clisp_chunk_t*
clisp_builtin_math_log(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "log");
}

clisp_chunk_t*
clisp_builtin_math_log10(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "log10");
}

clisp_chunk_t*
clisp_builtin_math_sin(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "sin");
}

clisp_chunk_t*
clisp_builtin_math_cos(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "cos");
}

clisp_chunk_t*
clisp_builtin_math_tan(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "tan");
}

clisp_chunk_t*
clisp_builtin_math_abs(clisp_expr_t* expr, clisp_env_t* env) {
    return clisp_builtin_math_functions(expr, env, "abs");
}