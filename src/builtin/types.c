
#include <builtin.h>

clisp_chunk_t*
clisp_builtin_type_error(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_STRING);

    clisp_chunk_t* error = clisp_chunk_error(chunk->value.string);
    clisp_chunk_delete(chunk);
    return error;
}