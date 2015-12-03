
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_ast_builtin_list) {

    PT_TEST(test_join_two_lists) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(append [1 2 3 4] [5 6 7])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_LIST);
        PT_ASSERT(chunk->value.list->count = 7);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_head_element) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(head [5 6 7])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number = 5);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_get_tail_from_list) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(tail [5 6 7])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_LIST);
        PT_ASSERT(chunk->value.list->count == 2);
        PT_ASSERT(chunk->value.list->chunks[0]->value.number == 6);
        PT_ASSERT(chunk->value.list->chunks[1]->value.number == 7);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_join_using_functions) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(append (tail [4 5 6 7]) (head [1 2 3 4]))", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_LIST);
        PT_ASSERT(chunk->value.list->count == 4);
        PT_ASSERT(chunk->value.list->chunks[0]->value.number == 5);
        PT_ASSERT(chunk->value.list->chunks[3]->value.number == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_list_eq_returns_true) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(list? [1 2 3 4])", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 1);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }

    PT_TEST(test_list_eq_returns_false) {
        clisp_env_t* env = create_basic_env();
        clisp_expr_t* ast = read_entry("(list? #t)", env);
        clisp_chunk_t* chunk = clisp_eval_ast(ast, env);

        PT_ASSERT(chunk->type == CLISP_BOOL);
        PT_ASSERT(chunk->value.boolean == 0);

        clisp_chunk_delete(chunk);
        clisp_expr_delete(ast);
        clisp_env_delete(env);
    }
}