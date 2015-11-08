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

void lval_del(lval* val);
lval* lval_add(lval* v, lval* x);
lval* lval_num(long number);
lval* lval_err(char* error);
lval* lval_sym(char* symbols);
lval* lval_sexpr(void);
lval* lval_pop(lval* val, int index);
lval* lval_take(lval* val, int index);


#endif
