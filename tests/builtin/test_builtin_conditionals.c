#include "ptest.h"

#include "../../src/builtin.h"
#include "../helper.h"

PT_SUITE(suite_builtin_conditionals) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_chunk_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(1));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_expr_append(expr, clisp_chunk_number(4));
        clisp_chunk_t* chunk = clisp_builtin_cond_if(expr);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 3);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_if_returns_first_expr) {
        clisp_chunk_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(0));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_expr_append(expr, clisp_chunk_number(4));
        clisp_chunk_t* chunk = clisp_builtin_cond_if(expr);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
    }
}