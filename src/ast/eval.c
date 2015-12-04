
#include <ast.h>
#include <types.h>

clisp_chunk_t*
clisp_eval_ast(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);
    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
    }

    if (chunk->type == CLISP_EXPR) {
        return clisp_eval_ast(chunk->value.list, env);
    } else if(chunk->type == CLISP_FUNCTION_C) {
        if (chunk->value.builtin.ftype == CLISP_FUNCTION_LAZY) {
            return clisp_eval_ast_builtin_lazy(chunk, expr, env);
        }
        return clisp_eval_ast_builtin_eager(chunk, expr, env);
    } else if (chunk->type == CLISP_FUNCTION) {
        return clisp_eval_ast_function(chunk, expr, env);
    }

    return chunk;
}

clisp_chunk_t*
clisp_eval_ast_builtin_eager(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_t* params = clisp_expr_new();
    while (expr->count) {
        clisp_expr_append(params, clisp_eval_ast(expr, env));
    }
    clisp_chunk_t* result = func->value.builtin.body(params, env);

    clisp_expr_delete(expr);
    return result;
}

clisp_chunk_t*
clisp_eval_ast_builtin_lazy(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env) {
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
        if (param->type == CLISP_EXPR) {
            param = clisp_eval_ast(param->value.list, env);
        }
        clisp_env_put(chunk->value.func.env, chunk->value.func.args->value.list->chunks[i], param);
    }
    chunk->value.func.env->parent = env;
    return clisp_eval_ast(call, chunk->value.func.env);
}