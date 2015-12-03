
#include <ast.h>
#include "builtin.h"



clisp_chunk_t*
clisp_builtin_cond_if(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 3);

    clisp_chunk_t* cond = clisp_expr_pop(expr, 0);

    if (cond->type == CLISP_EXPR) {
        cond = clisp_eval_ast(cond->value.list, env);
    }

    clisp_expr_assert_type(expr, cond->type, CLISP_BOOL);

    if (cond->value.boolean) {
        clisp_expr_remove(expr, 1);
    } else {
        clisp_expr_remove(expr, 0);
    }

    clisp_chunk_delete(cond);
    return clisp_eval_ast(expr, env);
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