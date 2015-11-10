#ifndef __CLISP_DATA__
#define __CLISP_DATA__

#include <stdlib.h>
#include <string.h>

#define LASSERT(args, cond, err) \
    if (!(cond)) { lval_del(args); return lval_err(err); }


struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

enum { LVAL_ERR, LVAL_NUM,   LVAL_SYM,
       LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };

typedef lval*(*lbuiltin)(lenv*, lval*);

struct lval {
    int type;
    long number;

    char* err;
    char* sym;
    lbuiltin func;

    int count;
    lval** cell;
};

struct lenv {
    int count;
    char** syms;
    lval** vals;
};


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
lval* lval_fun(lbuiltin func);
lval* lval_copy(lval* v);

lenv* lenv_new(void);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e, lval* k);
void lenv_put(lenv* e, lval* k, lval* v);

#endif
