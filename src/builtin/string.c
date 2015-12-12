
#include <builtin/string.h>

clisp_chunk_t*
clisp_builtin_string_check_type(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(chunk->type == CLISP_STRING);

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_string_uppercase(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_STRING);

    int total = strlen(chunk->value.string);
    for (int i = 0; i < total; i++){
        chunk->value.string[i] = toupper(chunk->value.string[i]);
    }

    return chunk;
}

clisp_chunk_t*
clisp_builtin_string_lowercase(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_STRING);

    int total = strlen(chunk->value.string);
    for (int i = 0; i < total; i++){
        chunk->value.string[i] = tolower(chunk->value.string[i]);
    }

    return chunk;
}

clisp_chunk_t*
clisp_builtin_string_concat(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert(expr, expr->count > 0, "Invalid number of arguments. Got: 0, Excepted: > 0");
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* first = clisp_expr_pop(expr, 0);

    clisp_chunk_t* chunk = NULL;
    while (expr->count) {
        chunk = clisp_expr_pop(expr, 0);

        if (chunk->type != CLISP_STRING) {
            clisp_chunk_delete(first);
            clisp_expr_delete(expr);
            clisp_chunk_t* error = clisp_chunk_error(TYPE_ERROR, clisp_print_type_name(chunk->type),
                                                     clisp_print_type_name(CLISP_STRING));
            clisp_chunk_delete(chunk);
            return error;
        }

        strcat(first->value.string, chunk->value.string);
    }
    clisp_chunk_delete(chunk);
    clisp_expr_delete(expr);

    return first;
}

clisp_chunk_t*
clisp_builtin_string_split(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);
    clisp_chunk_t* delimiter = clisp_expr_take(expr, 0);

    char* parts = strtok(chunk->value.string, delimiter->value.string);
    clisp_chunk_t* result = clisp_chunk_list();

    while (parts != NULL) {
        clisp_expr_append(result->value.list, clisp_chunk_str(parts));
        parts = strtok (NULL, delimiter->value.string);
    }

    clisp_chunk_delete(chunk);
    clisp_chunk_delete(delimiter);

    return result;
}

