#ifndef __CLISP_PRINT__
#define __CLISP_PRINT__

#include <stdio.h>

#include "data.h"

void lval_print(lval* v);
void lval_println(lval* v);
void lval_print_expr(lval* v, char open, char close);

#endif
