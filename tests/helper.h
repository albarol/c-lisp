#ifndef __CLISP_TESTS_HELPER__
#define __CLISP_TESTS_HELPER__


#include "../src/ast.h"
#include "../src/builtin.h"

clisp_env_t* create_basic_env();
clisp_expr_t* create_expr_with_two_numbers(float first, float second);
clisp_expr_t* read_entry(char* input, clisp_env_t* env);

#endif