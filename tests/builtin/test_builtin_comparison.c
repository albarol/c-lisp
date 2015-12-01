#include "ptest.h"

#include "../../src/builtin.h"
#include "../helper.h"

PT_SUITE(suite_builtin_comparison) {

    PT_TEST(test_gt_returns_true) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 2);
        clisp_chunk_t* result = clisp_builtin_ord_gt(expr);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.number == 1);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_gt_returns_false) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(2, 10);
        clisp_chunk_t* result = clisp_builtin_ord_gt(expr);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.number == 0);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_gte_returns_true) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 10);
        clisp_chunk_t* result = clisp_builtin_ord_gte(expr);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.number == 1);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_lt_returns_true) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(8, 10);
        clisp_chunk_t* result = clisp_builtin_ord_lt(expr);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.number == 1);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_lte_returns_true) {
        clisp_chunk_expr_t* expr = create_expr_with_two_numbers(10, 10);
        clisp_chunk_t* result = clisp_builtin_ord_lte(expr);

        PT_ASSERT(result->type == CLISP_BOOL);
        PT_ASSERT(result->value.number == 1);

        clisp_chunk_delete(result);
    }

    PT_TEST(test_throws_error_empty_expr) {
        clisp_chunk_t* result = clisp_builtin_ord(clisp_expr_new(), ">");

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_delete(result);
    }

    PT_TEST(test_throws_error_invalid_type) {
        clisp_chunk_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_str("string1"));
        clisp_expr_append(expr, clisp_chunk_str("string2"));
        clisp_chunk_t* result = clisp_builtin_ord(expr, ">");

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: String, Expected: Number");

        clisp_chunk_delete(result);
    }
}