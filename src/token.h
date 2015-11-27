#ifndef __CLISP_TOKEN__
#define __CLISP_TOKEN__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "types.h"


clisp_chunk_t* clisp_token_function(clisp_builtin_t function);
clisp_chunk_t* clisp_token_lambda(clisp_chunk_t* formals, clisp_chunk_t* body);
clisp_chunk_t* clisp_token_call(clisp_env_t* env, clisp_chunk_t* function, clisp_chunk_t* args);

int clisp_token_cmp(clisp_chunk_t* first, clisp_chunk_t* second);

void clisp_token_del(clisp_chunk_t* token);
clisp_chunk_t* clisp_token_append(clisp_chunk_t* super, clisp_chunk_t* child);
clisp_chunk_t* clisp_token_pop(clisp_chunk_t* super, int position);
clisp_chunk_t* clisp_token_take(clisp_chunk_t* super, int position);
clisp_chunk_t* clisp_token_join(clisp_chunk_t* super, clisp_chunk_t* child);
clisp_chunk_t* clisp_token_copy(clisp_chunk_t* token);

#endif
