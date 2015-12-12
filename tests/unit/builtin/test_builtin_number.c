#include <types.h>
#include "ptest.h"

#include "builtin.h"
#include "../helper.h"

PT_SUITE(suite_builtin_number) {

    /**
     * Test number check type
     */
    PT_TEST(test_number_check_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(5));
        clisp_chunk_t* result = clisp_builtin_number_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_check_type_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_number_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test zero
     */
    PT_TEST(test_number_zero) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(0));
        clisp_chunk_t* result = clisp_builtin_number_is_zero(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_zero_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_number_is_zero(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_zero_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_nil());
        clisp_chunk_t* result = clisp_builtin_number_is_zero(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Nil, Expected: Number");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test positive
     */
    PT_TEST(test_number_positive) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_number_is_positive(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test negative
     */
    PT_TEST(test_number_negative) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(-1));
        clisp_chunk_t* result = clisp_builtin_number_is_negative(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test odd
     */
    PT_TEST(test_number_negative) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_number_is_odd(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test even
     */
    PT_TEST(test_number_negative) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(2));
        clisp_chunk_t* result = clisp_builtin_number_is_even(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }


    /**
     * Test ordering
     */
    PT_TEST(test_number_gt) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_number_ordering_gt(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == 1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_gte) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 10);
        clisp_chunk_t* result = clisp_builtin_number_ordering_gte(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == 1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_lt) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(8, 10);
        clisp_chunk_t* result = clisp_builtin_number_ordering_lt(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == 1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_lte) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 10);
        clisp_chunk_t* result = clisp_builtin_number_ordering_lte(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == 1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_gt_throws_error_empty_expr) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* result = clisp_builtin_number_ordering_gt(clisp_expr_new(), env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_number_gt_throws_error_invalid_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_str("string1"));
        clisp_expr_append(expr, clisp_chunk_str("string2"));
        clisp_chunk_t* result = clisp_builtin_number_ordering_gt(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: String, Expected: Number");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }
}