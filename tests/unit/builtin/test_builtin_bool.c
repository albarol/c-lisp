#include <types.h>
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_builtin_bool) {

    /**
     * Test CheckType
     */
    PT_TEST(test_bool_check_type_should_be_true) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(false));
        clisp_chunk_t* result = clisp_builtin_bool_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_check_type_should_be_false) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_nil());
        clisp_chunk_t* result = clisp_builtin_bool_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_check_type_throws_exception_count_args) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_bool_check_type(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test Not
     */
    PT_TEST(test_bool_not_invert_bool_value) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_chunk_t* result = clisp_builtin_bool_not(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_not_throws_invalid_args_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_bool_not(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_not_throws_invalid_args_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_bool_not(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test And
     */
    PT_TEST(test_bool_and) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_expr_append(expr, clisp_chunk_bool(true));
        clisp_chunk_t* result = clisp_builtin_bool_and(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_and_throws_invalid_args_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_bool_and(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_and_throws_invalid_args_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_bool_and(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test or
     */
    PT_TEST(test_bool_or) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_expr_append(expr, clisp_chunk_bool(false));
        clisp_chunk_t* result = clisp_builtin_bool_or(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test xor
     */
    PT_TEST(test_bool_xor) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_expr_append(expr, clisp_chunk_bool(true));
        clisp_chunk_t* result = clisp_builtin_bool_xor(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test nand
     */
    PT_TEST(test_bool_nand) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(true));
        clisp_expr_append(expr, clisp_chunk_bool(true));
        clisp_chunk_t* result = clisp_builtin_bool_nand(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test nor
     */
    PT_TEST(test_bool_nand) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(false));
        clisp_expr_append(expr, clisp_chunk_bool(false));
        clisp_chunk_t* result = clisp_builtin_bool_nor(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test eq
     */
    PT_TEST(test_bool_eq_should_be_true) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_expr_append(expr, clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_bool_equal(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_eq_should_be_false) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_expr_append(expr, clisp_chunk_number(2));
        clisp_chunk_t* result = clisp_builtin_bool_equal(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_eq_should_be_false_diff_types) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(false));
        clisp_expr_append(expr, clisp_chunk_number(2));
        clisp_chunk_t* result = clisp_builtin_bool_equal(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == false);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    PT_TEST(test_bool_eq_throws_args_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_bool(false));
        clisp_chunk_t* result = clisp_builtin_bool_equal(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }

    /**
     * Test not equal
     */
    PT_TEST(test_bool_ne_should_be_true) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(2));
        clisp_expr_append(expr, clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_bool_not_equal(expr, env);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.boolean == true);

        clisp_chunk_free(result);
        clisp_env_free(env);
    }
}