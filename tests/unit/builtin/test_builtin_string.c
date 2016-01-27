
#include "ptest.h"

#include <types.h>
#include <builtin.h>

PT_SUITE(suite_builtin_string) {

    /**
     * Test check type
     */
    PT_TEST(test_string_check_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("String"));
        clisp_chunk_t* result = clisp_builtin_string_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_check_type_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_string_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test uppercase
     */
    PT_TEST(test_string_uppercase) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("string"));
        clisp_chunk_t* result = clisp_builtin_string_uppercase(expr, env);

        PT_ASSERT(result->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(result->value.string, "STRING");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_uppercase_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_string_uppercase(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_uppercase_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_string_uppercase(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test lowercase
     */
    PT_TEST(test_string_lowercase) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("STRING"));
        clisp_chunk_t* result = clisp_builtin_string_lowercase(expr, env);

        PT_ASSERT(result->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(result->value.string, "string");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_lowercase_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_string_lowercase(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_lowercase_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_string_lowercase(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test concat
     */
    PT_TEST(test_string_concat) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("Hello "));
        clisp_expr_append(expr, clisp_chunk_str("World"));
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(result->value.string, "Hello World");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_concat_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Invalid number of arguments. Got: 0, Excepted: > 0");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_concat_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_concat_intermediate_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("Hello "));
        clisp_expr_append(expr, clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test split
     */
    PT_TEST(test_string_split) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("Hello.World"));
        clisp_expr_append(expr, clisp_chunk_str("."));
        clisp_chunk_t* result = clisp_builtin_string_split(expr, env);

        PT_ASSERT(result->type == CLISP_LIST);
        PT_ASSERT(result->value.list->count == 2);
        PT_ASSERT_STR_EQ(result->value.list->chunks[0]->value.string, "Hello");
        PT_ASSERT_STR_EQ(result->value.list->chunks[1]->value.string, "World");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_split_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Invalid number of arguments. Got: 0, Excepted: > 0");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_string_split_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_expr_append(expr, clisp_chunk_str("."));
        clisp_chunk_t* result = clisp_builtin_string_concat(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_free(result);
        clisp_env_free(env);
    }
}