#ifndef __CLISP_BUILTIN_FILESYSTEM__
#define __CLISP_BUILTIN_FILESYSTEM__

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <types.h>
#include <error.h>

clisp_chunk_t* clisp_builtin_fs_permission(clisp_expr_t* expr, clisp_env_t* env);

/**
 * File operations
 */
clisp_chunk_t* clisp_builtin_fs_file_exists(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_delete_file(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_rename_file(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_file_size(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_copy_file(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_write_file(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_read_file(clisp_expr_t* expr, clisp_env_t* env);

/**
 * Directory operations
 */
clisp_chunk_t* clisp_builtin_fs_directory_exists(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_delete_directory(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_rename_directory(clisp_expr_t* expr, clisp_env_t* env);
clisp_chunk_t* clisp_builtin_fs_create_directory(clisp_expr_t* expr, clisp_env_t* env);


#endif