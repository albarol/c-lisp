
#include "environment.h"


void
clisp_env_define(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token) {
    while (env->parent) {
        env = env->parent;
    }
    clisp_env_put(env, token_symbol, token);
}
