#ifndef __CLISP_ERROR__
#define __CLISP_ERROR__

#include "token.h"

#define clisp_assert(t, cond, fmt, ...) \
      if (!(cond)) { clisp_token_t* error = clisp_token_error(fmt, ##__VA_ARGS__); clisp_token_del(t); return error; }

#define clisp_assert_count(t, num) \
    clisp_assert(t, t->count == num, "Incorrect number of arguments. Got: %li, Expected: %li", token->count, num)

#define clisp_assert_type(t, current, expected) \
    clisp_assert(t, current == expected, "Incorrect type of argument. Got: %s, Expected: %s", clisp_print_type_name(current), clisp_print_type_name(expected))

#endif
