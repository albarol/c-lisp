#ifndef __CLISP_DATA__
#define __CLISP_DATA__

#include <stdlib.h>
#include <string.h>

typedef struct {
    int type;
    long number;

    char* err;
    char* sym;

    int count;
    struct lval** cell;
} lval;

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

void lval_del(lval* v);
lval* lval_add(lval* v, lval* x);
lval* lval_num(long number);
lval* lval_err(char* error);
lval* lval_sym(char* symbolss);
lval* lval_sexpr(void);

#endif
