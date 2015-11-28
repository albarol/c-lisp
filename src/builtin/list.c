
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_list_create(clisp_env_t* env, clisp_chunk_t* token) {
    token->type = TOKEN_QEXPRESSION;
    return token;
}

clisp_chunk_t*
clisp_builtin_list_head(clisp_env_t* env, clisp_chunk_t* chunk) {
    clisp_assert_count(chunk, 1);

    clisp_chunk_t* list = chunk->value.expr.chunks[0];
    clisp_assert(chunk, list->type == TOKEN_QEXPRESSION,
                 "Function 'head' passed incorrect types");
    clisp_assert(chunk, list->value.expr.count != 0,
                 "Function 'head' passed {}!");

    list = clisp_expr_pop(chunk, 0);

    while (list->value.expr.count > 1) {
        clisp_chunk_delete(clisp_expr_pop(list, 1));
    }
    return list;
}

clisp_chunk_t*
clisp_builtin_list_tail(clisp_env_t* env, clisp_chunk_t* chunk) {
    clisp_assert_count(chunk, 1);

    clisp_chunk_t* list = chunk->value.expr.chunks[0];
    clisp_assert(chunk, list->type == TOKEN_QEXPRESSION,
                 "Function 'tail' passed incorrect types");
    clisp_assert(chunk, list->value.expr.count != 0,
                 "Function 'tail' passed {}!");

    list = clisp_expr_take(chunk, 0);
    clisp_chunk_delete(clisp_expr_pop(list, 0));
    return list;
}

clisp_chunk_t*
clisp_builtin_list_join(clisp_env_t* env, clisp_chunk_t* chunk) {

    for (int i = 0; i < chunk->value.expr.count; i++) {
        clisp_chunk_t* child = chunk->value.expr.chunks[i];
        clisp_assert_type(chunk, child->type, TOKEN_QEXPRESSION);
    }

    clisp_chunk_t* child = clisp_expr_pop(chunk, 0);

    while (chunk->value.expr.count) {
        child = clisp_expr_join(child, clisp_expr_pop(chunk, 0));
    }

    clisp_chunk_delete(chunk);
    return child;
}


clisp_chunk_t*
clisp_builtin_eval(clisp_env_t* env, clisp_chunk_t* chunk) {
    clisp_assert_count(chunk, 1);

    clisp_chunk_t* child = chunk->value.expr.chunks[0];
    clisp_assert_type(chunk, child->type, TOKEN_QEXPRESSION)

    child = clisp_expr_take(chunk, 0);
    child->type = CLISP_ATOM;
    return child;
    //return clisp_ast_eval(env, child);
}