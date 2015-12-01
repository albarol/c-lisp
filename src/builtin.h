#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include <math.h>

#include "types.h"
#include "error.h"
#include "print.h"

void clisp_builtin_load_functions(clisp_env_t* env);

clisp_chunk_t* clisp_builtin_math(clisp_chunk_expr_t* expr, char* op);
clisp_chunk_t* clisp_builtin_math_add(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_math_sub(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_math_mul(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_math_div(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_math_mod(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_math_pow(clisp_chunk_expr_t* expr);

clisp_chunk_t* clisp_builtin_ord(clisp_chunk_expr_t* expr, char* op);
clisp_chunk_t* clisp_builtin_ord_gt(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_ord_gte(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_ord_lt(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_ord_lte(clisp_chunk_expr_t* expr);

clisp_chunk_t* clisp_builtin_cmp(clisp_chunk_expr_t* expr, char* op);
clisp_chunk_t* clisp_builtin_cmp_eq(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_cmp_ne(clisp_chunk_expr_t* expr);

clisp_chunk_t* clisp_builtin_list_head(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_list_tail(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_list_join(clisp_chunk_expr_t* expr);
clisp_chunk_t* clisp_builtin_list_eq(clisp_chunk_expr_t* expr);


clisp_chunk_t* clisp_builtin_cond_if(clisp_chunk_expr_t* expr);


clisp_chunk_t* clisp_builtin_eval(clisp_env_t* env, clisp_chunk_t* token);

//clisp_chunk_t* clisp_builtin_var_set(clisp_env_t* env, clisp_chunk_t* token, char* function);
//clisp_chunk_t* clisp_builtin_define(clisp_env_t* env, clisp_chunk_t* token);
////clisp_chunk_t* clisp_builtin_assign(clisp_env_t* env, clisp_chunk_t* token);
//clisp_chunk_t* clisp_builtin_lambda(clisp_env_t* env, clisp_chunk_t* token);

#endif
