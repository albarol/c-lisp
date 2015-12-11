#include <types.h>
#include "ptest.h"

#include "../helper.h"

PT_SUITE(suite_builtin_syntactic) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(1));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_expr_append(expr, clisp_chunk_number(4));
        clisp_chunk_t* chunk = clisp_builtin_syntactic_if(expr, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 3);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(0));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_expr_append(expr, clisp_chunk_number(4));
        clisp_chunk_t* chunk = clisp_builtin_syntactic_if(expr, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 4);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_def_returns_function) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* args = clisp_chunk_expr();
        clisp_expr_append(args->value.list, clisp_chunk_symbol("sum"));
        clisp_expr_append(args->value.list, clisp_chunk_symbol("a"));
        clisp_expr_append(args->value.list, clisp_chunk_symbol("b"));

        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_append(body->value.list, clisp_chunk_symbol("+"));
        clisp_expr_append(body->value.list, clisp_chunk_symbol("a"));
        clisp_expr_append(body->value.list, clisp_chunk_symbol("b"));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, args);
        clisp_expr_append(expr, body);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_def(expr, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.list->count == 2);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_for_should_call_func_many_times) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* iterator = clisp_chunk_expr();
        clisp_expr_append(iterator->value.list, clisp_chunk_symbol("i"));
        clisp_chunk_t* list = clisp_chunk_list();
        clisp_expr_append(list->value.list, clisp_chunk_number(5));
        clisp_expr_append(iterator->value.list, list);

        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_append(body->value.list, clisp_chunk_symbol("display"));
        clisp_expr_append(body->value.list, clisp_chunk_symbol("i"));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, iterator);
        clisp_expr_append(expr, body);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_for(expr, env);

        PT_ASSERT(chunk->type == CLISP_NIL);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_for_throws_error_invalid_iterator_without_symbol) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* iterator = clisp_chunk_expr();
        clisp_chunk_t* list = clisp_chunk_list();
        clisp_expr_append(list->value.list, clisp_chunk_number(5));
        clisp_expr_append(iterator->value.list, list);

        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_append(body->value.list, clisp_chunk_symbol("display"));
        clisp_expr_append(body->value.list, clisp_chunk_symbol("i"));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, iterator);
        clisp_expr_append(expr, body);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_for(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_for_throws_error_invalid_iterator_without_list) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* iterator = clisp_chunk_expr();
        clisp_expr_append(iterator->value.list, clisp_chunk_symbol("i"));
        clisp_expr_append(iterator->value.list, clisp_chunk_list());

        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_append(body->value.list, clisp_chunk_symbol("display"));
        clisp_expr_append(body->value.list, clisp_chunk_symbol("i"));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, iterator);
        clisp_expr_append(expr, body);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_for(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_for_throws_error_invalid_iterator_without_body) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* iterator = clisp_chunk_expr();
        clisp_expr_append(iterator->value.list, clisp_chunk_symbol("i"));
        clisp_expr_append(iterator->value.list, clisp_chunk_list());

        clisp_chunk_t* body = clisp_chunk_expr();

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, iterator);
        clisp_expr_append(expr, body);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_for(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_cond_should_execute_one_expression) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* first = clisp_chunk_expr();
        clisp_expr_append(first->value.list, clisp_chunk_bool(false));
        clisp_expr_append(first->value.list, clisp_chunk_number(1));

        clisp_chunk_t* second = clisp_chunk_expr();
        clisp_expr_append(second->value.list, clisp_chunk_bool(true));
        clisp_expr_append(second->value.list, clisp_chunk_number(2));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, first);
        clisp_expr_append(expr, second);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_cond(expr, env);

        PT_ASSERT(chunk->type == CLISP_NUMBER);
        PT_ASSERT(chunk->value.number == 2);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_cond_throws_error_when_chunk_is_not_an_expression) {
        clisp_env_t* env = clisp_env_new();

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(false));
        clisp_expr_append(expr, clisp_chunk_number(1));
        clisp_chunk_t* chunk = clisp_builtin_syntactic_cond(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Invalid expression. It should be ((Boolean) Type)");

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_cond_throws_error_when_expr_does_not_have_bool) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* first = clisp_chunk_expr();
        clisp_expr_append(first->value.list, clisp_chunk_number(1));
        clisp_expr_append(first->value.list, clisp_chunk_number(1));

        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, first);
        clisp_chunk_t* chunk = clisp_builtin_syntactic_cond(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(chunk->value.string, "Invalid argument type. Got: Number, Expected: Boolean");

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_lambda_expression) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* args = clisp_chunk_expr();
        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, args);
        clisp_expr_append(expr, body);

        clisp_chunk_t* chunk = clisp_builtin_syntactic_lambda(expr, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_lambda_throws_error_invalid_number_of_args) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* args = clisp_chunk_expr();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, args);

        clisp_chunk_t* chunk = clisp_builtin_syntactic_lambda(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }

    PT_TEST(test_lambda_throws_error_invalid_arg_type) {
        clisp_env_t* env = clisp_env_new();

        clisp_chunk_t* args = clisp_chunk_number(1);
        clisp_chunk_t* body = clisp_chunk_expr();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, args);
        clisp_expr_append(expr, body);

        clisp_chunk_t* chunk = clisp_builtin_syntactic_lambda(expr, env);

        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }
}