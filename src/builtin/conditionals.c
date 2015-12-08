
#include <ast.h>
#include <types.h>
#include "builtin.h"

clisp_chunk_t*
clisp_builtin_conditional_if(clisp_expr_t* expr, clisp_env_t* env) {
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
clisp_builtin_conditional_def(clisp_expr_t* expr, clisp_env_t* env) {
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

clisp_chunk_t*
clisp_builtin_conditional_for(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* error = NULL;
    clisp_chunk_t* iterator = clisp_expr_pop(expr, 0);
    clisp_expr_assert_count(iterator->value.list, 2);

    clisp_chunk_t* vars = clisp_chunk_expr();
    clisp_expr_append(vars->value.list, clisp_expr_pop(iterator->value.list, 0));
    clisp_chunk_t* args = clisp_expr_pop(iterator->value.list, 0);
    clisp_chunk_t* body = clisp_expr_pop(expr, 0);

    if (vars->value.list->count == 0 || vars->value.list->chunks[0]->type != CLISP_SYMBOL) {
        error = clisp_chunk_error("Invalid argument for iterator");
        goto cleanup;
    } else if (args->value.list->count == 0) {
        error = clisp_chunk_error("Invalid argument for iterator");
        goto cleanup;
    } else if (body->value.list->count == 0) {
        error = clisp_chunk_error("Invalid argument for body");
        goto cleanup;
    }

    clisp_env_t* local_env = clisp_env_new();
    local_env->parent = env;

    for (int i = 0; i < args->value.list->count; i++) {
        clisp_expr_t* call = clisp_expr_new();
        clisp_expr_append(call, clisp_chunk_copy(body));
        clisp_env_put(local_env, vars->value.list->chunks[0], args->value.list->chunks[i]);
        clisp_chunk_delete(clisp_eval_ast(call, local_env));
        clisp_expr_delete(call);
    }

    clisp_env_delete(local_env);

cleanup:
    clisp_chunk_delete(body);
    clisp_chunk_delete(args);
    clisp_chunk_delete(iterator);
    clisp_expr_delete(expr);
    if (error != NULL) {
        return error;
    } else {
        return clisp_chunk_nil();
    }
}

clisp_chunk_t*
clisp_builtin_conditional_cond(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* call = NULL;
    clisp_chunk_t* error = NULL;

    while(expr->count) {
        clisp_chunk_t* tree = clisp_expr_pop(expr, 0);
        clisp_chunk_t* cond = NULL;

        if (tree->type != CLISP_EXPR) {
            error = clisp_chunk_error("Invalid expression. It should be ((Boolean) Type)");
            goto cleanup;
        }

        cond = clisp_expr_pop(tree->value.list, 0);
        if (cond->type == CLISP_EXPR) {
            cond = clisp_eval_ast(cond->value.list, env);
        }

        if (cond->type != CLISP_BOOL) {
            error = clisp_chunk_error("Invalid argument type. Got: %s, Expected: %s",
                                      clisp_print_type_name(cond->type), clisp_print_type_name(CLISP_BOOL));
            goto cleanup;
        }

        if (cond->value.boolean) {
            call = tree->value.list->chunks[1];
            break;
        }

        cleanup:
            if (cond != NULL) {
                clisp_chunk_delete(cond);
            }
            clisp_chunk_delete(tree);
    }

    clisp_expr_delete(expr);
    if (call != NULL) {
        return clisp_eval_ast(clisp_expr_create(call), env);
    }
    else if (error != NULL) {
        return error;
    }
    return clisp_chunk_nil();
}
