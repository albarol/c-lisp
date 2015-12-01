
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_math) {

    PT_TEST(test_sum_two_numbers) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(+ 1 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 2);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_negative_number) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("-1", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == -1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_sub_two_numbers) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(- 5 1)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_mul_two_numbers) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(* 5 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 10);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_div_two_numbers) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(/ 10 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_pow_number) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(^ 2 3)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 8);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_mod_number) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(% 10 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_throws_error_division_by_zero) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(/ 10 0)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Division By Zero!");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}