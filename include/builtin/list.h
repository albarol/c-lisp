#ifndef __CLISP_BUILTIN_LIST__
#define __CLISP_BUILTIN_LIST__

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_list_head(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_tail(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_append(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_check_type(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_length(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_empty(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_create(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_list_cons(clisp_expr_t* expr, clisp_env_t* env);

#endif