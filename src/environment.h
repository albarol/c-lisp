#ifndef __CLISP_ENVIRONMENT__
#define __CLISP_ENVIRONMENT__

#include "token.h"

clisp_chunk_t* clisp_env_get(clisp_env_t* env, clisp_chunk_t* token);
void clisp_env_put(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token);
void clisp_env_put_function(clisp_env_t* env, char* name, clisp_builtin_t function);

void clisp_env_define(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token);

#endif
