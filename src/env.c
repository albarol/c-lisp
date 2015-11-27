
#include "types.h"

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
clisp_env_delete(clisp_env_t* env) {
    for (int i = 0; i < env->count; i++) {
        free(env->symbols[i]);
        clisp_chunk_delete(env->tokens[i]);
    }
    free(env->symbols);
    free(env->tokens);
    free(env);
}