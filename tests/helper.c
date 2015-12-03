
#include "helper.h"

clisp_env_t*
create_basic_env() {
    clisp_env_t* env = clisp_env_new();
    clisp_builtin_load_functions(env);
    clisp_env_put(env, clisp_chunk_symbol("five"), clisp_chunk_number(5));
    return env;
}

clisp_expr_t*
create_expr_with_two_numbers(float first, float second) {
    clisp_expr_t* expr = clisp_expr_new();
    clisp_expr_append(expr, clisp_chunk_number(first));
    clisp_expr_append(expr, clisp_chunk_number(second));
    return expr;
}

clisp_expr_t*
read_entry(char* input, clisp_env_t* env) {
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
        comment  : /\;(\\\\.|[^\"])*/;                                                \
        boolean  : /(#t|#f)/;                                                         \
        number   : /-?[0-9]+(\\.[0-9]+)?/;                                            \
        string   : /\"(\\\\.|[^\"])*\"/ ;                                             \
        symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&\\^\\%\\?]+/ ;                           \
        list     : '[' <expr>* ']' ;                                                  \
        sexpr    : '(' <expr>* ')' ;                                                  \
        expr     : <comment> | <boolean> | <list> | <number> | <symbol> | <string> | <sexpr> ;   \
        lisp     : /^/ <expr>* /$/ ;                                                  \
    ", Comment, Boolean, Number, String, Symbol, List, Sexpr, Expr, Lisp);

    mpc_result_t r;
    mpc_parse("<stdin>", input, Lisp, &r);


    return clisp_read_ast(r.output);
}