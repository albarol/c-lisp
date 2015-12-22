#ifndef __CLISP_UTILS__
#define __CLISP_UTILS__

#include <math.h>
#include <stdlib.h>

#include <types.h>
#include <ast.h>
#include <parser.h>

#define CHUNK_SIZE 4096

clisp_chunk_t* clisp_utils_load_script(char* filename, clisp_env_t* env);
clisp_chunk_t* clisp_utils_read_file(const char* filename);

#endif
