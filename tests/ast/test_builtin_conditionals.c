
#include "ptest.h"

#include "../helper.h"
#include "../../src/types.h"

PT_SUITE(suite_ast_builtin_conditionals) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(if (== 2 2) (+ 2 3) (+ 2 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_if_returns_second_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(if (!= 2 2) (+ 2 3) (+ 2 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_def_should_return_function) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(def (sum a b) (+ a b))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.list->count == 2);
        PT_ASSERT_STR_EQ(env->symbols[env->count - 1], "sum");

        clisp_expr_t* ast_result = read_entry("(sum 1 2)", env);
        clisp_chunk_t* result = clisp_eval_ast(ast_result, env);
        PT_ASSERT(result->type == CLISP_NUMBER);
        PT_ASSERT(result->value.number == 3);

        clisp_chunk_delete(result);
        clisp_expr_delete(ast_result);
        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}