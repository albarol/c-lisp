
#include <types.h>


clisp_expr_t*
clisp_expr_new() {
    clisp_expr_t* expr = malloc(sizeof(clisp_expr_t));
    expr->count = 0;
    expr->chunks = NULL;
    return expr;
}

clisp_expr_t*
clisp_expr_create(clisp_chunk_t* chunk) {
    clisp_expr_t* expr = clisp_expr_new();
    clisp_expr_append(expr, chunk);
    return expr;
}


void
clisp_expr_delete(clisp_expr_t* expr) {
    for (int i = 0; i < expr->count; i++)
        clisp_chunk_delete(expr->chunks[i]);
    free(expr);
}

clisp_expr_t*
clisp_expr_append(clisp_expr_t* expr, clisp_chunk_t* child) {
    expr->count++;
    expr->chunks = realloc(expr->chunks, sizeof(clisp_chunk_t*) * expr->count);
    expr->chunks[expr->count - 1] = child;
    return expr;
}

void
clisp_expr_remove(clisp_expr_t* expr, int position) {

    clisp_chunk_t* item = expr->chunks[position];

    memmove(&expr->chunks[position], &expr->chunks[position + 1],
            sizeof(clisp_chunk_t*) * (expr->count - position - 1));

    expr->count--;
    expr->chunks = realloc(expr->chunks, sizeof(clisp_chunk_t*) * (expr->count));
    clisp_chunk_delete(item);
}



clisp_chunk_t*
clisp_expr_pop(clisp_expr_t* expr, int position) {

    clisp_chunk_t* item = expr->chunks[position];

    memmove(&expr->chunks[position], &expr->chunks[position + 1],
            sizeof(clisp_chunk_t*) * (expr->count - position - 1));

    expr->count--;
    expr->chunks = realloc(expr->chunks, sizeof(clisp_chunk_t*) * (expr->count));

    return item;
}

clisp_chunk_t*
clisp_expr_take(clisp_expr_t* expr, int position) {
    clisp_chunk_t* item = clisp_expr_pop(expr, position);
    clisp_expr_delete(expr);
    return item;
}

clisp_expr_t*
clisp_expr_join(clisp_expr_t* first, clisp_expr_t* second) {
    while (second->count) {
        first = clisp_expr_append(first, clisp_expr_pop(second, 0));
    }

    clisp_expr_delete(second);
    return first;
}