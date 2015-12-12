
#include <builtin/magic.h>

clisp_chunk_t*
clisp_builtin_magic_exit(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 0);
    exit(0);
}