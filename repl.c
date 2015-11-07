
#include <mpc.h>
#include <editline/readline.h>
#include <editline/history.h>

static char input[2048];


typedef struct {
    int type;
    long number;
    int err;
} lval;

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };


lval lval_num(long x) {
    lval v;
    v.type = LVAL_NUM;
    v.number = x;
    return v;
}

lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v) {

    switch(v.type) {
        case LVAL_NUM: printf("%li", v.number); break;

        case LVAL_ERR:

            if (v.err == LERR_DIV_ZERO) {
                printf("Error: Division by Zero!");
            }
            if (v.err == LERR_BAD_OP) {
                printf("Error: Invalid Operator!");
            }
            if (v.err == LERR_BAD_NUM) {
                printf("Error: Invalid Number!");
            }
            break;
    }

}
void lval_println(lval v) { lval_print(v); putchar('\n'); }

lval eval_op(lval x, char* op, lval y) {

    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y; }

    if (strcmp(op, "+") == 0) { return lval_num(x.number + y.number); }
    if (strcmp(op, "-") == 0) { return lval_num(x.number - y.number); }
    if (strcmp(op, "*") == 0) { return lval_num(x.number * y.number); }
    if (strcmp(op, "/") == 0) {
        return y.number == 0
            ? lval_err(LERR_DIV_ZERO)
            : lval_num(x.number / y.number);
    }

    return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {

    if (strstr(t->tag, "number")) {
        errno = 0;
        long x = strtol(t->contents, NULL, 10);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    char* op = t->children[1]->contents;

    lval x = eval(t->children[2]);

    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}

int main(int argc, char** argv) {

    puts("Lisp version 0.0.1\n");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lisp = mpc_new("lisp");

    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                        \
        number   : /-?[0-9]+/;                               \
        operator : '+' | '-' | '*' | '/' ;                   \
        expr     : <number> | '(' <operator> <expr>+ ')' ;   \
        lisp     : /^/ <operator> <expr>+ /$/ ;              \
    ",
    Number, Operator, Expr, Lisp);

    while (1) {

        char* input = readline("lisp> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lisp, &r)) {
            lval result = eval(r.output);
            lval_println(result);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.output);
            mpc_err_delete(r.output);
        }

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, Lisp);

    return 0;

}
