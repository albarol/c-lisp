#include <types.h>
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_conditionals) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(if (eq 2 2) (+ 2 3) (+ 2 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_if_returns_second_expr) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(if (ne 2 2) (+ 2 3) (+ 2 2))", env);
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

    PT_TEST(test_def_should_permits_recursive_call) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(def (fact n) (if (eq n 0) (1) (* n (fact (- n 1)))))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.list->count == 1);
        PT_ASSERT_STR_EQ(env->symbols[env->count - 1], "fact");

        clisp_expr_t* ast_result = read_entry("(fact 3)", env);
        clisp_chunk_t* result = clisp_eval_ast(ast_result, env);
        PT_ASSERT(result->type == CLISP_NUMBER);
        PT_ASSERT(result->value.number == 6);

        clisp_chunk_delete(result);
        clisp_expr_delete(ast_result);
        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_for_to_call_function_many_times) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(for (i [1 2 3 4]) (display i))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NIL);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_cond_should_execute_first_true_statement) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(cond ((> 3 4) 1) ((> 3 1) 3) (#t 2))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 3);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_lambda_high_order_function) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(def (map f n) (f n))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.list->count == 2);
        PT_ASSERT_STR_EQ(env->symbols[env->count - 1], "map");

        clisp_expr_t* ast_result = read_entry("(map (fn (t) (+ t 1)) 3)", env);
        clisp_chunk_t* result = clisp_eval_ast(ast_result, env);
        PT_ASSERT(result->type == CLISP_NUMBER);
        PT_ASSERT(result->value.number == 4);

        clisp_chunk_delete(result);
        clisp_expr_delete(ast_result);
        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}