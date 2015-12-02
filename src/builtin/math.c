
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_math(clisp_chunk_expr_t* expr, char* op) {

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
clisp_builtin_math_add(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "+");
}

clisp_chunk_t*
clisp_builtin_math_sub(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "-");
}

clisp_chunk_t*
clisp_builtin_math_mul(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "*");
}

clisp_chunk_t*
clisp_builtin_math_div(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "/");
}

clisp_chunk_t*
clisp_builtin_math_mod(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "%");
}

clisp_chunk_t*
clisp_builtin_math_pow(clisp_chunk_expr_t* expr) {
    return clisp_builtin_math(expr, "^");
}