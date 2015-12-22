
#include "ptest.h"

#include "types.h"


PT_SUITE(suite_env) {

    /**
     * Test new env
     */
    PT_TEST(test_new_env) {
        clisp_env_t* env = clisp_env_new();

        PT_ASSERT(env->count == 0);

        clisp_env_delete(env);
    }

    /**
     * Test get and put env
     */
    PT_TEST(test_put_and_get_symbol) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* symbol = clisp_chunk_symbol("x");
        clisp_chunk_t* value = clisp_chunk_number(5);

        clisp_env_put(env, symbol, value);

        clisp_chunk_t* chunk = clisp_env_get(env, symbol);

        PT_ASSERT(chunk->value.number == 5);

        clisp_env_delete(env);
        clisp_chunk_delete(symbol);
        clisp_chunk_delete(value);
    }

    PT_TEST(test_put_twice_and_get_symbol) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* symbol = clisp_chunk_symbol("x");
        clisp_chunk_t* value = clisp_chunk_number(5);
        clisp_chunk_t* new_value = clisp_chunk_number(6);

        clisp_env_put(env, symbol, value);
        clisp_env_put(env, symbol, new_value);

        clisp_chunk_t* chunk = clisp_env_get(env, symbol);

        PT_ASSERT(chunk->value.number == 6);

        clisp_env_delete(env);
        clisp_chunk_delete(symbol);
        clisp_chunk_delete(value);
        clisp_chunk_delete(new_value);
    }

    PT_TEST(test_get_unknown_symbol) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* symbol = clisp_chunk_symbol("x");

        clisp_chunk_t* error = clisp_env_get(env, symbol);

        PT_ASSERT_STR_EQ(error->value.string, "Unbound Symbol!");

        clisp_env_delete(env);
        clisp_chunk_delete(error);
    }
}