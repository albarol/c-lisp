
#include "ast.h"

clisp_chunk_t*
clisp_ast_read(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) { return clisp_ast_read_number(t); }
    if (strstr(t->tag, "symbol")) { return clisp_chunk_symbol(t->contents); }
    if (strstr(t->tag, "string")) { return clisp_ast_read_str(t); }

    clisp_chunk_t* token = NULL;
    if (strcmp(t->tag, ">") == 0) { token = clisp_chunk_sexpr(); }
    if (strcmp(t->tag, "comment")) { token = clisp_chunk_sexpr(); }
    if (strstr(t->tag, "sexpr")) { token = clisp_chunk_sexpr(); }
    if (strstr(t->tag, "qexpr")) { token = clisp_chunk_qexpr(); }

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

clisp_chunk_t*
clisp_ast_read_number(mpc_ast_t* t) {
    errno = 0;
    float x = strtof(t->contents, NULL);
    return errno != ERANGE
        ? clisp_chunk_number(x)
        : clisp_chunk_error("Invalid number");
}

clisp_chunk_t*
clisp_ast_read_str(mpc_ast_t* t) {
    t->contents[strlen(t->contents)-1] = '\0';

    char* unescaped = malloc(strlen(t->contents+1) + 1);
    strcpy(unescaped, t->contents+1);
    unescaped = mpcf_unescape(unescaped);
    clisp_chunk_t* str = clisp_chunk_str(unescaped);
    free(unescaped);
    return str;
}

clisp_chunk_t*
clisp_ast_eval(clisp_env_t* env, clisp_chunk_t* token) {
    if (token->type == CLISP_SYMBOL) {
        clisp_chunk_t* looked = clisp_env_get(env, token);
        clisp_token_del(token);
        return looked;
    }
    if (token->type == CLISP_ATOM) {
        return clisp_ast_eval_sexpr(env, token);
    }
    return token;
}

clisp_chunk_t*
clisp_ast_eval_sexpr(clisp_env_t* env, clisp_chunk_t* token) {

    for (int i = 0; i < token->count; i++) {
        token->tokens[i] = clisp_ast_eval(env, token->tokens[i]);
    }

    for (int i = 0; i < token->count; i++) {
        if (token->tokens[i]->type == CLISP_ERROR) {
            return clisp_token_take(token, i);
        }
    }

    if (token->count == 0) { return token; }
    if (token->count == 1) { return clisp_token_take(token, 0); }

    clisp_chunk_t* func = clisp_token_pop(token, 0);
    if (func->type != CLISP_FUNCTION) {
        clisp_token_del(token);
        clisp_token_del(func);
        return clisp_chunk_error("First element is not a function");
    }

    clisp_chunk_t* result = clisp_token_call(env, func, token);
    clisp_token_del(func);
    return result;
}
