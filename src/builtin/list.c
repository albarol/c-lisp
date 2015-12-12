
#include <builtin/list.h>

clisp_chunk_t*
clisp_builtin_list_create(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert(expr, expr->count > 0,
                      "Incorrect number of arguments. Got: 0, Expected: > 0");

    int valid_types = CLISP_BOOL|CLISP_SYMBOL|
                      CLISP_NUMBER|CLISP_LIST|CLISP_STRING;
    for (int i = 0; i < expr->count; i++) {
        clisp_expr_assert(expr, (expr->chunks[i]->type & valid_types) > 0,
                          "Incorrect type of argument. Type: %s is not supported", clisp_print_type_name(expr->chunks[i]->type));
    }

    clisp_chunk_t* chunk = clisp_chunk_list();
    clisp_expr_join(chunk->value.list, expr);
    return chunk;
}

clisp_chunk_t*
clisp_builtin_list_head(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_LIST)
    clisp_chunk_assert(chunk, chunk->value.list->count > 0, "List is empty")
    return clisp_expr_take(chunk->value.list, 0);
}

clisp_chunk_t*
clisp_builtin_list_tail(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_LIST)
    clisp_chunk_assert(chunk, chunk->value.list->count > 0, "List is empty")
    clisp_chunk_delete(clisp_expr_pop(chunk->value.list, 0));
    return chunk;
}

clisp_chunk_t*
clisp_builtin_list_check_type(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    return clisp_chunk_bool(chunk->type == CLISP_LIST);
}

clisp_chunk_t*
clisp_builtin_list_empty(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_LIST);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(chunk->value.list->count == 0);

    clisp_chunk_delete(chunk);
    return result;
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

clisp_chunk_t*
clisp_builtin_list_append(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_LIST);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_TYPE);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);
    clisp_chunk_t* second = clisp_expr_take(expr, 0);

    if (second->type == CLISP_LIST) {
        clisp_expr_join(first->value.list, second->value.list);
    } else {
        clisp_expr_append(first->value.list, second);
    }
    return first;
}

clisp_chunk_t*
clisp_builtin_list_cons(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_TYPE);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_TYPE);

    clisp_chunk_t* result = clisp_chunk_list();

    while (expr->count) {
        clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);

        if (chunk->type == CLISP_LIST) {
            clisp_expr_join(result->value.list, chunk->value.list);
        }
        else {
            clisp_expr_append(result->value.list, chunk);
        }
    }
    clisp_expr_delete(expr);
    return result;
}