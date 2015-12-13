#ifndef __CLISP_BUILTIN_EXCEPTION__
#define __CLISP_BUILTIN_EXCEPTION__

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_exception_error(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_exception_is_error(clisp_expr_t* expr, clisp_env_t* env);

#endif