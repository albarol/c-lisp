
#include "builtin.h"


lval*
builtin(lval* a, char* func) {
    if (strcmp("list", func) == 0) { return builtin_list(a); }
    if (strcmp("head", func) == 0) { return builtin_head(a); }
    if (strcmp("tail", func) == 0) { return builtin_tail(a); }
    if (strcmp("eval", func) == 0) { return builtin_eval(a); }
    if (strcmp("join", func) == 0) { return builtin_join(a); }
    if (strstr("+-/*%", func)) { return builtin_op(a, func); }
    lval_del(a);
    return lval_err("Unknown Function!");
}

lval*
builtin_op(lval* a, char* op) {

    for (int i = 0; i < a->count; i++) {
        if (((lval *)a->cell[i])->type != LVAL_NUM) {
            lval_del(a);
            return lval_err("Cannot operate on non-number!");
        }
    }

    lval* x = lval_pop(a, 0);

    if ((strcmp(op, "-") == 0) && a->count == 0) {
        x->number = -x->number;
    }

    while (a->count > 0) {

        lval* y = lval_pop(a, 0);

        if (strcmp(op, "+") == 0) { x->number += y->number; }
        if (strcmp(op, "-") == 0) { x->number -= y->number; }
        if (strcmp(op, "*") == 0) { x->number *= y->number; }
        if (strcmp(op, "%") == 0) { x->number %= y->number; }
        if (strcmp(op, "/") == 0) {
            if (y->number == 0) {
                lval_del(x); lval_del(y);
                x = lval_err("Division By Zero!"); break;
            }
            x->number /= y->number;
        }

        lval_del(y);
    }

    lval_del(a); return x;
}


lval*
builtin_head(lval* a) {
    LASSERT(a, a->count == 1,
            "Function 'head' passed too many arguments!");
    lval* list = a->cell[0];
    LASSERT(a, list->type == LVAL_QEXPR,
            "Function 'head' passed incorrect types");
    LASSERT(a, list->count != 0,
            "Function 'head' passed {}!");

    list = lval_take(a, 0);

    while (list->count > 1) { lval_del(lval_pop(list, 1)); }
    return list;
}

lval*
builtin_tail(lval* a) {
    LASSERT(a, a->count == 1,
            "Function 'tail' passed too many arguments!");
    lval* list = a->cell[0];
    LASSERT(a, list->type == LVAL_QEXPR,
            "Function 'tail' passed incorrect types");
    LASSERT(a, list->count != 0,
            "Function 'tail' passed {}!");

    list = lval_take(a, 0);
    lval_del(lval_pop(list, 0));
    return list;
}

lval*
builtin_list(lval* a) {
    a->type = LVAL_QEXPR;
    return a;
}


lval*
builtin_eval(lval* a) {
    LASSERT(a, a->count == 1,
            "Function 'eval' passed too many arguments!");

    lval* v = a->cell[0];
    LASSERT(a, v->type == LVAL_QEXPR,
            "Function 'eval' passed incorrect types");

    v = lval_take(a, 0);
    v->type = LVAL_SEXPR;
    return lval_eval(v);
}

lval*
builtin_join(lval* a) {

    for (int i = 0; i < a->count; i++) {
        lval* child = a->cell[i];
        LASSERT(a, child->type == LVAL_QEXPR,
                "Function 'join' passed incorrect type");
    }

    lval* x = lval_pop(a, 0);

    while (a->count) {
        x = lval_join(x, lval_pop(a, 0));
    }

    lval_del(a);
    return x;
}
