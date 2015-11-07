#ifndef __CLISP_EVAL__
#define __CLISP_EVAL__

#include <mpc.h>

#include "data.h"

lval* lval_read(mpc_ast_t* t);
lval* lval_read_num(mpc_ast_t* t);

#endif
