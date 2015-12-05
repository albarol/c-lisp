#include <types.h>
#include "ptest.h"

#include "builtin.h"


clisp_expr_t*
create_list(char *argv[], int argc) {
    clisp_chunk_t* chunk = clisp_chunk_list();

    for (int i = 0; i < argc; i++) {
        clisp_expr_append(chunk->value.list, clisp_chunk_str(argv[i]));
    }

    clisp_expr_t* expr = clisp_expr_new();
    clisp_expr_append(expr, chunk);

    return expr;
}


PT_SUITE(suite_builtin_list) {

    PT_TEST(test_get_head_element_from_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2"};
        clisp_expr_t* chunk = create_list(argv, 2);

        clisp_chunk_t* head = clisp_builtin_list_head(chunk, env);

        PT_ASSERT(head->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(head->value.string, "item1");

        clisp_chunk_delete(head);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_head_throws_empty_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {};
        clisp_expr_t* chunk = create_list(argv, 0);
        clisp_chunk_t* head = clisp_builtin_list_head(chunk, env);

        PT_ASSERT(head->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(head->value.string, "List is empty");

        clisp_chunk_delete(head);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_tail_element_from_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk, env);

        PT_ASSERT(tail->type == CLISP_LIST);
        PT_ASSERT(tail->value.list->count == 2);

        clisp_chunk_delete(tail);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_tail_throws_empty_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {};
        clisp_expr_t* chunk = create_list(argv, 0);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk, env);

        PT_ASSERT(tail->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(tail->value.string, "List is empty");

        clisp_chunk_delete(tail);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_length_of_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* result = clisp_builtin_list_length(chunk, env);

        PT_ASSERT(result->type == CLISP_NUMBER);
        PT_ASSERT(result->value.number == 3);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_length_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_length(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_length_throws_invalid_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_list_length(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: List");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }
}