
#include "token.h"
#include "builtin.h"
#include "types.h"


clisp_chunk_t*
clisp_token_lambda(clisp_chunk_t* formals, clisp_chunk_t* body) {

    clisp_chunk_t* token = malloc(sizeof(clisp_chunk_t));
    token->type = CLISP_FUNCTION;
    token->value.builtin = NULL;

    token->value.func.env = clisp_env_new();
    token->value.func.args = formals;
    token->value.func.body = body;

    return token;
}

clisp_chunk_t*
clisp_token_call(clisp_env_t* env, clisp_chunk_t* f, clisp_chunk_t* args) {

    if (f->type == CLISP_FUNCTION_C) { return f->value.builtin(env, args); }

    int given = args->count;
    int total = f->value.func.args->count;

    while (args->count) {

        if (f->value.func.args->count == 0) {
            clisp_chunk_delete(args);
            return clisp_chunk_error("Function passed too many arguments. "
                                             "Got: %i, Expected: %i", given, total);
        }

        clisp_chunk_t* symbol = clisp_token_pop(f->value.func.args, 0);
        clisp_chunk_t* token = clisp_token_pop(args, 0);

        clisp_env_put(f->value.func.env, symbol, token);
        clisp_chunk_delete(symbol);
        clisp_chunk_delete(token);
    }

    clisp_chunk_delete(args);

    if (f->value.func.args->count == 0) {

        f->value.func.env->parent = env;
        return clisp_builtin_eval(f->value.func.env,
                clisp_token_append(clisp_chunk_sexpr(), clisp_token_copy(f->value.func.body)));
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

        case CLISP_FUNCTION_C:
            return first->value.builtin == second->value.builtin;

        case CLISP_FUNCTION:
            return clisp_token_cmp(first->value.func.args, second->value.func.args)
                   && clisp_token_cmp(first->value.func.body, second->value.func.body);

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
    clisp_chunk_delete(token);
    return item;
}


clisp_chunk_t*
clisp_token_join(clisp_chunk_t* first, clisp_chunk_t* second) {
    while (second->count) {
        first = clisp_token_append(first, clisp_token_pop(second, 0));
    }

    clisp_chunk_delete(second);
    return first;
}


clisp_chunk_t*
clisp_token_copy(clisp_chunk_t* token) {

    clisp_chunk_t* copy_token= malloc(sizeof(clisp_chunk_t));
    copy_token->type = token->type;

    switch (token->type) {

        case CLISP_FUNCTION_C:
            copy_token->value.builtin = token->value.builtin;
            break;

        case CLISP_FUNCTION:
            copy_token->value.func.env = clisp_env_copy(token->value.func.env);
            copy_token->value.func.args = clisp_token_copy(token->value.func.args);
            copy_token->value.func.body = clisp_token_copy(token->value.func.body);
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
