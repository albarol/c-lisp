
#include "ptest.h"

#include "../src/builtin.h"


clisp_chunk_t*
create_two_numbers(float first, float second) {
    clisp_chunk_t* expr = clisp_chunk_sexpr();
    clisp_expr_append(expr, clisp_chunk_number(first));
    clisp_expr_append(expr, clisp_chunk_number(second));

    return expr;
}


PT_SUITE(suite_builtin_math) {

    PT_TEST(test_add_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_add(env, expr);

        PT_ASSERT(result->value.number == 12);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_minus_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_sub(env, expr);

        PT_ASSERT(result->value.number == 8);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_mul_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mul(env, expr);

        PT_ASSERT(result->value.number == 20);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_div_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_div(env, expr);

        PT_ASSERT(result->value.number == 5);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_mod_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_math_mod(env, expr);

        PT_ASSERT(result->value.number == 0);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_pow_two_numbers) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(2, 2);
        clisp_chunk_t* result = clisp_builtin_math_pow(env, expr);

        PT_ASSERT(result->value.number == 4);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_negative_number) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = clisp_chunk_sexpr();
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_math_sub(env, expr);

        PT_ASSERT(result->value.number == -5);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_invalid_number) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = clisp_chunk_sexpr();
        clisp_expr_append(expr, clisp_chunk_symbol("symbol"));
        clisp_expr_append(expr, clisp_chunk_number(5));

        clisp_chunk_t* result = clisp_builtin_math_add(env, expr);

        PT_ASSERT_STR_EQ(result->value.string, "Cannot operate on non-number!");
        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_division_by_zero) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* expr = create_two_numbers(10, 0);
        clisp_chunk_t* result = clisp_builtin_math_div(env, expr);

        PT_ASSERT_STR_EQ(result->value.string, "Division By Zero!");
        PT_ASSERT(result->type == CLISP_ERROR);

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }
}