#ifndef __CLISP_TYPES__
#define __CLISP_TYPES__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

struct clisp_chunk_t;
struct clisp_env_t;
typedef struct clisp_chunk_t clisp_chunk_t;
typedef struct clisp_env_t clisp_env_t;

typedef clisp_chunk_t* (* clisp_builtin_t)(clisp_env_t*, clisp_chunk_t*);


typedef enum {
    CLISP_NIL = 1,
    CLISP_TRUE = 2,
    CLISP_FALSE = 4,
    CLISP_ERROR = 8,
    CLISP_NUMBER = 16,
    CLISP_SYMBOL = 32,
    CLISP_STRING = 64,
    CLISP_LIST = 128,
    CLISP_FUNCTION = 256,
    CLISP_FUNCTION_C = 512,
    CLISP_ATOM = 1024,
    TOKEN_QEXPRESSION = 2048
} clisp_chunk_type_t;


struct clisp_chunk_t {
    clisp_chunk_type_t type;

    float number;
    char* symbol;
    char* error;
    char* str;

    clisp_builtin_t builtin;
    clisp_env_t* env;
    clisp_chunk_t* formals;
    clisp_chunk_t* body;

    int count;
    clisp_chunk_t** tokens;
};

clisp_chunk_t* clisp_chunk_new(clisp_chunk_type_t type);
void clisp_chunk_delete(clisp_chunk_t* chunk);

clisp_chunk_t* clisp_chunk_number(float num);
clisp_chunk_t* clisp_chunk_symbol(char* symbol);
clisp_chunk_t* clisp_chunk_str(char* str);
clisp_chunk_t* clisp_chunk_error(char* error, ...);
clisp_chunk_t* clisp_chunk_sexpr(void);
clisp_chunk_t* clisp_chunk_qexpr(void);
clisp_chunk_t* clisp_chunk_builtin(clisp_builtin_t function);

#endif