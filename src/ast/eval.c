
#include "../eval.h"

clisp_chunk_t*
clisp_eval_ast(clisp_chunk_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);

    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
    }

    if(chunk->type == CLISP_FUNCTION_C) {
        return clisp_eval_ast_builtin(chunk, expr, env);
    }
    return chunk;
}

clisp_chunk_t*
clisp_eval_ast_builtin(clisp_chunk_t* func, clisp_chunk_expr_t* expr, clisp_env_t* env) {
    clisp_chunk_expr_t* params = clisp_expr_new();
    while (expr->count) {
        clisp_expr_append(params, clisp_eval_ast(expr, env));
    }
    clisp_chunk_t* result = func->value.builtin.body(params);
    return result;
}