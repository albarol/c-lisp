#ifndef __CLISP_BUILTIN_IO__
#define __CLISP_BUILTIN_IO__

#include <stdio.h>
#include <stdlib.h>

#include <types.h>
#include <error.h>
#include <print.h>
#include <ast.h>
#include <parser.h>
#include <utils.h>

clisp_chunk_t* clisp_builtin_io_display(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_io_print(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_io_load(clisp_expr_t* expr, clisp_env_t* env);

#endif