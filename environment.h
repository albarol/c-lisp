#ifndef __CLISP_ENVIRONMENT__
#define __CLISP_ENVIRONMENT__

#include "token.h"

struct clisp_env_t {
    int count;
    char** symbols;
    clisp_token_t** tokens;
};

clisp_env_t* clisp_env_new(void);
clisp_env_t* clisp_env_copy(clisp_env_t* env);
void clisp_env_del(clisp_env_t* env);
clisp_token_t* clisp_env_get(clisp_env_t* env, clisp_token_t* token);
void clisp_env_put(clisp_env_t* env, clisp_token_t* t, clisp_token_t* v);
void clisp_env_put_function(clisp_env_t* env, char* name, clisp_function_t function);

#endif
