
#include "print.h"

void lval_print(lval* v) {
    switch(v->type) {
        case LVAL_NUM: printf("%li", v->number); break;
        case LVAL_ERR: printf("Error: %s", v->err); break;
        case LVAL_SYM: printf("%s", v->sym); break;
        case LVAL_SEXPR: lval_print_expr(v, '(', ')'); break;
        case LVAL_QEXPR: lval_print_expr(v, '{', '}'); break;
    }

}
void lval_println(lval* v) { lval_print(v); putchar('\n'); }

void lval_print_expr(lval* v, char open, char close) {
    putchar(open);

    for (int i = 0; i < v->count; i++) {

        lval_print((lval*) v->cell[i]);

        if (i != (v->count - 1)) {
            putchar(' ');
        }
    }

    putchar(close);
}
