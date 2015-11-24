
#include "ast.h"

clisp_token_t*
clisp_ast_read(mpc_ast_t* t) {

    if (strstr(t->tag, "number")) { return clisp_ast_read_number(t); }
    if (strstr(t->tag, "symbol")) { return clisp_token_symbol(t->contents); }

    clisp_token_t* token = NULL;
    if (strcmp(t->tag, ">") == 0) { token = clisp_token_sexpr(); }
    if (strstr(t->tag, "sexpr")) { token = clisp_token_sexpr(); }
    if (strstr(t->tag, "qexpr")) { token = clisp_token_qexpr(); }

    for (int i = 0; i < t->children_num; i++) {
        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
        if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
        if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
        token = clisp_token_append(token, clisp_ast_read(t->children[i]));
    }
    return token;
}

clisp_token_t*
clisp_ast_read_number(mpc_ast_t* t) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE
        ? clisp_token_number(x)
        : clisp_token_error("Invalid number");
}

clisp_token_t*
clisp_ast_eval(clisp_env_t* env, clisp_token_t* token) {
    if (token->type == TOKEN_SYMBOL) {
        clisp_token_t* looked = clisp_env_get(env, token);
        clisp_token_del(token);
        return looked;
    }
    if (token->type == TOKEN_SEXPRESSION) {
        return clisp_ast_eval_sexpr(env, token);
    }
    return token;
}

clisp_token_t*
clisp_ast_eval_sexpr(clisp_env_t* env, clisp_token_t* token) {

    for (int i = 0; i < token->count; i++) {
        token->tokens[i] = clisp_ast_eval(env, token->tokens[i]);
    }

    for (int i = 0; i < token->count; i++) {
        if (token->tokens[i]->type == TOKEN_ERROR) {
            return clisp_token_take(token, i);
        }
    }

    if (token->count == 0) { return token; }
    if (token->count == 1) { return clisp_token_take(token, 0); }

    clisp_token_t* func = clisp_token_pop(token, 0);
    if (func->type != TOKEN_FUNCTION) {
        clisp_token_del(token);
        clisp_token_del(func);
        return clisp_token_error("First element is not a function");
    }

    clisp_token_t* result = clisp_token_call(env, func, token);
    clisp_token_del(func);
    return result;
}
