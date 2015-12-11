#ifndef __CLISP_BUILTIN_BOOL__
#define __CLISP_BUILTIN_BOOL__

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_bool_check_type(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_not(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_and(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_or(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_xor(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_nand(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_nor(clisp_expr_t* expr, clisp_env_t* env);

clisp_chunk_t* clisp_builtin_bool_equal(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_bool_not_equal(clisp_expr_t* expr, clisp_env_t* env);

#endif
