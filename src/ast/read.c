
#include <ast.h>


clisp_expr_t*
clisp_read_ast(mpc_ast_t* ast) {

    if (strcmp(ast->tag, ">") == 0) { return clisp_read_ast(ast->children[1]); }

    clisp_expr_t* expr = clisp_expr_new();

    if (strstr(ast->tag, "number")) { clisp_expr_append(expr, clisp_read_number(ast)); }
    if (strstr(ast->tag, "symbol")) { clisp_expr_append(expr, clisp_chunk_symbol(ast->contents)); }
    if (strstr(ast->tag, "string")) { clisp_expr_append(expr, clisp_read_string(ast)); }
    if (strstr(ast->tag, "boolean")) { clisp_expr_append(expr, clisp_read_bool(ast)); }
    if (strstr(ast->tag, "list")) { clisp_expr_append(expr, clisp_read_list(ast)); }
    if (strstr(ast->tag, "sexpr")) { clisp_expr_append(expr, clisp_read_sexpr(ast)); }

    return expr;
}


clisp_chunk_t*
clisp_read_number(mpc_ast_t* ast) {
    errno = 0;
    float x = strtof(ast->contents, NULL);
    return errno != ERANGE
           ? clisp_chunk_number(x)
           : clisp_chunk_error("Invalid number");

}

clisp_chunk_t*
clisp_read_string(mpc_ast_t* ast) {
    ast->contents[strlen(ast->contents)-1] = '\0';
    char* unescaped = alloc(strlen(ast->contents+1) + 1);
    strcpy(unescaped, ast->contents+1);
    unescaped = mpcf_unescape(unescaped);
    clisp_chunk_t* str = clisp_chunk_str(unescaped);
    free(unescaped);
    return str;
}

clisp_chunk_t*
clisp_read_bool(mpc_ast_t* ast) {
    if (strcmp(ast->contents, "#t") == 0) {
        return clisp_chunk_bool(1);
    } else {
        return clisp_chunk_bool(0);
    }
}

clisp_chunk_t*
clisp_read_list(mpc_ast_t* ast) {
   clisp_chunk_t* chunk = clisp_chunk_list();

    for (int i = 0; i < ast->children_num; i++) {
        if (strcmp(ast->children[i]->contents, "[") == 0) { continue; }
        if (strcmp(ast->children[i]->contents, "]") == 0) { continue; }
        if (strcmp(ast->children[i]->tag, "regex") == 0) { continue; }
        clisp_expr_join(chunk->value.list, clisp_read_ast(ast->children[i]));
    }
    return chunk;
}

clisp_chunk_t*
clisp_read_sexpr(mpc_ast_t* ast) {

    clisp_chunk_t* expr = clisp_chunk_expr();

    for (int i = 0; i < ast->children_num; i++) {
        if (strcmp(ast->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(ast->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(ast->children[i]->tag, "regex") == 0) { continue; }
        clisp_expr_join(expr->value.list, clisp_read_ast(ast->children[i]));
    }
    return expr;
}
