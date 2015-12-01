
#include "ptest.h"

#include "../../src/builtin.h"
#include "../helper.h"

PT_SUITE(suite_builtin_math) {

    PT_TEST(test_add_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_add(expr);

        PT_ASSERT(result->value.number == 12);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_minus_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_sub(expr);

        PT_ASSERT(result->value.number == 8);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_negativate_number) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_expr_pop(expr, 1);
        clisp_chunk_t* result = clisp_builtin_math_sub(expr);

        PT_ASSERT(result->value.number == -10);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_mul_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mul(expr);

        PT_ASSERT(result->value.number == 20);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_div_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_div(expr);

        PT_ASSERT(result->value.number == 5);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_mod_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mod(expr);

        PT_ASSERT(result->value.number == 0);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_pow_two_numbers) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(2, 3);
        clisp_chunk_t* result = clisp_builtin_math_pow(expr);

        PT_ASSERT(result->value.number == 8);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_throws_error_invalid_number) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_symbol("symbol"));
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_math_add(expr);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Symbol, Expected: Number");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_division_by_zero) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 0);
        clisp_chunk_t* result = clisp_builtin_math_div(expr);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Division By Zero!");

        clisp_chunk_delete(result);
    }
}