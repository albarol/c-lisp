#ifndef __CLISP_TYPES__
#define __CLISP_TYPES__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

#include <common.h>


struct clisp_chunk_t;
struct clisp_env_t;
struct clisp_expr_t;
typedef struct clisp_chunk_t clisp_chunk_t;
typedef struct clisp_env_t clisp_env_t;
typedef struct clisp_expr_t clisp_expr_t;


/*
 * Lisp definitions
 */

typedef enum {
    CLISP_NIL = 1,
    CLISP_BOOL = 2,
    CLISP_NUMBER = 4,
    CLISP_SYMBOL = 8,
    CLISP_STRING = 16,
    CLISP_LIST = 32,
    CLISP_FUNCTION = 64,
    CLISP_FUNCTION_C = 128,
    CLISP_ERROR = 256,
    CLISP_EXPR = 512,
    CLISP_TYPE = CLISP_NIL | CLISP_BOOL |
                 CLISP_NUMBER | CLISP_SYMBOL |
                 CLISP_STRING | CLISP_LIST |
                 CLISP_FUNCTION | CLISP_FUNCTION_C
} clisp_chunk_type_t;

typedef enum {
    CLISP_FUNCTION_LAZY = 1,
    CLISP_FUNCTION_EAGER = 2
} clisp_function_type;

typedef clisp_chunk_t* (* clisp_builtin_t)(clisp_expr_t* expr, clisp_env_t* env);

struct clisp_chunk_t {
    clisp_chunk_type_t type;

    union {
        bool boolean;
        float number;
        char* string;
        clisp_expr_t* list;

        struct {
            clisp_builtin_t body;
            clisp_function_type ftype;
        } builtin;

        struct {
            clisp_env_t* env;
            clisp_chunk_t* args;
            clisp_chunk_t* body;
            int count;
        } func;
    } value;
};

struct clisp_expr_t {
    int count;
    clisp_chunk_t** chunks;
};

clisp_chunk_t* clisp_chunk_new(clisp_chunk_type_t type);
void clisp_chunk_free(clisp_chunk_t* chunk);

clisp_chunk_t* clisp_chunk_copy(clisp_chunk_t* metadata);
bool clisp_chunk_cmp(clisp_chunk_t* first, clisp_chunk_t* second);

clisp_chunk_t* clisp_chunk_nil();
clisp_chunk_t* clisp_chunk_number(float num);
clisp_chunk_t* clisp_chunk_symbol(char* symbol);
clisp_chunk_t* clisp_chunk_str(char* str);
clisp_chunk_t* clisp_chunk_error(char* error, ...);
clisp_chunk_t* clisp_chunk_list(void);
clisp_chunk_t* clisp_chunk_bool(bool value);
clisp_chunk_t* clisp_chunk_builtin(clisp_builtin_t function, clisp_function_type ftype);
clisp_chunk_t* clisp_chunk_function(clisp_chunk_t* args, clisp_chunk_t* body);
clisp_chunk_t* clisp_chunk_expr();


/*
 * Expression definitions
 */
clisp_expr_t* clisp_expr_new();
clisp_expr_t* clisp_expr_create(clisp_chunk_t* chunk);
        clisp_expr_t* clisp_expr_append(clisp_expr_t* expr, clisp_chunk_t* child);
clisp_chunk_t* clisp_expr_pop(clisp_expr_t* expr, int position);
void clisp_expr_remove(clisp_expr_t* expr, int position);
clisp_chunk_t* clisp_expr_take(clisp_expr_t* super, int position);
clisp_expr_t* clisp_expr_join(clisp_expr_t* first, clisp_expr_t* second);
void clisp_expr_free(clisp_expr_t* expr);

/*
 * Env definitions
 */

struct clisp_env_t {
    clisp_env_t* parent;
    int count;
    char** symbols;
    clisp_chunk_t** chunks;
};

clisp_env_t* clisp_env_new(void);
clisp_env_t* clisp_env_copy(clisp_env_t* env);
void clisp_env_free(clisp_env_t* env);

clisp_chunk_t* clisp_env_get(clisp_env_t* env, clisp_chunk_t* token);
clisp_chunk_t* clisp_env_remove(clisp_env_t* env, clisp_chunk_t* token);
void clisp_env_put(clisp_env_t* env, clisp_chunk_t* symbol, clisp_chunk_t* value);
void clisp_env_put_builtin(clisp_env_t* env, char* symbol, clisp_builtin_t builtin, clisp_function_type type);


#endif