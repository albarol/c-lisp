//
//#include "ast.h"
//
//clisp_chunk_t*
//clisp_ast_read(mpc_ast_t* t) {
//    if (strstr(t->tag, "number")) { return clisp_ast_read_number(t); }
//    if (strstr(t->tag, "symbol")) { return clisp_chunk_symbol(t->contents); }
//    if (strstr(t->tag, "string")) { return clisp_ast_read_str(t); }
//
//    clisp_chunk_t* token = NULL;
//    if (strcmp(t->tag, ">") == 0) { token = clisp_chunk_sexpr(); }
//    if (strcmp(t->tag, "comment")) { token = clisp_chunk_sexpr(); }
//    if (strstr(t->tag, "sexpr")) { token = clisp_chunk_sexpr(); }
//    if (strstr(t->tag, "qexpr")) { token = clisp_chunk_qexpr(); }
//
//    for (int i = 0; i < t->children_num; i++) {
//        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
//        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
//        if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
//        if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
//        if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
//        token = clisp_expr_append(token, clisp_ast_read(t->children[i]));
//    }
//    return token;
//}
//
//clisp_chunk_t*
//clisp_ast_read_number(mpc_ast_t* t) {
//    errno = 0;
//    float x = strtof(t->contents, NULL);
//    return errno != ERANGE
//        ? clisp_chunk_number(x)
//        : clisp_chunk_error("Invalid number");
//}
//
//clisp_chunk_t*
//clisp_ast_read_str(mpc_ast_t* t) {
//    t->contents[strlen(t->contents)-1] = '\0';
//
//    char* unescaped = malloc(strlen(t->contents+1) + 1);
//    strcpy(unescaped, t->contents+1);
//    unescaped = mpcf_unescape(unescaped);
//    clisp_chunk_t* str = clisp_chunk_str(unescaped);
//    free(unescaped);
//    return str;
//}
//
//clisp_chunk_t*
//clisp_ast_eval(clisp_env_t* env, clisp_chunk_t* token) {
//    if (token->type == CLISP_SYMBOL) {
//        clisp_chunk_t* looked = clisp_env_get(env, token);
//        clisp_chunk_delete(token);
//        return looked;
//    }
//    if (token->type == CLISP_ATOM) {
//        return clisp_ast_eval_sexpr(env, token);
//    }
//    return token;
//}
//
//clisp_chunk_t*
//clisp_ast_eval_sexpr(clisp_env_t* env, clisp_chunk_t* token) {
//
//    for (int i = 0; i < token->value.expr.count; i++) {
//        token->value.expr.chunks[i] = clisp_ast_eval(env, token->value.expr.chunks[i]);
//    }
//
//    for (int i = 0; i < token->value.expr.count; i++) {
//        if (token->value.expr.chunks[i]->type == CLISP_ERROR) {
//            return clisp_expr_take(token, i);
//        }
//    }
//
//    if (token->value.expr.count == 0) { return token; }
//    if (token->value.expr.count == 1) { return clisp_expr_take(token, 0); }
//
//    clisp_chunk_t* func = clisp_expr_pop(token, 0);
//    if (func->type & (CLISP_FUNCTION|CLISP_FUNCTION_C)) {
//        clisp_chunk_t* result = clisp_ast_call(env, func, token);
//        clisp_chunk_delete(func);
//        return result;
//    }
//
//    clisp_chunk_delete(token);
//    clisp_chunk_delete(func);
//    return clisp_chunk_error("First element is not a function");
//}
//
//clisp_chunk_t*
//clisp_ast_call(clisp_env_t* env, clisp_chunk_t* f, clisp_chunk_t* args) {
//
////    if (f->type == CLISP_FUNCTION_C) { return f->value.builtin(env, args); }
//
//    int given = args->value.expr.count;
//    int total = f->value.func.args->value.expr.count;
//
//    while (args->value.expr.count) {
//
//        if (f->value.func.args->value.expr.count == 0) {
//            clisp_chunk_delete(args);
//            return clisp_chunk_error("Function passed too many arguments. "
//                                             "Got: %i, Expected: %i", given, total);
//        }
//
//        clisp_chunk_t* symbol = clisp_expr_pop(f->value.func.args, 0);
//        clisp_chunk_t* token = clisp_expr_pop(args, 0);
//
//        clisp_env_put(f->value.func.env, symbol, token);
//        clisp_chunk_delete(symbol);
//        clisp_chunk_delete(token);
//    }
//
//    clisp_chunk_delete(args);
//
//    if (f->value.func.args->value.expr.count == 0) {
//
//        f->value.func.env->parent = env;
//        return clisp_builtin_eval(f->value.func.env,
//                                  clisp_expr_append(clisp_chunk_sexpr(), clisp_chunk_copy(f->value.func.body)));
//    } else {
//        return clisp_chunk_copy(f);
//    }
//}