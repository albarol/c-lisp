
#include "environment.h"

clisp_env_t*
clisp_env_new(void) {
    clisp_env_t* env = malloc(sizeof(clisp_env_t));
    env->count = 0;
    env->symbols = NULL;
    env->tokens = NULL;
    return env;
}

void
clisp_env_del(clisp_env_t* env) {

    for (int i = 0; i < env->count; i++) {
        free(env->symbols[i]);
        clisp_token_del(env->tokens[i]);
    }
    free(env->symbols);
    free(env->tokens);
    free(env);
}


clisp_token_t*
clisp_env_get(clisp_env_t* env, clisp_token_t* token_symbol) {

    for (int i = 0; i < env->count; i++) {

        if (strcmp(env->symbols[i], token_symbol->symbol) == 0) {
            return clisp_token_copy(env->tokens[i]);
        }
    }
    return clisp_token_error("Unbound Symbol!");
}

void
clisp_env_put(clisp_env_t* env, clisp_token_t* token_symbol, clisp_token_t* token) {

    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->symbols[i], token_symbol->symbol) == 0) {
            clisp_token_del(env->tokens[i]);
            env->tokens[i] = clisp_token_copy(token);
            return;
        }
    }

    env->count++;
    env->tokens = realloc(env->tokens, sizeof(clisp_token_t*) * env->count);
    env->symbols = realloc(env->symbols, sizeof(char*) * env->count);

    env->tokens[env->count - 1] = clisp_token_copy(token);
    env->symbols[env->count - 1] = malloc(strlen(token_symbol->symbol) + 1);
    strcpy(env->symbols[env->count - 1], token_symbol->symbol);
}

void
clisp_env_put_function(clisp_env_t* env, char* name, clisp_function_t function) {
    clisp_token_t* symbol = clisp_token_symbol(name);
    clisp_token_t* func = clisp_token_function(function);
    clisp_env_put(env, symbol, func);

    clisp_token_del(symbol);
    clisp_token_del(func);
}