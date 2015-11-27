#include "builtin.h"


/**
 * Load all builtin functions
 */
void
clisp_builtin_load_functions(clisp_env_t* env) {

    clisp_env_put_function(env, "+", clisp_builtin_math_add);
    clisp_env_put_function(env, "-", clisp_builtin_math_sub);
    clisp_env_put_function(env, "*", clisp_builtin_math_mul);
    clisp_env_put_function(env, "/", clisp_builtin_math_div);
    clisp_env_put_function(env, "%", clisp_builtin_math_mod);
    clisp_env_put_function(env, "^", clisp_builtin_math_pow);

    clisp_env_put_function(env, "list", clisp_builtin_list_create);
    clisp_env_put_function(env, "head", clisp_builtin_list_head);
    clisp_env_put_function(env, "tail", clisp_builtin_list_tail);
    clisp_env_put_function(env, "join", clisp_builtin_list_join);

    clisp_env_put_function(env, "eval", clisp_builtin_eval);
    clisp_env_put_function(env, "def", clisp_builtin_define);
    clisp_env_put_function(env, "=", clisp_builtin_assign);
    clisp_env_put_function(env, "\\",  clisp_builtin_lambda);

    clisp_env_put_function(env, ">",  clisp_builtin_ord_gt);
    clisp_env_put_function(env, ">=",  clisp_builtin_ord_gte);
    clisp_env_put_function(env, "<",  clisp_builtin_ord_lt);
    clisp_env_put_function(env, "<=",  clisp_builtin_ord_lte);

    clisp_env_put_function(env, "==",  clisp_builtin_cmp_eq);
    clisp_env_put_function(env, "!=",  clisp_builtin_cmp_ne);
    clisp_env_put_function(env, "if",  clisp_builtin_cmp_if);
}

/**
 * Define functions for arithmetic operations
 */
clisp_chunk_t*
clisp_builtin_math(clisp_env_t* env, clisp_chunk_t* token, char* op) {

    for (int i = 0; i < token->count; i++) {
        clisp_chunk_t* item = token->tokens[i];

        if (item->type != CLISP_NUMBER) {
            clisp_chunk_delete(token);
            return clisp_chunk_error("Cannot operate on non-number!");
        }
    }

    clisp_chunk_t* first = clisp_token_pop(token, 0);

    if ((strcmp(op, "-") == 0) && token->count == 0) {
        first->value.number = -first->value.number;
    }

    while (token->count > 0) {

        clisp_chunk_t* second = clisp_token_pop(token, 0);

        if (strcmp(op, "+") == 0) { first->value.number += second->value.number; }
        if (strcmp(op, "-") == 0) { first->value.number -= second->value.number; }
        if (strcmp(op, "*") == 0) { first->value.number *= second->value.number; }
        if (strcmp(op, "%") == 0) { first->value.number = fmod(first->value.number, second->value.number); }
        if (strcmp(op, "^") == 0) {
            float base = first->value.number;
            for (int i = 1; i < second->value.number; i++) {
                first->value.number *= base;
            }
        }
        if (strcmp(op, "/") == 0) {
            if (second->value.number == 0) {
                clisp_chunk_delete(first);
                clisp_chunk_delete(second);
                first = clisp_chunk_error("Division By Zero!");
                break;
            }
            first->value.number /= second->value.number;
        }

        clisp_chunk_delete(second);
    }

    clisp_chunk_delete(token);
    return first;
}


clisp_chunk_t*
clisp_builtin_math_add(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "+");
}

clisp_chunk_t*
clisp_builtin_math_sub(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "-");
}

clisp_chunk_t*
clisp_builtin_math_mul(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "*");
}

clisp_chunk_t*
clisp_builtin_math_div(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "/");
}

clisp_chunk_t*
clisp_builtin_math_mod(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "%");
}

clisp_chunk_t*
clisp_builtin_math_pow(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_math(env, token, "^");
}

/**
 * Define functions for ordering
 */
clisp_chunk_t*
clisp_builtin_ord(clisp_env_t* env, clisp_chunk_t* token, char* op) {
    clisp_assert_count(token, 2);
    clisp_assert_type(token, token->tokens[0]->type, CLISP_NUMBER);
    clisp_assert_type(token, token->tokens[1]->type, CLISP_NUMBER);

    int result;
    if (strcmp(op, ">") == 0) {
        result = (token->tokens[0]->value.number > token->tokens[1]->value.number);
    }
    else if (strcmp(op, "<") == 0) {
        result = (token->tokens[0]->value.number < token->tokens[1]->value.number);
    }
    else if (strcmp(op, ">=") == 0) {
        result = (token->tokens[0]->value.number >= token->tokens[1]->value.number);
    }
    else if (strcmp(op, "<=") == 0) {
        result = (token->tokens[0]->value.number <= token->tokens[1]->value.number);
    }

    clisp_chunk_delete(token);
    return clisp_chunk_number(result);
}

clisp_chunk_t*
clisp_builtin_ord_gt(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, ">");
}

clisp_chunk_t*
clisp_builtin_ord_lt(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, "<");
}

clisp_chunk_t*
clisp_builtin_ord_gte(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, ">=");
}

clisp_chunk_t*
clisp_builtin_ord_lte(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_ord(env, token, "<=");
}



/**
 * Define functions for comparison
 */

clisp_chunk_t*
clisp_builtin_cmp(clisp_env_t* env, clisp_chunk_t* token, char* op) {
    clisp_assert_count(token, 2);

    int result;
    if (strcmp(op, "==") == 0) {
        result = clisp_token_cmp(token->tokens[0], token->tokens[1]);
    }

    if (strcmp(op, "!=") == 0) {
        result = !clisp_token_cmp(token->tokens[0], token->tokens[1]);
    }
    clisp_chunk_delete(token);
    return clisp_chunk_number(result);
}

clisp_chunk_t*
clisp_builtin_cmp_eq(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_cmp(env, token, "==");
}

clisp_chunk_t*
clisp_builtin_cmp_ne(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_cmp(env, token, "!=");
}

clisp_chunk_t*
clisp_builtin_cmp_if(clisp_env_t* env, clisp_chunk_t* token) {
    clisp_assert_count(token, 3);
    clisp_assert_type(token, token->tokens[0]->type, CLISP_NUMBER);
    clisp_assert_type(token, token->tokens[1]->type, TOKEN_QEXPRESSION);
    clisp_assert_type(token, token->tokens[2]->type, TOKEN_QEXPRESSION);

    clisp_chunk_t* new_token;
    token->tokens[1]->type = CLISP_ATOM;
    token->tokens[2]->type = CLISP_ATOM;

    if (token->tokens[0]->value.number) {
        new_token = clisp_ast_eval(env, clisp_token_pop(token, 1));
    } else {
        new_token = clisp_ast_eval(env, clisp_token_pop(token, 2));
    }

    clisp_chunk_delete(token);
    return new_token;
}


/**
 * Define functions for lists
 */
clisp_chunk_t*
clisp_builtin_list_create(clisp_env_t* env, clisp_chunk_t* token) {
    token->type = TOKEN_QEXPRESSION;
    return token;
}

clisp_chunk_t*
clisp_builtin_list_head(clisp_env_t* env, clisp_chunk_t* token) {
    clisp_assert_count(token, 1);

    clisp_chunk_t* list = token->tokens[0];
    clisp_assert(token, list->type == TOKEN_QEXPRESSION,
                 "Function 'head' passed incorrect types");
    clisp_assert(token, list->count != 0,
                 "Function 'head' passed {}!");

    list = clisp_token_take(token, 0);

    while (list->count > 1) {
        clisp_chunk_delete(clisp_token_pop(list, 1));
    }
    return list;
}

clisp_chunk_t*
clisp_builtin_list_tail(clisp_env_t* env, clisp_chunk_t* token) {
    clisp_assert_count(token, 1);

    clisp_chunk_t* list = token->tokens[0];
    clisp_assert(token, list->type == TOKEN_QEXPRESSION,
                 "Function 'tail' passed incorrect types");
    clisp_assert(token, list->count != 0,
                 "Function 'tail' passed {}!");

    list = clisp_token_take(token, 0);
    clisp_chunk_delete(clisp_token_pop(list, 0));
    return list;
}

clisp_chunk_t*
clisp_builtin_list_join(clisp_env_t* env, clisp_chunk_t* token) {

    for (int i = 0; i < token->count; i++) {
        clisp_chunk_t* child = token->tokens[i];
        clisp_assert_type(token, child->type, TOKEN_QEXPRESSION);
    }

    clisp_chunk_t* child = clisp_token_pop(token, 0);

    while (token->count) {
        child = clisp_token_join(child, clisp_token_pop(token, 0));
    }

    clisp_chunk_delete(token);
    return child;
}


clisp_chunk_t*
clisp_builtin_eval(clisp_env_t* env, clisp_chunk_t* token) {
    clisp_assert_count(token, 1);

    clisp_chunk_t* child = token->tokens[0];
    clisp_assert_type(token, child->type, TOKEN_QEXPRESSION)

    child = clisp_token_take(token, 0);
    child->type = CLISP_ATOM;
    return clisp_ast_eval(env, child);
}


/**
 * Define functions for create functions
 */
clisp_chunk_t*
clisp_builtin_var_set(clisp_env_t* env, clisp_chunk_t* token, char* function) {

    clisp_chunk_t* child = token->tokens[0];
    clisp_assert_type(token, child->type, TOKEN_QEXPRESSION);

    for (int i = 0; i < child->count; i++) {
        clisp_assert(token, child->tokens[i]->type, CLISP_SYMBOL)
    }

    clisp_assert(token, child->count == token->count - 1,
                 "Function cannot define incorrect "
                         "number of values to symbols")

    for (int i = 0; i < child->count; i++) {
        if (strcmp(function, "=") == 0) {
            clisp_env_define(env, child->tokens[i], token->tokens[i+1]);
        }

        if (strcmp(function, "def") == 0) {
            clisp_env_put(env, child->tokens[i], token->tokens[i+1]);
        }
    }

    clisp_chunk_delete(token);
    return clisp_chunk_sexpr();
}

clisp_chunk_t*
clisp_builtin_define(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_var_set(env, token, "def");
}

clisp_chunk_t*
clisp_builtin_assign(clisp_env_t* env, clisp_chunk_t* token) {
    return clisp_builtin_var_set(env, token, "=");
}


clisp_chunk_t*
clisp_builtin_lambda(clisp_env_t* env, clisp_chunk_t* token) {

    clisp_assert_count(token, 2);
    clisp_assert_type(token, token->tokens[0]->type, TOKEN_QEXPRESSION);
    clisp_assert_type(token, token->tokens[1]->type, TOKEN_QEXPRESSION);

    for (int i = 0; i < token->tokens[0]->count; i++) {
        clisp_chunk_t* child = token->tokens[0]->tokens[i];
        clisp_assert(token, child->type = CLISP_SYMBOL,
                     "Cannot define non-symbol. Got: %s, Expected: %s",
                     clisp_print_type_name(child->type), clisp_print_type_name(CLISP_SYMBOL));
    }

    clisp_chunk_t* formals = clisp_token_pop(token, 0);
    clisp_chunk_t* body = clisp_token_pop(token, 0);
    clisp_chunk_delete(token);

    return clisp_token_lambda(formals, body);
}
