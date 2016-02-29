

#include <builtin/syntactic.h>


clisp_chunk_t*
clisp_builtin_syntactic_if(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 3);

    clisp_chunk_t* cond = clisp_expr_pop(expr, 0);

    if (cond->type == CLISP_EXPR) {
        cond = clisp_eval_ast(cond->value.list, env);
    }

    clisp_expr_assert_type(expr, cond->type, CLISP_BOOL);

    if (cond->value.boolean == true) {
        clisp_expr_remove(expr, 1);
    } else {
        clisp_expr_remove(expr, 0);
    }

    clisp_chunk_free(cond);
    return clisp_eval_ast(expr, env);
}

clisp_chunk_t*
clisp_builtin_syntactic_def(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* args = clisp_expr_pop(expr, 0);
    clisp_chunk_assert_type(args, args->type, CLISP_EXPR);

    clisp_chunk_t* body = clisp_expr_take(expr, 0);

    for (int i = 0; i < args->value.list->count; i++) {
        clisp_chunk_assert_type(args, args->value.list->chunks[i]->type, CLISP_SYMBOL)
    }

    clisp_chunk_t* name = clisp_expr_pop(args->value.list, 0);
    clisp_chunk_t* func = clisp_chunk_function(args, body);
    clisp_env_put(env, name, func);

    clisp_chunk_free(name);
    return func;
}

clisp_chunk_t*
clisp_builtin_syntactic_for(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* error = NULL;
    clisp_chunk_t* iterator = clisp_expr_pop(expr, 0);
    clisp_chunk_assert_type(iterator, iterator->type, CLISP_EXPR)
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
        clisp_chunk_free(clisp_eval_ast(call, local_env));
        clisp_expr_free(call);
    }

    clisp_env_free(local_env);

cleanup:
clisp_chunk_free(body);
    clisp_chunk_free(args);
    clisp_chunk_free(iterator);
    clisp_expr_free(expr);
    if (error != NULL) {
        return error;
    } else {
        return clisp_chunk_nil();
    }
}

clisp_chunk_t*
clisp_builtin_syntactic_cond(clisp_expr_t* expr, clisp_env_t* env) {

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
                clisp_chunk_free(cond);
            }
        clisp_chunk_free(tree);
    }

    clisp_expr_free(expr);
    if (call != NULL) {
        return clisp_eval_ast(clisp_expr_create(call), env);
    }
    else if (error != NULL) {
        return error;
    }
    return clisp_chunk_nil();
}


clisp_chunk_t*
clisp_builtin_syntactic_when(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* call = NULL;
    clisp_chunk_t* error = NULL;

    while(expr->count) {
        clisp_chunk_t* tree = clisp_expr_pop(expr, 0);
        clisp_chunk_t* cond = NULL;

        if (tree->type != CLISP_EXPR) {
            error = clisp_chunk_error("Invalid expression. It should be ((Boolean) Type)");
        }

        cond = clisp_expr_pop(tree->value.list, 0);
        if (cond->type == CLISP_EXPR) {
            cond = clisp_eval_ast(cond->value.list, env);
        }

        if (cond->type != CLISP_BOOL) {
            error = clisp_chunk_error("Invalid argument type. Got: %s, Expected: %s",
                                      clisp_print_type_name(cond->type), clisp_print_type_name(CLISP_BOOL));
        }

        if (cond->value.boolean) {
            call = tree->value.list->chunks[1];
            clisp_eval_ast(clisp_expr_create(call), env);
        }

        clisp_chunk_free(cond);
        clisp_chunk_free(tree);
    }
    clisp_expr_free(expr);

    if (error != NULL) {
        return error;
    }
    return clisp_chunk_nil();
}

clisp_chunk_t*
clisp_builtin_syntactic_unless(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_chunk_t* call = NULL;
    clisp_chunk_t* error = NULL;

    while(expr->count) {
        clisp_chunk_t* tree = clisp_expr_pop(expr, 0);
        clisp_chunk_t* cond = NULL;

        if (tree->type != CLISP_EXPR) {
            error = clisp_chunk_error("Invalid expression. It should be ((Boolean) Type)");
        }

        cond = clisp_expr_pop(tree->value.list, 0);
        if (cond->type == CLISP_EXPR) {
            cond = clisp_eval_ast(cond->value.list, env);
        }

        if (cond->type != CLISP_BOOL) {
            error = clisp_chunk_error("Invalid argument type. Got: %s, Expected: %s",
                                      clisp_print_type_name(cond->type), clisp_print_type_name(CLISP_BOOL));
        }

        if (!cond->value.boolean) {
            call = tree->value.list->chunks[1];
            clisp_eval_ast(clisp_expr_create(call), env);
        }

        clisp_chunk_free(cond);
        clisp_chunk_free(tree);
    }
    clisp_expr_free(expr);

    if (error != NULL) {
        return error;
    }
    return clisp_chunk_nil();
}

clisp_chunk_t*
clisp_builtin_syntactic_lambda(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_expr_assert_count(expr, 2);

    clisp_chunk_t* args = clisp_expr_pop(expr, 0);
    clisp_chunk_t* body = clisp_expr_take(expr, 0);

    if ((args->type & (CLISP_EXPR|CLISP_NIL)) == 0) {
        clisp_chunk_free(args);
        clisp_chunk_free(body);
        return clisp_chunk_error("Invalid argument type. Got: %s, Expected: Expression", clisp_print_type_name(args->type));
    }

    clisp_chunk_t* func = clisp_chunk_function(args, body);
    func->value.func.env->parent = env;
    return func;
}

clisp_chunk_t*
clisp_builtin_syntactic_type(clisp_expr_t* expr, clisp_env_t* env) {

    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_str(clisp_print_type_name(chunk->type));

    clisp_chunk_free(chunk);
    return result;
}
