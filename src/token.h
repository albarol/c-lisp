#ifndef __CLISP_TOKEN__
#define __CLISP_TOKEN__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "types.h"


clisp_chunk_t* clisp_token_call(clisp_env_t* env, clisp_chunk_t* function, clisp_chunk_t* args);

int clisp_token_cmp(clisp_chunk_t* first, clisp_chunk_t* second);


#endif
