#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_builtin_magic) {

    PT_TEST(test_show_repr_of_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(1));
        clisp_chunk_t* chunk = clisp_builtin_magic_repr(expr, env);

        PT_ASSERT(chunk->type == CLISP_NIL);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_invalid_params_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(0));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_chunk_t* chunk = clisp_builtin_magic_repr(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Incorrect number of arguments. Got: 2, Expected: 1");

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }
}