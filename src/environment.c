
#include "environment.h"


//void
//clisp_env_put_function(clisp_env_t* env, char* name, clisp_builtin_t function) {
//    clisp_chunk_t* symbol = clisp_chunk_symbol(name);
//    clisp_chunk_t* func = clisp_chunk_builtin(function);
//    clisp_env_put(env, symbol, func);
//
//    clisp_chunk_delete(symbol);
//    clisp_chunk_delete(func);
//}

void
clisp_env_define(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token) {
    while (env->parent) {
        env = env->parent;
    }
    clisp_env_put(env, token_symbol, token);
}
