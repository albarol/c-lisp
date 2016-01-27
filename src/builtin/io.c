
#include <builtin/io.h>
#include <types.h>

clisp_chunk_t*
clisp_builtin_io_display(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);

    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
    }

    printf("%s -> ", clisp_print_type_name(chunk->type));
    clisp_print_writeln(chunk);
    clisp_chunk_free(chunk);
    return clisp_chunk_nil();
}

clisp_chunk_t*
clisp_builtin_io_print(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);

    clisp_chunk_t* chunk = clisp_expr_pop(expr, 0);


    if (chunk->type == CLISP_SYMBOL) {
        chunk = clisp_env_get(env, chunk);
        clisp_print_writeln(chunk);
        clisp_chunk_free(chunk);
    }
    else if (chunk->type == CLISP_EXPR) {
        clisp_expr_t* call = clisp_expr_create(chunk);
        clisp_chunk_t* result = clisp_eval_ast(call, env);
        clisp_print_writeln(result);
        clisp_chunk_free(result);
    }
    else {
        clisp_print_writeln(chunk);
        clisp_chunk_free(chunk);
    }

    return clisp_chunk_nil();
}

clisp_chunk_t*
clisp_builtin_io_load(clisp_expr_t* expr, clisp_env_t* env) {
    clisp_expr_assert_count(expr, 1);
    clisp_chunk_t* chunk = clisp_expr_take(expr, 0);
    clisp_chunk_assert_type(chunk, chunk->type, CLISP_STRING);

    clisp_chunk_t* result =  clisp_utils_load_script(chunk->value.string, env);
    clisp_chunk_free(chunk);
    return result;
}