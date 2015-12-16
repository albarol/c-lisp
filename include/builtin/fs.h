#ifndef __CLISP_BUILTIN_FILESYSTEM__
#define __CLISP_BUILTIN_FILESYSTEM__

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_fs_file_exists(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_delete_file(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_rename_file(clisp_expr_t* expr, clisp_env_t* env);

#endif