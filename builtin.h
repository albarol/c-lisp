#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include "data.h"
#include "eval.h"

lval* builtin(lval* a, char* func);
lval* builtin_op(lval* a, char* op);
lval* builtin_list(lval* a);
lval* builtin_head(lval* a);
lval* builtin_tail(lval* a);
lval* builtin_eval(lval* a);
lval* builtin_join(lval* a);

#endif
