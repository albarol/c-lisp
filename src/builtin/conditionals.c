
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_cond_if(clisp_chunk_expr_t* expr) {
    clisp_expr_assert_count(expr, 3);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_BOOL);

    clisp_chunk_t* cond = clisp_expr_pop(expr, 0);
    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_pop(expr, 0);

    if (cond->value.number == 1) {
        clisp_chunk_delete(cond);
        clisp_chunk_delete(second);
        return first;
    } else {
        clisp_chunk_delete(cond);
        clisp_chunk_delete(first);
        return second;
    }
}