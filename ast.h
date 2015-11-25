#ifndef __CLISP_EVAL__
#define __CLISP_EVAL__

#include <mpc.h>

#include "token.h"
#include "environment.h"
#include "builtin.h"

clisp_token_t* clisp_ast_read(mpc_ast_t* t);
clisp_token_t* clisp_ast_read_number(mpc_ast_t* t);
clisp_token_t* clisp_ast_read_str(mpc_ast_t* t);
clisp_token_t* clisp_ast_eval(clisp_env_t* env, clisp_token_t* token);
clisp_token_t* clisp_ast_eval_sexpr(clisp_env_t* env, clisp_token_t* token);

#endif
