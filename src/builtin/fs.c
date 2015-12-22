
#include <builtin/fs.h>

clisp_chunk_t*
clisp_builtin_fs_file_exists(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(access(chunk->value.string, F_OK ) != -1);

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_fs_delete_file(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_chunk_bool(unlink(chunk->value.string) == 0);

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_fs_rename_file(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_STRING);

    clisp_chunk_t* src = clisp_expr_pop(expr, 0);
    clisp_chunk_t* dst = clisp_expr_take(expr, 0);

    clisp_chunk_t* result = clisp_chunk_bool(rename(src->value.string, dst->value.string) == 0);

    clisp_chunk_delete(src);
    clisp_chunk_delete(dst);
    return result;
}

clisp_chunk_t*
clisp_builtin_fs_copy_file(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_STRING);

    clisp_chunk_t* src = clisp_expr_pop(expr, 0);
    clisp_chunk_t* dst = clisp_expr_take(expr, 0);

    clisp_chunk_t* content = clisp_builtin_fs_read_file(clisp_expr_create(src), env);

    clisp_expr_t* call = clisp_expr_create(dst);
    clisp_expr_append(call, content);
    clisp_builtin_fs_write_file(call, env);

    return clisp_chunk_nil();
}

clisp_chunk_t*
clisp_builtin_fs_file_size(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = NULL;

    struct stat fileStat;
    if(stat(chunk->value.string, &fileStat) < 0) {
        result = clisp_chunk_error("File not found.");
    }
    else {
        result = clisp_chunk_number(fileStat.st_size);
    }

    clisp_chunk_delete(chunk);
    return result;
}

clisp_chunk_t*
clisp_builtin_fs_write_file(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 2);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);
    clisp_expr_assert_type(expr, expr->chunks[1]->type, CLISP_STRING);

    clisp_chunk_t* name = clisp_expr_pop(expr, 0);
    clisp_chunk_t* content = clisp_expr_take(expr, 0);

    clisp_chunk_t* result = NULL;
    FILE* fp = fopen(name->value.string, "w");

    if (fp == NULL) {
        result = clisp_chunk_error("Invalid file.");
    }
    else {
        fputs(content->value.string, fp);
        result = clisp_chunk_nil();
        fclose(fp);
    }


    clisp_chunk_delete(name);
    clisp_chunk_delete(content);
    return result;
}

clisp_chunk_t*
clisp_builtin_fs_read_file(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = clisp_utils_read_file(chunk->value.string);

    clisp_chunk_delete(chunk);
    return result;
}


clisp_chunk_t*
clisp_builtin_fs_permission(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_expr_assert_type(expr, expr->chunks[0]->type, CLISP_STRING);

    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_t* result = NULL;

    struct stat fileStat;
    if(stat(chunk->value.string, &fileStat) < 0) {
        result = clisp_chunk_error("File not found.");
    }
    else {
        char perm[5];
        sprintf(perm, "#%i%i%i%i",
                S_ISDIR(fileStat.st_mode),
                (fileStat.st_mode & S_IRWXU) >> 6,
                (fileStat.st_mode & S_IRWXG) >> 3,
                (fileStat.st_mode & S_IRWXO));
        result = clisp_chunk_str(perm);
    }

    clisp_chunk_delete(chunk);
    return result;
}