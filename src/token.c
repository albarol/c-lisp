
#include "token.h"
#include "builtin.h"
#include "types.h"


clisp_chunk_t*
clisp_token_call(clisp_env_t* env, clisp_chunk_t* f, clisp_chunk_t* args) {

    if (f->type == CLISP_FUNCTION_C) { return f->value.builtin(env, args); }

    int given = args->value.expr.count;
    int total = f->value.func.args->count;

    while (args->value.expr.count) {

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