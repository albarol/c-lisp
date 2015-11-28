#include "builtin.h"


/**
 * Load all builtin functions
 */
void
clisp_builtin_load_functions(clisp_env_t* env) {

//    clisp_env_put_function(env, "+", clisp_builtin_math_add);
//    clisp_env_put_function(env, "-", clisp_builtin_math_sub);
//    clisp_env_put_function(env, "*", clisp_builtin_math_mul);
//    clisp_env_put_function(env, "/", clisp_builtin_math_div);
//    clisp_env_put_function(env, "%", clisp_builtin_math_mod);
//    clisp_env_put_function(env, "^", clisp_builtin_math_pow);
//
//    clisp_env_put_function(env, "list", clisp_builtin_list_create);
//    clisp_env_put_function(env, "head", clisp_builtin_list_head);
//    clisp_env_put_function(env, "tail", clisp_builtin_list_tail);
//    clisp_env_put_function(env, "join", clisp_builtin_list_join);
//
//    clisp_env_put_function(env, "eval", clisp_builtin_eval);
//    clisp_env_put_function(env, "def", clisp_builtin_define);
//    clisp_env_put_function(env, "=", clisp_builtin_assign);
//    clisp_env_put_function(env, "\\",  clisp_builtin_lambda);
//
//    clisp_env_put_function(env, ">",  clisp_builtin_ord_gt);
//    clisp_env_put_function(env, ">=",  clisp_builtin_ord_gte);
//    clisp_env_put_function(env, "<",  clisp_builtin_ord_lt);
//    clisp_env_put_function(env, "<=",  clisp_builtin_ord_lte);
//
//    clisp_env_put_function(env, "==",  clisp_builtin_cmp_eq);
//    clisp_env_put_function(env, "!=",  clisp_builtin_cmp_ne);
//    clisp_env_put_function(env, "if",  clisp_builtin_cmp_if);
}


/**
 * Define functions for create functions
 */
clisp_chunk_t*
clisp_builtin_var_set(clisp_env_t* env, clisp_chunk_t* chunk, char* function) {

    clisp_chunk_t* child = chunk->value.expr.chunks[0];
    clisp_assert_type(chunk, child->type, TOKEN_QEXPRESSION);

    for (int i = 0; i < child->value.expr.count; i++) {
        clisp_assert(chunk, child->value.expr.chunks[i]->type, CLISP_SYMBOL)
    }

    clisp_assert(chunk, child->value.expr.count == chunk->value.expr.count - 1,
                 "Function cannot define incorrect "
                         "number of values to symbols")

    for (int i = 0; i < child->value.expr.count; i++) {
        if (strcmp(function, "def") == 0) {
            clisp_env_put(env, child->value.expr.chunks[i], chunk->value.expr.chunks[i+1]);
        }
    }

    clisp_chunk_delete(chunk);
    return clisp_chunk_sexpr();
}

clisp_chunk_t*
clisp_builtin_define(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_var_set(env, token, "def");
}

clisp_chunk_t*
clisp_builtin_lambda(clisp_env_t* env, clisp_chunk_t* chunk) {

    clisp_assert_count(chunk, 2);

    clisp_chunk_t* args = clisp_expr_pop(chunk, 0);
    clisp_chunk_t* body = clisp_expr_pop(chunk, 0);

    clisp_assert_type(chunk, args->type, TOKEN_QEXPRESSION);
    clisp_assert_type(chunk, args->type, TOKEN_QEXPRESSION);

    for (int i = 0; i < args->value.expr.count; i++) {
        clisp_chunk_t* child = args->value.expr.chunks[i];
        clisp_assert(chunk, child->type = CLISP_SYMBOL,
                     "Cannot define non-symbol. Got: %s, Expected: %s",
                     clisp_print_type_name(child->type), clisp_print_type_name(CLISP_SYMBOL));
    }

    clisp_chunk_delete(chunk);
    return clisp_chunk_function(args, body);
}
