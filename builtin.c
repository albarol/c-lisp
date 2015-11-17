
#include "builtin.h"


void
clisp_builtin_load_functions(clisp_env_t* env) {

    clisp_env_put_function(env, "+", clisp_builtin_arithmetic_add);
    clisp_env_put_function(env, "-", clisp_builtin_arithmetic_sub);
    clisp_env_put_function(env, "*", clisp_builtin_arithmetic_mul);
    clisp_env_put_function(env, "/", clisp_builtin_arithmetic_div);
    clisp_env_put_function(env, "mod", clisp_builtin_arithmetic_mod);

    clisp_env_put_function(env, "list", clisp_builtin_list_create);
    clisp_env_put_function(env, "head", clisp_builtin_list_head);
    clisp_env_put_function(env, "tail", clisp_builtin_list_tail);
    clisp_env_put_function(env, "join", clisp_builtin_list_join);

    clisp_env_put_function(env, "eval", clisp_builtin_eval);

    clisp_env_put_function(env, "def", clisp_builtin_define);
}

clisp_token_t*
clisp_builtin_arithmetic(clisp_env_t* env, clisp_token_t* token, char* op) {

    for (int i = 0; i < token->count; i++) {
        clisp_token_t* item = token->tokens[i];

        if (item->type != TOKEN_NUMBER) {
            clisp_token_del(token);
            return clisp_token_error("Cannot operate on non-number!");
        }
    }

    clisp_token_t* first = clisp_token_pop(token, 0);

    if ((strcmp(op, "-") == 0) && token->count == 0) {
        first->number = -first->number;
    }

    while (token->count > 0) {

        clisp_token_t* second = clisp_token_pop(token, 0);

        if (strcmp(op, "+") == 0) { first->number += second->number; }
        if (strcmp(op, "-") == 0) { first->number -= second->number; }
        if (strcmp(op, "*") == 0) { first->number *= second->number; }
        if (strcmp(op, "mod") == 0) { first->number %= second->number; }
        if (strcmp(op, "/") == 0) {
            if (second->number == 0) {
                clisp_token_del(first);
                clisp_token_del(second);
                first = clisp_token_error("Division By Zero!");
                break;
            }
            first->number /= second->number;
        }

        clisp_token_del(second);
    }

    clisp_token_del(token);
    return first;
}


clisp_token_t*
clisp_builtin_arithmetic_add(clisp_env_t* env, clisp_token_t* token) {
    return clisp_builtin_arithmetic(env, token, "+");
}

clisp_token_t*
clisp_builtin_arithmetic_sub(clisp_env_t* env, clisp_token_t* token) {
    return clisp_builtin_arithmetic(env, token, "-");
}

clisp_token_t*
clisp_builtin_arithmetic_mul(clisp_env_t* env, clisp_token_t* token) {
    return clisp_builtin_arithmetic(env, token, "*");
}

clisp_token_t*
clisp_builtin_arithmetic_div(clisp_env_t* env, clisp_token_t* token) {
    return clisp_builtin_arithmetic(env, token, "/");
}

clisp_token_t*
clisp_builtin_arithmetic_mod(clisp_env_t* env, clisp_token_t* token) {
    return clisp_builtin_arithmetic(env, token, "mod");
}


clisp_token_t*
clisp_builtin_list_create(clisp_env_t* env, clisp_token_t* token) {
    token->type = TOKEN_QEXPRESSION;
    return token;
}


clisp_token_t*
clisp_builtin_list_head(clisp_env_t* env, clisp_token_t* token) {
    clisp_assert(token, token->count == 1,
                 "Function 'head' passed too many arguments!");

    clisp_token_t* list = token->tokens[0];
    clisp_assert(token, list->type == TOKEN_QEXPRESSION,
                 "Function 'head' passed incorrect types");
    clisp_assert(token, list->count != 0,
                 "Function 'head' passed {}!");

    list = clisp_token_take(token, 0);

    while (list->count > 1) {
        clisp_token_del(clisp_token_pop(list, 1));
    }
    return list;
}

clisp_token_t*
clisp_builtin_list_tail(clisp_env_t* env, clisp_token_t* token) {
    clisp_assert(token, token->count == 1,
                 "Function 'tail' passed too many arguments!");
    clisp_token_t* list = token->tokens[0];
    clisp_assert(token, list->type == TOKEN_QEXPRESSION,
                 "Function 'tail' passed incorrect types");
    clisp_assert(token, list->count != 0,
                 "Function 'tail' passed {}!");

    list = clisp_token_take(token, 0);
    clisp_token_del(clisp_token_pop(list, 0));
    return list;
}

clisp_token_t*
clisp_builtin_list_join(clisp_env_t* env, clisp_token_t* token) {

    for (int i = 0; i < token->count; i++) {
        clisp_token_t* child = token->tokens[i];
        clisp_assert(token, child->type == TOKEN_QEXPRESSION,
                     "Function 'join' passed incorrect type");
    }

    clisp_token_t* child = clisp_token_pop(token, 0);

    while (token->count) {
        child = clisp_token_join(child, clisp_token_pop(token, 0));
    }

    clisp_token_del(token);
    return child;
}


clisp_token_t*
clisp_builtin_eval(clisp_env_t* env, clisp_token_t* token) {
    clisp_assert(token, token->count == 1,
                 "Function 'eval' passed too many arguments! "
                 "Passed: %li, Expected: %li", token->count, 1);

    clisp_token_t* child = token->tokens[0];
    clisp_assert(token, token->type == TOKEN_QEXPRESSION,
                 "Function 'eval' passed incorrect types "
                 "Passed: %s, Expected: %s", clisp_print_type_name(token->type), clisp_print_type_name(TOKEN_QEXPRESSION));

    child = clisp_token_take(token, 0);
    child->type = TOKEN_QEXPRESSION;
    return clisp_ast_eval(env, child);
}


clisp_token_t*
clisp_builtin_define(clisp_env_t* env, clisp_token_t* token) {
    clisp_assert(token, token->tokens[0]->type == TOKEN_QEXPRESSION,
                 "Function 'def' passed incorrect type "
                 "Passed: %s, Expected: %s", clisp_print_type_name(token->type), clisp_print_type_name(TOKEN_QEXPRESSION));

    clisp_token_t* child = token->tokens[0];

    for (int i = 0; i < child->count; i++) {
        clisp_assert(token, child->tokens[i]->type == TOKEN_SYMBOL,
                     "Function 'def' cannot define non-symbol");
    }

    clisp_assert(token, child->count == token->count-1,
                 "Function 'def' cannot define incorrect "
                 "number of values to symbols");

    for (int i = 0; i < child->count; i++) {
        clisp_env_put(env, child->tokens[i], token->tokens[i+1]);
    }

    clisp_token_del(token);
    return clisp_token_sexpr();
}
