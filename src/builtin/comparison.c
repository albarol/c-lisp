
#include "../builtin.h"

clisp_chunk_t*
clisp_builtin_cmp(clisp_env_t* env, clisp_chunk_t* chunk, char* op) {
    clisp_assert_count(chunk, 2);

    clisp_chunk_t* first = chunk->value.expr.chunks[0];
    clisp_chunk_t* second = chunk->value.expr.chunks[1];

    int result;
    if (strcmp(op, "==") == 0) {
        result = clisp_chunk_cmp(first, second);
    }

    if (strcmp(op, "!=") == 0) {
        result = !clisp_chunk_cmp(first, second);
    }
    clisp_chunk_delete(chunk);
    return clisp_chunk_number(result);
}

clisp_chunk_t*
clisp_builtin_cmp_eq(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_cmp(env, token, "==");
}

clisp_chunk_t*
clisp_builtin_cmp_ne(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_cmp(env, token, "!=");
}

clisp_chunk_t*
clisp_builtin_cmp_if(clisp_env_t* env, clisp_chunk_t* chunk) {
    clisp_assert_count(chunk, 3);
    clisp_assert_type(chunk, chunk->value.expr.chunks[0]->type, CLISP_NUMBER);
    clisp_assert_type(chunk, chunk->value.expr.chunks[1]->type, TOKEN_QEXPRESSION);
    clisp_assert_type(chunk, chunk->value.expr.chunks[2]->type, TOKEN_QEXPRESSION);

    clisp_chunk_t* new_token;
    chunk->value.expr.chunks[1]->type = CLISP_ATOM;
    chunk->value.expr.chunks[2]->type = CLISP_ATOM;

    if (chunk->value.expr.chunks[0]->value.number) {
  //      new_token = clisp_ast_eval(env, clisp_expr_pop(chunk, 1));
    } else {
//        new_token = clisp_ast_eval(env, clisp_expr_pop(chunk, 2));
    }

    clisp_chunk_delete(chunk);
    return new_token;
}