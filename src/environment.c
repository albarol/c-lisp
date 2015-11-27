
#include "environment.h"

clisp_env_t*
clisp_env_new(void) {
    clisp_env_t* env = malloc(sizeof(clisp_env_t));
    env->parent = NULL;
    env->count = 0;
    env->symbols = NULL;
    env->tokens = NULL;
    return env;
}

clisp_env_t*
clisp_env_copy(clisp_env_t* env) {
    clisp_env_t* new_env = malloc(sizeof(clisp_env_t));
    new_env->parent = env->parent;
    new_env->count = env->count;

    new_env->symbols = malloc(sizeof(char*) * new_env->count);
    new_env->tokens = malloc(sizeof(clisp_chunk_t*) * new_env->count);

    for (int i = 0; i < new_env->count; i++) {
        new_env->tokens[i] = clisp_token_copy(env->tokens[i]);
        new_env->symbols[i] = malloc(strlen(env->symbols[i]) + 1);
        strcpy(new_env->symbols[i], env->symbols[i]);
    }
    return new_env;
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


clisp_chunk_t*
clisp_env_get(clisp_env_t* env, clisp_chunk_t* token_symbol) {

    for (int i = 0; i < env->count; i++) {

        if (strcmp(env->symbols[i], token_symbol->value.string) == 0) {
            return clisp_token_copy(env->tokens[i]);
        }
    }

    if (env->parent) {
        return clisp_env_get(env->parent, token_symbol);
    }

    return clisp_chunk_error("Unbound Symbol!");
}

void
clisp_env_put(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token) {

    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->symbols[i], token_symbol->value.string) == 0) {
            clisp_token_del(env->tokens[i]);
            env->tokens[i] = clisp_token_copy(token);
            return;
        }
    }

    env->count++;
    env->tokens = realloc(env->tokens, sizeof(clisp_chunk_t*) * env->count);
    env->symbols = realloc(env->symbols, sizeof(char*) * env->count);

    env->tokens[env->count - 1] = clisp_token_copy(token);
    env->symbols[env->count - 1] = malloc(strlen(token_symbol->value.string) + 1);
    strcpy(env->symbols[env->count - 1], token_symbol->value.string);
}

void
clisp_env_put_function(clisp_env_t* env, char* name, clisp_builtin_t function) {
    clisp_chunk_t* symbol = clisp_chunk_symbol(name);
    clisp_chunk_t* func = clisp_chunk_builtin(function);
    clisp_env_put(env, symbol, func);

    clisp_token_del(symbol);
    clisp_token_del(func);
}

void
clisp_env_define(clisp_env_t* env, clisp_chunk_t* token_symbol, clisp_chunk_t* token) {
    while (env->parent) {
        env = env->parent;
    }
    clisp_env_put(env, token_symbol, token);
}
