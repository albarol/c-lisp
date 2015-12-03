#include "ptest.h"

#include "../../src/builtin.h"
#include "../helper.h"
#include "../../src/types.h"

PT_SUITE(suite_builtin_conditionals) {

    PT_TEST(test_if_returns_first_expr) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_new();
        clisp_expr_append(expr, clisp_chunk_bool(1));
        clisp_expr_append(expr, clisp_chunk_number(3));
        clisp_expr_append(expr, clisp_chunk_number(4));
        clisp_chunk_t* chunk = clisp_builtin_cond_if(expr, env);

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
        clisp_chunk_t* chunk = clisp_builtin_cond_if(expr, env);

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
        clisp_chunk_t* chunk = clisp_builtin_cond_def(expr, env);

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.list->count == 2);

        clisp_chunk_delete(chunk);
        clisp_env_delete(env);
    }
}