
#include "ptest.h"

#include <builtin.h>
#include <types.h>


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

    /**
     * Test create list
     */
    PT_TEST(test_create_list) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_list_create(expr, env);

        PT_ASSERT(result->type == CLISP_LIST);
        PT_ASSERT(result->value.list->count == 1);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_create_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_create(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: > 0");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_create_throws_invalid_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_nil());

        clisp_chunk_t* result = clisp_builtin_list_create(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Type: Nil is not supported");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test head
     */
    PT_TEST(test_list_head) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2"};
        clisp_expr_t* chunk = create_list(argv, 2);

        clisp_chunk_t* head = clisp_builtin_list_head(chunk, env);

        PT_ASSERT(head->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(head->value.string, "item1");

        clisp_chunk_free(head);
        clisp_env_free(env);
    }

    PT_TEST(test_list_head_throws_empty_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {};
        clisp_expr_t* chunk = create_list(argv, 0);
        clisp_chunk_t* head = clisp_builtin_list_head(chunk, env);

        PT_ASSERT(head->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(head->value.string, "List is empty");

        clisp_chunk_free(head);
        clisp_env_free(env);
    }

    PT_TEST(test_list_head_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_create(clisp_chunk_bool(false));
        clisp_chunk_t* result = clisp_builtin_list_head(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Boolean, Expected: List");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test tail
     */
    PT_TEST(test_list_tail_element_from_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk, env);

        PT_ASSERT(tail->type == CLISP_LIST);
        PT_ASSERT(tail->value.list->count == 2);

        clisp_chunk_free(tail);
        clisp_env_free(env);
    }

    PT_TEST(test_list_tail_throws_empty_list) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {};
        clisp_expr_t* chunk = create_list(argv, 0);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk, env);

        PT_ASSERT(tail->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(tail->value.string, "List is empty");

        clisp_chunk_free(tail);
        clisp_env_free(env);
    }

    /**
     * Test empty
     */
    PT_TEST(test_list_empty_should_be_false) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* result = clisp_builtin_list_empty(chunk, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_empty_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_empty(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_empty_throws_invalid_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_list_empty(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: List");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test length
     */
    PT_TEST(test_list_length) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* result = clisp_builtin_list_length(chunk, env);

        PT_ASSERT(result->type == CLISP_NUMBER);
        PT_ASSERT(result->value.number == 3);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_list_length_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_length(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_list_length_throws_invalid_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_list_length(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: List");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test append
     */
    PT_TEST(test_list_append) {
        clisp_env_t* env = clisp_env_new();
        char *argv[] = {"item1", "item2", "item3"};
        clisp_expr_t* expr = create_list(argv, 3);
        clisp_expr_append(expr, clisp_chunk_str("item4"));

        clisp_chunk_t* result = clisp_builtin_list_append(expr, env);

        PT_ASSERT(result->type == CLISP_LIST);
        PT_ASSERT(result->value.list->count == 4);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_list_append_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_append(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_list_append_throws_invalid_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(5));
        clisp_expr_append(expr, clisp_chunk_number(1));

        clisp_chunk_t* result = clisp_builtin_list_append(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: List");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test cons
     */
    PT_TEST(test_list_cons) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_expr_append(expr, clisp_chunk_bool(false));

        clisp_chunk_t* result = clisp_builtin_list_cons(expr, env);

        PT_ASSERT(result->type == CLISP_LIST);
        PT_ASSERT(result->value.list->count == 2);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_list_cons_throws_empty_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* chunk = clisp_expr_new();

        clisp_chunk_t* result = clisp_builtin_list_cons(chunk, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }
}