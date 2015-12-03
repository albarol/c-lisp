
#include <mpc.h>
#include <editline/readline.h>
#include <editline/history.h>

#include "types.h"
#include "print.h"
#include "ast.h"
#include "builtin.h"

static char input[2048];

int main(int argc, char** argv) {

    puts("CLisp version 0.2.0\n");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Comment = mpc_new("comment");
    mpc_parser_t* Boolean = mpc_new("boolean");
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* String = mpc_new("string");
    mpc_parser_t* Symbol = mpc_new("symbol");
    mpc_parser_t* List = mpc_new("list");
    mpc_parser_t* Sexpr = mpc_new("sexpr");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lisp = mpc_new("lisp");


    mpca_lang(MPCA_LANG_DEFAULT, "                                                    \
        comment  : /;(\\\\.|[^\"])*/;                                                \
        boolean  : /(#t|#f)/;                                                         \
        number   : /-?[0-9]+(\\.[0-9]+)?/;                                            \
        string   : /\"(\\\\.|[^\"])*\"/ ;                                             \
        symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&\\^\\%\\?]+/ ;                           \
        list     : '[' <expr>* ']' ;                                                  \
        sexpr    : '(' <expr>* ')' ;                                                  \
        expr     : <comment> | <boolean> | <list> | <number> | <symbol> | <string> | <sexpr> ;   \
        lisp     : /^/ <expr>* /$/ ;                                                  \
    ", Comment, Boolean, Number, String, Symbol, List, Sexpr, Expr, Lisp);


    clisp_env_t* env = clisp_env_new();
    clisp_builtin_load_functions(env);

    while (1) {

        char* input = readline("clisp> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lisp, &r)) {
            clisp_expr_t* expr = clisp_read_ast(r.output);
            clisp_chunk_t* result = clisp_eval_ast(expr, env);
            clisp_print_writeln(result);
            clisp_chunk_delete(result);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.output);
            mpc_err_delete(r.output);
        }

        free(input);
    }

    mpc_cleanup(8, Comment, Number, String, Symbol, Sexpr, Expr, Lisp);
    clisp_env_delete(env);

    return 0;
}
