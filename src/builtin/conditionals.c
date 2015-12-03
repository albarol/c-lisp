
#include "builtin.h"

clisp_chunk_t*
clisp_builtin_cond_if(clisp_expr_t* expr, clisp_env_t* env) {
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

clisp_chunk_t*
clisp_builtin_cond_def(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* args = clisp_expr_pop(expr, 0);
    clisp_chunk_t* body = clisp_expr_pop(expr, 0);

    for (int i = 0; i < args->value.list->count; i++) {
        clisp_chunk_assert_type(args, args->value.list->chunks[i]->type, CLISP_SYMBOL)
    }

    clisp_chunk_t* name = clisp_expr_pop(args->value.list, 0);
    clisp_chunk_t* func = clisp_chunk_function(args, body);
    clisp_env_put(env, name, func);
    return func;
}