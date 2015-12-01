
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_conditionals) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(if (== 2 2) (+ 2 3) (+ 2 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_if_returns_second_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_chunk_expr_t* ast = read_entry("(if (!= 2 2) (+ 2 3) (+ 2 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}