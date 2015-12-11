#ifndef __CLISP_BUILTIN_IO__
#define __CLISP_BUILTIN_IO__

#include <types.h>
#include <error.h>
#include <print.h>

clisp_chunk_t* clisp_builtin_io_display(clisp_expr_t* expr, clisp_env_t* env);

#endif