#ifndef __CLISP_AST__
#define __CLISP_AST__

#include <mpc.h>

#include "token.h"
#include "environment.h"
#include "builtin.h"

clisp_chunk_t* clisp_ast_read(mpc_ast_t* t);
clisp_chunk_t* clisp_ast_read_number(mpc_ast_t* t);
clisp_chunk_t* clisp_ast_read_str(mpc_ast_t* t);
clisp_chunk_t* clisp_ast_eval(clisp_env_t* env, clisp_chunk_t* token);
clisp_chunk_t* clisp_ast_eval_sexpr(clisp_env_t* env, clisp_chunk_t* token);
clisp_chunk_t* clisp_ast_call(clisp_env_t* env, clisp_chunk_t* f, clisp_chunk_t* args);

#endif
