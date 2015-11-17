#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include "token.h"
#include "environment.h"
#include "ast.h"

void clisp_builtin_load_functions(clisp_env_t* env);

clisp_token_t* clisp_builtin_arithmetic(clisp_env_t* env, clisp_token_t* token, char* op);
clisp_token_t* clisp_builtin_arithmetic_add(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_sub(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_mul(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_div(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_arithmetic_mod(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_list_create(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_head(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_tail(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_eval(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_builtin_list_join(clisp_env_t* env, clisp_token_t* token);

clisp_token_t* clisp_builtin_define(clisp_env_t* env, clisp_token_t* token);

#endif
