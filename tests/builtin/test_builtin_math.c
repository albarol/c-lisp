#include <types.h>
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_builtin_math) {

    /**
     * Test add
     */
    PT_TEST(test_math_add) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_add(expr, env);

        PT_ASSERT(result->value.number == 12);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_add_throws_error_invalid_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_symbol("symbol"));
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_math_add(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Symbol, Expected: Number");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_add_throws_error_invalid_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_math_add(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 1, Expected: 2");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }


    /**
     * Test sub
     */
    PT_TEST(test_math_sub) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_sub(expr, env);

        PT_ASSERT(result->value.number == 8);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_negative_number) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_expr_pop(expr, 1);
        clisp_chunk_t* result = clisp_builtin_math_sub(expr, env);

        PT_ASSERT(result->value.number == -10);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }


    /**
     * Test mul
     */
    PT_TEST(test_math_mul) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mul(expr, env);

        PT_ASSERT(result->value.number == 20);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
     * Test div
     */
    PT_TEST(test_math_div) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_div(expr, env);

        PT_ASSERT(result->value.number == 5);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_div_throws_error_division_by_zero) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 0);
        clisp_chunk_t* result = clisp_builtin_math_div(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Division By Zero!");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
    * Test mod
    */
    PT_TEST(test_math_mod) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mod(expr, env);

        PT_ASSERT(result->value.number == 0);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
    * Test pow
    */
    PT_TEST(test_math_pow) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = create_expr_with_two_numbers(2, 3);
        clisp_chunk_t* result = clisp_builtin_math_pow(expr, env);

        PT_ASSERT(result->value.number == 8);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    /**
    * Test math functions
    */
    PT_TEST(test_math_round) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(2.3));
        clisp_chunk_t* result = clisp_builtin_math_round(expr, env);

        PT_ASSERT(result->value.number == 2);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_round_throws_arg_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_chunk_t* result = clisp_builtin_math_round(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_round_throws_arg_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_nil());
        clisp_chunk_t* result = clisp_builtin_math_round(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Nil, Expected: Number");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_floor) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(2.8));
        clisp_chunk_t* result = clisp_builtin_math_floor(expr, env);

        PT_ASSERT(result->value.number == 2);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_ceil) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(2.8));
        clisp_chunk_t* result = clisp_builtin_math_ceil(expr, env);

        PT_ASSERT(result->value.number == 3);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_sqrt) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(4));
        clisp_chunk_t* result = clisp_builtin_math_sqrt(expr, env);

        PT_ASSERT(result->value.number == 2);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_log) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_math_log(expr, env);

        PT_ASSERT(result->value.number == 0);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_log10) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1000));
        clisp_chunk_t* result = clisp_builtin_math_log10(expr, env);

        PT_ASSERT(result->value.number == 3);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_cos) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(3.1415));
        clisp_chunk_t* result = clisp_builtin_math_cos(expr, env);

        PT_ASSERT(result->value.number == -1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_sin) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1.5708));
        clisp_chunk_t* result = clisp_builtin_math_sin(expr, env);

        PT_ASSERT(result->value.number == 1);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_tan) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(0.7854));
        clisp_chunk_t* result = clisp_builtin_math_tan(expr, env);

        PT_ASSERT(almost_equal(result->value.number, 1, 0.1));

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_math_tan) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(0.7854));
        clisp_chunk_t* result = clisp_builtin_math_tan(expr, env);

        PT_ASSERT(almost_equal(result->value.number, 1, 0.1));

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

}