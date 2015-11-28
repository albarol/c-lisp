
#include "ptest.h"

#include "../src/types.h"


clisp_chunk_t*
fake_builtin(clisp_env_t* env, clisp_chunk_t* chunk) {
    return chunk;
}

PT_SUITE(suite_types) {

    PT_TEST(test_new_chunk_number) {
        clisp_chunk_t* chunk = clisp_chunk_number(5);

        PT_ASSERT(chunk->value.number == 5);
        PT_ASSERT(chunk->type == CLISP_NUMBER);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_symbol) {
        clisp_chunk_t* chunk = clisp_chunk_symbol("symbol");

        PT_ASSERT(strcmp(chunk->value.string, "symbol") == 0);
        PT_ASSERT(chunk->type == CLISP_SYMBOL);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_string) {
        clisp_chunk_t* chunk = clisp_chunk_str("string");

        PT_ASSERT(strcmp(chunk->value.string, "string") == 0);
        PT_ASSERT(chunk->type == CLISP_STRING);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_error) {
        clisp_chunk_t* chunk = clisp_chunk_error("Error %i", 1);

        PT_ASSERT(strcmp(chunk->value.string, "Error 1") == 0);
        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_sexpr) {
        clisp_chunk_t* chunk = clisp_chunk_sexpr();

        PT_ASSERT(chunk->value.expr.count == 0);
        PT_ASSERT(chunk->type == CLISP_ATOM);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_qexpr) {
        clisp_chunk_t* chunk = clisp_chunk_qexpr();

        PT_ASSERT(chunk->value.expr.count == 0);
        PT_ASSERT(chunk->type == TOKEN_QEXPRESSION);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_builtin_should_return_number) {
        clisp_chunk_t* chunk = clisp_chunk_builtin(fake_builtin);

        PT_ASSERT(chunk->type == CLISP_FUNCTION_C);

        clisp_chunk_t* result = chunk->value.builtin(clisp_env_new(), clisp_chunk_number(5));
        PT_ASSERT(result->value.number == 5);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_builtin_should_return_str) {
        clisp_chunk_t* chunk = clisp_chunk_builtin(fake_builtin);

        PT_ASSERT(chunk->type == CLISP_FUNCTION_C);

        clisp_chunk_t* result = chunk->value.builtin(clisp_env_new(), clisp_chunk_str("string"));
        PT_ASSERT(strcmp(result->value.string, "string") == 0);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_function) {
        clisp_chunk_t* chunk = clisp_chunk_function(clisp_chunk_sexpr(), clisp_chunk_sexpr());

        PT_ASSERT(chunk->type == CLISP_FUNCTION);
        PT_ASSERT(chunk->value.func.args->value.expr.count == 0);
        PT_ASSERT(chunk->value.func.body->value.expr.count == 0);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_copy_chunk_builtin) {
        clisp_chunk_t* chunk = clisp_chunk_builtin(fake_builtin);
        clisp_chunk_t* copied = clisp_chunk_copy(chunk);

        clisp_chunk_t* result = copied->value.builtin(clisp_env_new(), clisp_chunk_number(5));
        PT_ASSERT(result->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_chunk_delete(copied);
        clisp_chunk_delete(result);
    }

    PT_TEST(test_copy_chunk_number) {

        clisp_chunk_t* chunk = clisp_chunk_number(5);
        clisp_chunk_t* copied = clisp_chunk_copy(chunk);

        PT_ASSERT(copied->value.number == 5);

        clisp_chunk_delete(chunk);
        clisp_chunk_delete(copied);
    }

    PT_TEST(test_copy_chunk_symbol) {

        clisp_chunk_t* chunk = clisp_chunk_symbol("symbol");
        clisp_chunk_t* copied = clisp_chunk_copy(chunk);

        PT_ASSERT_STR_EQ(copied->value.string, "symbol");

        clisp_chunk_delete(chunk);
        clisp_chunk_delete(copied);
    }
}