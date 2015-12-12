#ifndef __CLISP_BUILTIN_SYNTACTIC__
#define __CLISP_BUILTIN_SYNTACTIC__

#include <types.h>
#include <error.h>
#include <ast.h>

clisp_chunk_t* clisp_builtin_syntactic_if(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_def(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_for(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_cond(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_when(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_unless(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_syntactic_lambda(clisp_expr_t* expr, clisp_env_t* env);

#endif