#ifndef __CLISP_AST__
#define __CLISP_AST__

#include "types.h"
#include "mpc.h"

clisp_chunk_t* clisp_eval_ast(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_eval_symbol(clisp_chunk_t* symbol, clisp_env_t* env);
clisp_chunk_t* clisp_eval_ast_builtin_eager(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_eval_ast_builtin_lazy(clisp_chunk_t* func, clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_eval_ast_function(clisp_chunk_t* chunk, clisp_expr_t* expr, clisp_env_t* env);

clisp_expr_t* clisp_read_ast(mpc_ast_t* ast);
clisp_chunk_t* clisp_read_number(mpc_ast_t* ast);
clisp_chunk_t* clisp_read_string(mpc_ast_t* ast);
clisp_chunk_t* clisp_read_bool(mpc_ast_t* ast);
clisp_chunk_t* clisp_read_list(mpc_ast_t* ast);
clisp_chunk_t* clisp_read_sexpr(mpc_ast_t* ast);

#endif