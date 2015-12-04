
#include <builtin.h>
#include <print.h>

clisp_chunk_t*
clisp_builtin_magic_repr(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);

    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
    }

    clisp_print_write(chunk);
    clisp_chunk_delete(chunk);
    return clisp_chunk_nil();
}