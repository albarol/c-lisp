
#include "ast.h"


clisp_chunk_t*
clisp_eval_ast(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);

    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
    }

    if (chunk->type == CLISP_EXPR) {
        return clisp_eval_ast(chunk->value.list, env);
    } else if(chunk->type == CLISP_FUNCTION_C) {
        if (strcmp(chunk->value.builtin.name, "def") == 0) {
            return clisp_eval_ast_conditionals(chunk, expr, env);
        }
        return clisp_eval_ast_builtin(chunk, expr, env);
    } else if (chunk->type == CLISP_FUNCTION) {
        return clisp_eval_ast_function(chunk, expr, env);

    }
    return chunk;
}

clisp_chunk_t*
clisp_eval_ast_builtin(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_t* params = clisp_expr_new();
    while (expr->count) {
        clisp_expr_append(params, clisp_eval_ast(expr, env));
    }
    clisp_chunk_t* result = func->value.builtin.body(params, env);
    return result;
}

clisp_chunk_t*
clisp_eval_ast_conditionals(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env) {
    return func->value.builtin.body(expr, env);
}

clisp_chunk_t*
clisp_eval_ast_function(clisp_chunk_t* chunk, clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_t* call = clisp_expr_new();
    clisp_expr_append(call, chunk->value.func.body);

    if (chunk->value.func.args->value.list->count != expr->count) {
        return clisp_chunk_error("Incorrect number of arguments. Got: %li, Expected: %li",
                                 expr->count, chunk->value.func.args->value.list->count);
    }

    for (int i = 0; i < chunk->value.func.args->value.list->count; i++) {
        clisp_chunk_t* param = clisp_expr_pop(expr, 0);
        clisp_env_put(chunk->value.func.env, chunk->value.func.args->value.list->chunks[i], param);
    }
    chunk->value.func.env->parent = env;
    return clisp_eval_ast(call, chunk->value.func.env);
}