#include "ptest.h"

#include "builtin.h"
#include "../helper.h"

PT_SUITE(suite_builtin_types) {

    PT_TEST(test_create_error) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_str("Some error"));
        clisp_chunk_t* result = clisp_builtin_type_error(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Some error");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_error_throws_with_invalid_args_count) {
        clisp_env_t* env = clisp_env_new();
        clisp_chunk_t* result = clisp_builtin_type_error(clisp_expr_new(), env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect number of arguments. Got: 0, Expected: 1");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

    PT_TEST(test_error_throws_with_invalid_args_type) {
        clisp_env_t* env = clisp_env_new();
        clisp_expr_t* expr = clisp_expr_create(clisp_chunk_number(1));
        clisp_chunk_t* result = clisp_builtin_type_error(expr, env);

        PT_ASSERT(result->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(result->value.string, "Incorrect type of argument. Got: Number, Expected: String");

        clisp_chunk_delete(result);
        clisp_env_delete(env);
    }

}