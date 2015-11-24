#ifndef __CLISP_TOKEN__
#define __CLISP_TOKEN__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


struct clisp_token_t;
struct clisp_env_t;
typedef struct clisp_token_t clisp_token_t;
typedef struct clisp_env_t clisp_env_t;

typedef clisp_token_t* (*clisp_function_t)(clisp_env_t*, clisp_token_t*);


typedef enum {
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_FUNCTION,
    TOKEN_SEXPRESSION,
    TOKEN_QEXPRESSION
} clisp_token_type_t;


struct clisp_token_t {
    clisp_token_type_t type;

    long number;
    char* symbol;
    char* error;

    clisp_function_t builtin;
    clisp_env_t* env;
    clisp_token_t* formals;
    clisp_token_t* body;

    int count;
    clisp_token_t** tokens;
};

clisp_token_t* clisp_token_number(long number);
clisp_token_t* clisp_token_error(char* error, ...);
clisp_token_t* clisp_token_symbol(char* symbol);
clisp_token_t* clisp_token_sexpr(void);
clisp_token_t* clisp_token_qexpr(void);
clisp_token_t* clisp_token_function(clisp_function_t function);
clisp_token_t* clisp_token_lambda(clisp_token_t* formals, clisp_token_t* body);
clisp_token_t* clisp_token_call(clisp_env_t* env, clisp_token_t* function, clisp_token_t* args);

int clisp_token_cmp(clisp_token_t* first, clisp_token_t* second);

void clisp_token_del(clisp_token_t* token);
clisp_token_t* clisp_token_append(clisp_token_t* super, clisp_token_t* child);
clisp_token_t* clisp_token_pop(clisp_token_t* super, int position);
clisp_token_t* clisp_token_take(clisp_token_t* super, int position);
clisp_token_t* clisp_token_join(clisp_token_t* super, clisp_token_t* child);
clisp_token_t* clisp_token_copy(clisp_token_t* token);

#endif
