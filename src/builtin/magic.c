
#include <builtin/magic.h>

clisp_chunk_t*
clisp_builtin_magic_exit(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_expr_assert_type(chunk, chunk->type, CLISP_NUMBER);
    exit((int) chunk->value.number);
}