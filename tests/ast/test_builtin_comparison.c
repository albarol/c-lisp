
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_comparison) {

    PT_TEST(test_compare_eq_returns_false) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(eq 2 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_eq_returns_true) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(eq 2 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_eq_using_lists_returns_true) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(eq [1 2 3] [1 2 3])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_ne_returns_true) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(ne 2 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_ne_returns_false) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(ne 2 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_different_types_returns_false) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(eq 2 \"2\")", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_invalid_params) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(eq)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}