#include <types.h>
#include "builtin.h"

clisp_chunk_t*
clisp_builtin_list_head(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert(chunk, chunk->value.list->count > 0, "List is empty")

    while (chunk->value.list->count > 1) {
        clisp_chunk_delete(clisp_expr_pop(chunk->value.list, 1));
    }
    return clisp_expr_take(chunk->value.list, 0);
}

clisp_chunk_t*
clisp_builtin_list_tail(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert(chunk, chunk->value.list->count > 0, "List is empty")
    clisp_chunk_delete(clisp_expr_pop(chunk->value.list, 0));
    return chunk;
}

clisp_chunk_t*
clisp_builtin_list_join(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_LIST);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_TYPE);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_pop(expr, 0);

    if (second->type == CLISP_LIST) {
        clisp_expr_join(first->value.list, second->value.list);
    } else {
        clisp_expr_append(first->value.list, second);
    }
    return first;
}

clisp_chunk_t*
clisp_builtin_list_eq(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    int result = 0;
    if (chunk->type == CLISP_LIST) {
        result = 1;
    }
    return clisp_chunk_bool(result);
}

clisp_chunk_t*
clisp_builtin_list_length(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_LIST);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_number(chunk->value.list->count);

    clisp_chunk_delete(chunk);
    return result;
}