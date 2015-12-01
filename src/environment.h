#ifndef __CLISP_ENVIRONMENT__
#define __CLISP_ENVIRONMENT__

#include "token.h"


void clisp_env_define(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token);

#endif