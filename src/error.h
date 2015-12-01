#ifndef __CLISP_ERROR__
#define __CLISP_ERROR__

#include "token.h"
#include "print.h"

#define clisp_chunk_assert(t, cond, fmt, ...) \
      if (!(cond)) { clisp_chunk_t* error = clisp_chunk_error(fmt, ##__VA_ARGS__); clisp_chunk_delete(t); return error; }

#define clisp_expr_assert(t, cond, fmt, ...) \
    if (!(cond)) { clisp_chunk_t* error = clisp_chunk_error(fmt, ##__VA_ARGS__); clisp_expr_delete(t); return error; }

#define clisp_assert(t, cond, fmt, ...) \
      if (!(cond)) { clisp_chunk_t* error = clisp_chunk_error(fmt, ##__VA_ARGS__); clisp_chunk_delete(t); return error; }

#define clisp_chunk_assert_count(t, num) \
    clisp_assert(t, t->value.expr.count == num, "Incorrect number of arguments. Got: %li, Expected: %li", t->value.expr.count, num)

#define clisp_expr_assert_count(t, num) \
    clisp_expr_assert(t, t->count == num, "Incorrect number of arguments. Got: %li, Expected: %li", t->count, num)

#define clisp_chunk_assert_type(t, current, expected) \
    clisp_assert(t, current == expected, "Incorrect type of argument. Got: %s, Expected: %s", clisp_print_type_name(current), clisp_print_type_name(expected))

#define clisp_expr_assert_type(t, current, expected) \
    clisp_expr_assert(t, current == expected, "Incorrect type of argument. Got: %s, Expected: %s", clisp_print_type_name(current), clisp_print_type_name(expected))


#endif
