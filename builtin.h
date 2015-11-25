#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include "token.h"
#include "environment.h"
#include "ast.h"
#include "error.h"

void clisp_builtin_load_functions(clisp_env_t* env);

clisp_token_t* clisp_builtin_arithmetic(clisp_env_t* env, clisp_token_t* token, char* op);
clisp_token_t* clisp_builtin_arithmetic_add(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_sub(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_mul(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_div(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_mod(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_ord(clisp_env_t* env, clisp_token_t* token, char* op);
clisp_token_t* clisp_builtin_ord_gt(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_ord_gte(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_ord_lt(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_ord_lte(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_cmp(clisp_env_t* env, clisp_token_t* token, char* op);
clisp_token_t* clisp_builtin_cmp_eq(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_cmp_ne(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_cmp_if(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_list_create(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_head(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_tail(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_join(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_eval(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_var_set(clisp_env_t* env, clisp_token_t* token, char* function);
clisp_token_t* clisp_builtin_define(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_assign(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_lambda(clisp_env_t* env, clisp_token_t* token);

#endif
