#ifndef __CLISP_DATA__
#define __CLISP_DATA__

#include <stdlib.h>
#include <string.h>

#define LASSERT(args, cond, err) \
    if (!(cond)) { lval_del(args); return lval_err(err); }


typedef struct {
    int type;
    long number;

    char* err;
    char* sym;

    int count;
    struct lval** cell;
} lval;

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };

void lval_del(lval* val);
lval* lval_add(lval* v, lval* x);
lval* lval_num(long number);
lval* lval_err(char* error);
lval* lval_sym(char* symbols);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_pop(lval* val, int index);
lval* lval_take(lval* val, int index);
lval* lval_join(lval* x, lval* y);

#endif
