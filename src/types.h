#ifndef __CLISP_TYPES__
#define __CLISP_TYPES__

struct clisp_chunk_t;
struct clisp_env_t;
typedef struct clisp_chunk_t clisp_chunk_t;
typedef struct clisp_env_t clisp_env_t;

typedef clisp_chunk_t* (*clisp_function_t)(clisp_env_t*, clisp_chunk_t*);


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

    clisp_function_t builtin;
    clisp_env_t* env;
    clisp_chunk_t* formals;
    clisp_chunk_t* body;

    int count;
    clisp_chunk_t** tokens;
};


#endif