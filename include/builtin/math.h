#ifndef __CLISP_BUILTIN_MATH__
#define __CLISP_BUILTIN_MATH__

#include <math.h>

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_math_add(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_sub(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_mul(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_div(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_mod(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_pow(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_round(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_floor(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_ceil(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_sqrt(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_log(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_log10(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_sin(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_cos(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_tan(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_abs(clisp_expr_t* expr, clisp_env_t* env);

#endif