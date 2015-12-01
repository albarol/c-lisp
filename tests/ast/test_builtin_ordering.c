
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_ordering) {

    PT_TEST(test_compare_gt) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(> 2 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.number == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_gte) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(>= 2 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.number == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_lt) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(< 2 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.number == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_compare_lte) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(<= 2 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.number == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_invalid_number) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(<= 2 \"2\")", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Incorrect type of argument. Got: String, Expected: Number");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_invalid_params) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(<=)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Incorrect number of arguments. Got: 0, Expected: 2");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}