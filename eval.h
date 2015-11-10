#ifndef __CLISP_EVAL__
#define __CLISP_EVAL__

#include <mpc.h>

#include "data.h"
#include "builtin.h"

lval* lval_read(mpc_ast_t* t);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_eval_sexpr(lenv* e, lval* v);
lval* lval_eval(lenv* e, lval* v);

#endif
