#ifndef __CLISP_PARSER__
#define __CLISP_PARSER__

#include <mpc.h>

#include <types.h>
#include <ast.h>
#include <print.h>

struct clisp_grammar_t;
typedef struct clisp_grammar_t clisp_grammar_t;

struct clisp_grammar_t {
    mpc_parser_t* Comment;
    mpc_parser_t* Boolean;
    mpc_parser_t* Number;
    mpc_parser_t* String;
    mpc_parser_t* Symbol;
    mpc_parser_t* List;
    mpc_parser_t* Sexpr;
    mpc_parser_t* Expr;
    mpc_parser_t* Lisp;
};

static clisp_grammar_t* Grammar;

clisp_grammar_t* clisp_grammar_new();
void clisp_grammar_delete(clisp_grammar_t* grammar);

void clisp_process(char* input, clisp_env_t* env, bool print);

#endif