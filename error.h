#ifndef __CLISP_ERROR__
#define __CLISP_ERROR__

#include "token.h"

#define clisp_assert(token, cond, fmt, ...) \
      if (!(cond)) { \
          clisp_token_t* error = clisp_token_error(fmt, ##__VA_ARGS__); \
          clisp_token_del(token); \
          return error; \
}

#endif
