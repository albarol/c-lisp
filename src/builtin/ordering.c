
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_ord(clisp_chunk_expr_t* expr, char* op) {
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

    clisp_chunk_delete(first);
    clisp_chunk_delete(second);
    return clisp_chunk_bool(result);
}

clisp_chunk_t*
clisp_builtin_ord_gt(clisp_chunk_expr_t* expr) {
    return clisp_builtin_ord(expr, ">");
}

clisp_chunk_t*
clisp_builtin_ord_lt(clisp_chunk_expr_t* expr) {
    return clisp_builtin_ord(expr, "<");
}

clisp_chunk_t*
clisp_builtin_ord_gte(clisp_chunk_expr_t* expr) {
    return clisp_builtin_ord(expr, ">=");
}

clisp_chunk_t*
clisp_builtin_ord_lte(clisp_chunk_expr_t* expr) {
    return clisp_builtin_ord(expr, "<=");
}