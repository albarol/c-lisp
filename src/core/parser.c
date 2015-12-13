
#include <parser.h>

clisp_grammar_t*
clisp_grammar_new() {
    clisp_grammar_t* grammar = malloc(sizeof(clisp_grammar_t));

    grammar->Comment = mpc_new("comment");
    grammar->Boolean = mpc_new("boolean");
    grammar->Number = mpc_new("number");
    grammar->String = mpc_new("string");
    grammar->Symbol = mpc_new("symbol");
    grammar->List = mpc_new("list");
    grammar->Sexpr = mpc_new("sexpr");
    grammar->Expr = mpc_new("expr");
    grammar->Lisp = mpc_new("lisp");


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
    ", grammar->Comment, grammar->Boolean, grammar->Number, grammar->String, grammar->Symbol, grammar->List,
       grammar->Sexpr, grammar->Expr, grammar->Lisp);

    return grammar;
}

void
clisp_grammar_delete(clisp_grammar_t* grammar) {
    mpc_cleanup(8, grammar->Comment, grammar->Number, grammar->String, grammar->Symbol, grammar->Sexpr, grammar->Expr, grammar->Lisp);
    free(grammar);
}

void
clisp_process(char* input, clisp_env_t* env, bool print) {
    if (Grammar == NULL) {
        Grammar = clisp_grammar_new();
    }
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Grammar->Lisp, &r)) {
        clisp_expr_t* expr = clisp_read_ast(r.output);
        clisp_chunk_t* result = clisp_eval_ast(expr, env);
        if (print)
            clisp_print_writeln(result);
        clisp_chunk_delete(result);
        mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.output);
        mpc_err_delete(r.output);
    }
}