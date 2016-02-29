
#include <types.h>

clisp_env_t*
clisp_env_new(void) {
    clisp_env_t* env = malloc(sizeof(clisp_env_t));
    env->parent = NULL;
    env->count = 0;
    env->symbols = NULL;
    env->chunks = NULL;
    return env;
}

clisp_env_t*
clisp_env_copy(clisp_env_t* env) {
    clisp_env_t* new_env = malloc(sizeof(clisp_env_t));
    new_env->parent = env->parent;
    new_env->count = env->count;

    new_env->symbols = malloc(sizeof(char*) * new_env->count);
    new_env->chunks = malloc(sizeof(clisp_chunk_t*) * new_env->count);

    for (int i = 0; i < new_env->count; i++) {
        new_env->chunks[i] = clisp_chunk_copy(env->chunks[i]);
        new_env->symbols[i] = malloc(strlen(env->symbols[i]) + 1);
        strcpy(new_env->symbols[i], env->symbols[i]);
    }
    return new_env;
}

void
clisp_env_free(clisp_env_t* env) {
    for (int i = 0; i < env->count; i++) {
        free(env->symbols[i]);
        clisp_chunk_free(env->chunks[i]);
    }
    free(env->symbols);
    free(env->chunks);
    free(env);
}

clisp_chunk_t*
clisp_env_get(clisp_env_t* env, clisp_chunk_t* symbol) {

    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->symbols[i], symbol->value.string) == 0) {
            return clisp_chunk_copy(env->chunks[i]);
        }
    }

    if (env->parent) {
        return clisp_env_get(env->parent, symbol);
    }

    return clisp_chunk_error("Unbound Symbol!");
}

void
clisp_env_put(clisp_env_t* env, clisp_chunk_t* symbol, clisp_chunk_t* value) {

    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->symbols[i], symbol->value.string) == 0) {
            clisp_chunk_free(env->chunks[i]);
            env->chunks[i] = clisp_chunk_copy(value);
            return;
        }
    }

    env->count++;
    env->chunks = realloc(env->chunks, sizeof(clisp_chunk_t*) * env->count);
    env->symbols = realloc(env->symbols, sizeof(char*) * env->count);

    env->chunks[env->count - 1] = clisp_chunk_copy(value);
    env->symbols[env->count - 1] = malloc(strlen(symbol->value.string) + 1);
    strcpy(env->symbols[env->count - 1], symbol->value.string);
}

void
clisp_env_put_builtin(clisp_env_t* env, char* symbol, clisp_builtin_t builtin, clisp_function_type type) {
    clisp_chunk_t* s = clisp_chunk_symbol(symbol);
    clisp_chunk_t* b = clisp_chunk_builtin(builtin, type);

    clisp_env_put(env, s, b);
    clisp_chunk_free(s);
    clisp_chunk_free(b);
}