#include "ptest.h"

#include "../src/types.h"


PT_SUITE(suite_expr) {

    PT_TEST(test_append_chunk_in_expr) {
        clisp_chunk_t* expr = clisp_chunk_sexpr();

        clisp_expr_append(expr, clisp_chunk_symbol("x"));

        PT_ASSERT_STR_EQ(expr->value.expr.chunks[0]->value.string, "x");
        PT_ASSERT(expr->value.expr.count == 1);

        clisp_chunk_delete(expr);
    }

    PT_TEST(test_pop_chunk_in_expr) {
        clisp_chunk_t* expr = clisp_chunk_sexpr();

        clisp_expr_append(expr, clisp_chunk_symbol("x"));
        clisp_chunk_t* symbol = clisp_expr_pop(expr, 0);

        PT_ASSERT_STR_EQ(symbol->value.string, "x");
        PT_ASSERT(expr->value.expr.count == 0);

        clisp_chunk_delete(expr);
        clisp_chunk_delete(symbol);
    }

    PT_TEST(test_take_chunk_in_expr) {
        clisp_chunk_t* expr = clisp_chunk_sexpr();

        clisp_expr_append(expr, clisp_chunk_symbol("x"));
        clisp_chunk_t* symbol = clisp_expr_take(expr, 0);

        PT_ASSERT_STR_EQ(symbol->value.string, "x");

        clisp_chunk_delete(symbol);
    }

    PT_TEST(test_join_two_chunks) {
        clisp_chunk_t* first = clisp_chunk_sexpr();
        clisp_chunk_t* second = clisp_chunk_sexpr();
        clisp_expr_append(second, clisp_chunk_symbol("x"));

        first = clisp_expr_join(first, second);

        clisp_chunk_t* symbol = clisp_expr_pop(first, 0);
        PT_ASSERT_STR_EQ(symbol->value.string, "x");

        clisp_chunk_delete(symbol);
        clisp_chunk_delete(first);
    }
}