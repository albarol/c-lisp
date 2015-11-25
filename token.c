
#include "token.h"
#include "builtin.h"

clisp_token_t*
clisp_token_number(float num) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_NUMBER;
    token->number = num;
    return token;
}

clisp_token_t*
clisp_token_error(char* fmt, ...) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_ERROR;

    va_list args;
    va_start(args, fmt);

    token->error = malloc(512);
    vsnprintf(token->error, 511, fmt, args);

    token->error = realloc(token->error, strlen(token->error)+1);
    va_end(args);

    return token;
}

clisp_token_t*
clisp_token_symbol(char* symbol) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_SYMBOL;
    token->symbol = malloc(strlen(symbol) + 1);
    strcpy(token->symbol, symbol);
    return token;
}

clisp_token_t*
clisp_token_sexpr(void) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_SEXPRESSION;
    token->count = 0;
    token->tokens = NULL;
    return token;
}

clisp_token_t*
clisp_token_qexpr(void) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_QEXPRESSION;
    token->count = 0;
    token->tokens = NULL;
    return token;
}

clisp_token_t*
clisp_token_str(char* str) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_STR;
    token->str = malloc(strlen(str) + 1);
    strcpy(token->str, str);
    return token;
}

clisp_token_t*
clisp_token_function(clisp_function_t function) {
    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_FUNCTION;
    token->builtin = function;
    return token;
}

clisp_token_t*
clisp_token_lambda(clisp_token_t* formals, clisp_token_t* body) {

    clisp_token_t* token = malloc(sizeof(clisp_token_t));
    token->type = TOKEN_FUNCTION;
    token->builtin = NULL;

    token->env = clisp_env_new();
    token->formals = formals;
    token->body = body;

    return token;
}

clisp_token_t*
clisp_token_call(clisp_env_t* env, clisp_token_t* f, clisp_token_t* args) {

    if (f->builtin) { return f->builtin(env, args); }

    int given = args->count;
    int total = f->formals->count;

    while (args->count) {

        if (f->formals->count == 0) {
            clisp_token_del(args);
            return clisp_token_error("Function passed too many arguments. "
                                     "Got: %i, Expected: %i", given, total);
        }

        clisp_token_t* symbol = clisp_token_pop(f->formals, 0);
        clisp_token_t* token = clisp_token_pop(args, 0);

        clisp_env_put(f->env, symbol, token);
        clisp_token_del(symbol);
        clisp_token_del(token);
    }

    clisp_token_del(args);

    if (f->formals->count == 0) {

        f->env->parent = env;
        return clisp_builtin_eval(f->env,
                clisp_token_append(clisp_token_sexpr(), clisp_token_copy(f->body)));
    } else {
        return clisp_token_copy(f);
    }
}

int
clisp_token_cmp(clisp_token_t* first, clisp_token_t* second) {

    if (first->type != second->type) { return 0; }

    switch (first->type) {

        case TOKEN_NUMBER:
            return (first->number == second->number);

        case TOKEN_ERROR:
            return (strcmp(first->error, second->error) == 0);

        case TOKEN_SYMBOL:
            return (strcmp(first->symbol, second->symbol) == 0);

        case TOKEN_STR:
            return (strcmp(first->str, second->str) == 0);

        case TOKEN_FUNCTION:
            if (first->builtin || second->builtin) {
                return first->builtin == second->builtin;
            } else {
                return clisp_token_cmp(first->formals, second->formals)
                       && clisp_token_cmp(first->body, second->body);
            }

        case TOKEN_QEXPRESSION:
        case TOKEN_SEXPRESSION:
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
clisp_token_del(clisp_token_t* token) {

    switch (token->type) {

        case TOKEN_NUMBER:
            break;

        case TOKEN_FUNCTION:
            if (!token->builtin) {
                clisp_env_del(token->env);
                clisp_token_del(token->formals);
                clisp_token_del(token->body);
            }
            break;

        case TOKEN_ERROR:
            free(token->error);
            break;

        case TOKEN_SYMBOL:
            free(token->symbol);
            break;

        case TOKEN_STR:
            free(token->str);
            break;

        case TOKEN_QEXPRESSION:
        case TOKEN_SEXPRESSION:
            for (int i = 0; i < token->count; i++) {
                clisp_token_del(token->tokens[i]);
            }
            break;
    }

    free(token);
}

clisp_token_t*
clisp_token_append(clisp_token_t* super, clisp_token_t* child) {
    super->count++;
    super->tokens = realloc(super->tokens, sizeof(clisp_token_t*) * super->count);
    super->tokens[super->count - 1] = child;
    return super;
}

clisp_token_t*
clisp_token_pop(clisp_token_t* token, int position) {

    clisp_token_t* item = token->tokens[position];

    memmove(&token->tokens[position], &token->tokens[position + 1],
            sizeof(clisp_token_t*) * (token->count-position-1));

    token->count--;

    token->tokens = realloc(token->tokens, sizeof(clisp_token_t*) * (token->count));
    return item;
}


clisp_token_t*
clisp_token_take(clisp_token_t* token, int position) {
    clisp_token_t* item = clisp_token_pop(token, position);
    clisp_token_del(token);
    return item;
}


clisp_token_t*
clisp_token_join(clisp_token_t* first, clisp_token_t* second) {
    while (second->count) {
        first = clisp_token_append(first, clisp_token_pop(second, 0));
    }

    clisp_token_del(second);
    return first;
}


clisp_token_t*
clisp_token_copy(clisp_token_t* token) {

    clisp_token_t* copy_token= malloc(sizeof(clisp_token_t));
    copy_token->type = token->type;

    switch (token->type) {
        case TOKEN_FUNCTION:
            if (token->builtin) {
                copy_token->builtin = token->builtin;
            } else {
                copy_token->builtin = NULL;
                copy_token->env = clisp_env_copy(token->env);
                copy_token->formals = clisp_token_copy(token->formals);
                copy_token->body = clisp_token_copy(token->body);
            }
            break;

        case TOKEN_NUMBER:
            copy_token->number = token->number;
            break;

        case TOKEN_ERROR:
            copy_token->error = malloc(strlen(token->error));
            strcpy(copy_token->error, token->symbol);
            break;

        case TOKEN_SYMBOL:
            copy_token->symbol = malloc(strlen(token->symbol));
            strcpy(copy_token->symbol, token->symbol);
            break;

        case TOKEN_STR:
            copy_token->symbol = malloc(strlen(token->str));
            strcpy(copy_token->str, token->str);
            break;


        case TOKEN_QEXPRESSION:
        case TOKEN_SEXPRESSION:
            copy_token->count = token->count;
            copy_token->tokens = malloc(sizeof(clisp_token_t*) * token->count);
            for (int i = 0; i < copy_token->count; i++) {
                copy_token->tokens[i] = clisp_token_copy(token->tokens[i]);
            }
            break;
    }
    return copy_token;
}
