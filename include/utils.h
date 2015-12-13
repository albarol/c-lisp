#ifndef __CLISP_UTILS__
#define __CLISP_UTILS__

#include <math.h>
#include <stdlib.h>

#include <types.h>
#include <ast.h>
#include <parser.h>

clisp_chunk_t* clisp_utils_load_script(char* filename, clisp_env_t* env);

#endif
