#ifndef __CLISP_BUILTIN_STRING__
#define __CLISP_BUILTIN_STRING__

#include <types.h>
#include <error.h>
#include <ctype.h>

clisp_chunk_t* clisp_builtin_string_check_type(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_string_uppercase(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_string_lowercase(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_string_concat(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_string_split(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_string_length(clisp_expr_t* expr, clisp_env_t* env);

#endif