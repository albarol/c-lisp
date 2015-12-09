#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include <math.h>

#include "ast.h"
#include "types.h"
#include "error.h"
#include "print.h"

void clisp_builtin_load_functions(clisp_env_t* env);

clisp_chunk_t* clisp_builtin_math(clisp_expr_t* expr, clisp_env_t* env, char* op);
clisp_chunk_t* clisp_builtin_math_add(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_sub(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_mul(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_div(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_mod(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_math_pow(clisp_expr_t* expr, clisp_env_t* env);

clisp_chunk_t* clisp_builtin_ord(clisp_expr_t* expr, clisp_env_t* env, char* op);
clisp_chunk_t* clisp_builtin_ord_gt(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_ord_gte(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_ord_lt(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_ord_lte(clisp_expr_t* expr, clisp_env_t* env);

clisp_chunk_t* clisp_builtin_cmp(clisp_expr_t* expr, clisp_env_t* env, char* op);
clisp_chunk_t* clisp_builtin_cmp_eq(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_cmp_ne(clisp_expr_t* expr, clisp_env_t* env);

clisp_chunk_t* clisp_builtin_list_head(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_tail(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_join(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_is_list(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_length(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_empty(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_create(clisp_expr_t* expr, clisp_env_t* env);


clisp_chunk_t* clisp_builtin_conditional_if(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_conditional_def(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_conditional_for(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_conditional_cond(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_conditional_fn(clisp_expr_t* expr, clisp_env_t* env);


clisp_chunk_t* clisp_builtin_magic_display(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_magic_exit(clisp_expr_t* expr, clisp_env_t* env);

#endif
