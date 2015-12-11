#ifndef __CLISP_BUILTIN_NUMBER__
#define __CLISP_BUILTIN_NUMBER__

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_number_check_type(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_is_zero(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_is_positive(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_is_negative(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_is_even(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_is_odd(clisp_expr_t* expr, clisp_env_t* env);

clisp_chunk_t* clisp_builtin_number_ordering_gt(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_ordering_gte(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_ordering_lt(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_number_ordering_lte(clisp_expr_t* expr, clisp_env_t* env);

#endif