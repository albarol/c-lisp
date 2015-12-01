
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_cmp(clisp_chunk_expr_t* expr, char* op) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_pop(expr, 0);

    int result = 0;
    if (strcmp(op, "==") == 0) {
        result = clisp_chunk_cmp(first, second);
    }

    if (strcmp(op, "!=") == 0) {
        result = !clisp_chunk_cmp(first, second);
    }

    clisp_expr_delete(expr);
    return clisp_chunk_bool(result);
}

clisp_chunk_t*
clisp_builtin_cmp_eq(clisp_chunk_expr_t* expr) {
    return clisp_builtin_cmp(expr, "==");
}

clisp_chunk_t*
clisp_builtin_cmp_ne(clisp_chunk_expr_t* expr) {
    return clisp_builtin_cmp(expr, "!=");
}