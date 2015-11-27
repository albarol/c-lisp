
#include "token.h"
#include "builtin.h"


clisp_chunk_t*
clisp_token_function(clisp_builtin_t function) {
    clisp_chunk_t* token = malloc(sizeof(clisp_chunk_t));
    token->type = CLISP_FUNCTION;
    token->builtin = function;
    return token;
}

clisp_chunk_t*
clisp_token_lambda(clisp_chunk_t* formals, clisp_chunk_t* body) {

    clisp_chunk_t* token = malloc(sizeof(clisp_chunk_t));
    token->type = CLISP_FUNCTION;
    token->builtin = NULL;

    token->env = clisp_env_new();
    token->formals = formals;
    token->body = body;

    return token;
}

clisp_chunk_t*
clisp_token_call(clisp_env_t* env, clisp_chunk_t* f, clisp_chunk_t* args) {

    if (f->builtin) { return f->builtin(env, args); }

    int given = args->count;
    int total = f->formals->count;

    while (args->count) {

        if (f->formals->count == 0) {
            clisp_token_del(args);
            return clisp_chunk_error("Function passed too many arguments. "
                                             "Got: %i, Expected: %i", given, total);
        }

        clisp_chunk_t* symbol = clisp_token_pop(f->formals, 0);
        clisp_chunk_t* token = clisp_token_pop(args, 0);

        clisp_env_put(f->env, symbol, token);
        clisp_token_del(symbol);
        clisp_token_del(token);
    }

    clisp_token_del(args);

    if (f->formals->count == 0) {

        f->env->parent = env;
        return clisp_builtin_eval(f->env,
                clisp_token_append(clisp_chunk_sexpr(), clisp_token_copy(f->body)));
    } else {
        return clisp_token_copy(f);
    }
}

int
clisp_token_cmp(clisp_chunk_t* first, clisp_chunk_t* second) {

    if (first->type != second->type) { return 0; }

    switch (first->type) {

        case CLISP_NUMBER:
            return (first->value.number == second->value.number);

        case CLISP_ERROR:
            return (strcmp(first->value.string, second->value.string) == 0);

        case CLISP_SYMBOL:
            return (strcmp(first->value.string, second->value.string) == 0);

        case CLISP_STRING:
            return (strcmp(first->value.string, second->value.string) == 0);

        case CLISP_FUNCTION:
            if (first->builtin || second->builtin) {
                return first->builtin == second->builtin;
            } else {
                return clisp_token_cmp(first->formals, second->formals)
                       && clisp_token_cmp(first->body, second->body);
            }

        case TOKEN_QEXPRESSION:
        case CLISP_ATOM:
            if (first->count != second->count) { return 0; }
            for (int i = 0; i < first->count; i++) {
                if (!clisp_token_cmp(first->tokens[i], second->tokens[i])) {
                    return 0;
                }
            }
            return 1;
        break;
    }
    return 0;
}

void
clisp_token_del(clisp_chunk_t* token) {

    switch (token->type) {

        case CLISP_NUMBER:
            break;

        case CLISP_FUNCTION:
            if (!token->builtin) {
                clisp_env_del(token->env);
                clisp_token_del(token->formals);
                clisp_token_del(token->body);
            }
            break;

        case CLISP_ERROR:
            free(token->value.string);
            break;

        case CLISP_SYMBOL:
            free(token->value.string);
            break;

        case CLISP_STRING:
            free(token->value.string);
            break;

        case TOKEN_QEXPRESSION:
        case CLISP_ATOM:
            for (int i = 0; i < token->count; i++) {
                clisp_token_del(token->tokens[i]);
            }
            break;
    }

    free(token);
}

clisp_chunk_t*
clisp_token_append(clisp_chunk_t* super, clisp_chunk_t* child) {
    super->count++;
    super->tokens = realloc(super->tokens, sizeof(clisp_chunk_t*) * super->count);
    super->tokens[super->count - 1] = child;
    return super;
}

clisp_chunk_t*
clisp_token_pop(clisp_chunk_t* token, int position) {

    clisp_chunk_t* item = token->tokens[position];

    memmove(&token->tokens[position], &token->tokens[position + 1],
            sizeof(clisp_chunk_t*) * (token->count - position - 1));

    token->count--;

    token->tokens = realloc(token->tokens, sizeof(clisp_chunk_t*) * (token->count));
    return item;
}


clisp_chunk_t*
clisp_token_take(clisp_chunk_t* token, int position) {
    clisp_chunk_t* item = clisp_token_pop(token, position);
    clisp_token_del(token);
    return item;
}


clisp_chunk_t*
clisp_token_join(clisp_chunk_t* first, clisp_chunk_t* second) {
    while (second->count) {
        first = clisp_token_append(first, clisp_token_pop(second, 0));
    }

    clisp_token_del(second);
    return first;
}


clisp_chunk_t*
clisp_token_copy(clisp_chunk_t* token) {

    clisp_chunk_t* copy_token= malloc(sizeof(clisp_chunk_t));
    copy_token->type = token->type;

    switch (token->type) {
        case CLISP_FUNCTION:
            if (token->builtin) {
                copy_token->builtin = token->builtin;
            } else {
                copy_token->builtin = NULL;
                copy_token->env = clisp_env_copy(token->env);
                copy_token->formals = clisp_token_copy(token->formals);
                copy_token->body = clisp_token_copy(token->body);
            }
            break;

        case CLISP_NUMBER:
            copy_token->value.number = token->value.number;
            break;

        case CLISP_ERROR:
            copy_token->value.string = malloc(strlen(token->value.string));
            strcpy(copy_token->value.string, token->value.string);
            break;

        case CLISP_SYMBOL:
            copy_token->value.string = malloc(strlen(token->value.string));
            strcpy(copy_token->value.string, token->value.string);
            break;

        case CLISP_STRING:
            copy_token->value.string = malloc(strlen(token->value.string));
            strcpy(copy_token->value.string, token->value.string);
            break;


        case TOKEN_QEXPRESSION:
        case CLISP_ATOM:
            copy_token->count = token->count;
            copy_token->tokens = malloc(sizeof(clisp_chunk_t*) * token->count);
            for (int i = 0; i < copy_token->count; i++) {
                copy_token->tokens[i] = clisp_token_copy(token->tokens[i]);
            }
            break;
    }
    return copy_token;
}
