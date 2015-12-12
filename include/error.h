#ifndef __CLISP_ERROR__
#define __CLISP_ERROR__

#include "types.h"
#include "print.h"


#define TYPE_ERROR "Incorrect type of argument. Got: %s, Expected: %s"
#define COUNT_ERROR "Incorrect number of arguments. Got: %li, Expected: %li"

#define clisp_chunk_assert(t, cond, fmt, ...) \
      if (!(cond)) { clisp_chunk_t* error = clisp_chunk_error(fmt, ##__VA_ARGS__); clisp_chunk_delete(t); return error; }

#define clisp_chunk_assert_type(t, current, expected) \
    clisp_chunk_assert(t, (current & expected) != 0, TYPE_ERROR, clisp_print_type_name(current), clisp_print_type_name(expected))

#define clisp_expr_assert(t, cond, fmt, ...) \
    if (!(cond)) { clisp_chunk_t* error = clisp_chunk_error(fmt, ##__VA_ARGS__); clisp_expr_delete(t); return error; }

#define clisp_expr_assert_count(t, num) \
    clisp_expr_assert(t, t->count == num, COUNT_ERROR, t->count, num)

#define clisp_expr_assert_type(t, current, expected) \
    clisp_expr_assert(t, (current & expected) != 0, TYPE_ERROR, clisp_print_type_name(current), clisp_print_type_name(expected))

#endif
