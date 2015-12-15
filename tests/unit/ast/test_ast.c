#include <types.h>
#include "ptest.h"

#include "../helper.h"


PT_SUITE(suite_ast) {

    PT_TEST(test_get_chunk_number) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("5", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_chunk_symbol) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("five", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_chunk_string) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("\"string\"", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(chunk->value.string, "string");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }

    PT_TEST(test_get_chunk_boolean_true) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("#t", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }

    PT_TEST(test_get_chunk_boolean_false) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("#f", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }

    PT_TEST(test_get_chunk_expr) {
        clisp_env_t* env = create_basic_env();

        clisp_expr_t* ast = read_entry("(+ 1 2)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 3);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }

    PT_TEST(test_get_complex_expr) {
        clisp_env_t* env = create_basic_env();

        clisp_expr_t* ast = read_entry("(+ 1 (+ 2 1))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }

    PT_TEST(test_get_expr_using_symbol) {
        clisp_env_t* env = create_basic_env();

        clisp_expr_t* ast = read_entry("(+ five (+ 2 1))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 8);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
        clisp_env_delete(env);
    }


    PT_TEST(test_get_chunk_list_of_numbers) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("[1 2 3 4]", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_LIST);
        PT_ASSERT(chunk->value.list->count == 4);
        PT_ASSERT(chunk->value.list->chunks[0]->value.number == 1);
        PT_ASSERT(chunk->value.list->chunks[1]->value.number == 2);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
    }

    PT_TEST(test_get_chunk_list_of_strings) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("[\"1\" \"2\"]", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_LIST);
        PT_ASSERT(chunk->value.list->count == 2);
        PT_ASSERT_STR_EQ(chunk->value.list->chunks[0]->value.string, "1");
        PT_ASSERT_STR_EQ(chunk->value.list->chunks[1]->value.string, "2");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
    }

    PT_TEST(test_should_return_error_when_function_not_found) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(join [1 2 3] [1 2 3])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string,  "Unbound Symbol!");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);;
    }

    PT_TEST(test_should_return_error_if_builtin_param_has_error) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(append (tail [1 2 3]) (head))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string,  "Incorrect type of argument. Got: Error, Expected: Any type");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
    }

    PT_TEST(test_should_run_function_with_empty_sexpr) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(list ())", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string,  "Incorrect type of argument. Type: Nil is not supported");

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
    }

    PT_TEST(test_one_function_should_call_another) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(def (a t) t)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        clisp_expr_delete(ast);
        clisp_chunk_delete(chunk);

        ast = read_entry("(def (b t) (a t))", env);
        chunk = clisp_eval_ast(ast, env);

        clisp_expr_delete(ast);
        clisp_chunk_delete(chunk);

        ast = read_entry("(b 1)", env);
        chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
    }

    PT_TEST(test_call_function_of_functions) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(def (test-case name expr) (if (error? expr) (when (#t (print name)) (#t (print expr)) (#t %exit)) (print (string->concat name \": [Passed]\"))))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        clisp_expr_delete(ast);
        clisp_chunk_delete(chunk);

        ast = read_entry("(def (check-eq? f s m) (cond ((ne f s) (error m))))", env);
        chunk = clisp_eval_ast(ast, env);

        clisp_expr_delete(ast);
        clisp_chunk_delete(chunk);

        ast = read_entry("(test-case \"Test negative number\" (check-eq? -1 -1 \"should be negative\"))", env);
        chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NIL);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
    }
}