
#include <builtin.h>

/**
 * Load all builtin functions
 */
void
clisp_builtin_load_functions(clisp_env_t* env) {

    /**
     * Boolean builtin functions
     */
    clisp_env_put_builtin(env, "eq", clisp_builtin_bool_equal, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "ne", clisp_builtin_bool_not_equal, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "bool?", clisp_builtin_bool_check_type, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "not", clisp_builtin_bool_not, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "and", clisp_builtin_bool_and, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "or", clisp_builtin_bool_or, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "xor", clisp_builtin_bool_xor, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "nand", clisp_builtin_bool_nand, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "nor", clisp_builtin_bool_nor, CLISP_FUNCTION_EAGER);

    /**
     * Exception builtin functions
     */
    clisp_env_put_builtin(env, "error", clisp_builtin_exception_error, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "error?", clisp_builtin_exception_is_error, CLISP_FUNCTION_EAGER);

    /**
     * IO builtin functions
     */
    clisp_env_put_builtin(env, "display", clisp_builtin_io_display, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "println", clisp_builtin_io_println, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "print", clisp_builtin_io_print, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "load", clisp_builtin_io_load, CLISP_FUNCTION_LAZY);

    /**
     * List builtin functions
     */
    clisp_env_put_builtin(env, "head", clisp_builtin_list_head, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "tail", clisp_builtin_list_tail, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "append", clisp_builtin_list_append, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "list?", clisp_builtin_list_check_type, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "length", clisp_builtin_list_length, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "empty?", clisp_builtin_list_empty, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "list", clisp_builtin_list_create, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "cons", clisp_builtin_list_cons, CLISP_FUNCTION_EAGER);

    /**
     * Magic builtin functions
     */
    clisp_env_put_builtin(env, "%exit", clisp_builtin_magic_exit, CLISP_FUNCTION_LAZY);


    /**
     * Math builtin functions
     */
    clisp_env_put_builtin(env, "+", clisp_builtin_math_add, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "-", clisp_builtin_math_sub, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "*", clisp_builtin_math_mul, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "/", clisp_builtin_math_div, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "%", clisp_builtin_math_mod, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "^", clisp_builtin_math_pow, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "round", clisp_builtin_math_round, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "floor", clisp_builtin_math_floor, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "ceil", clisp_builtin_math_ceil, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "sqrt", clisp_builtin_math_sqrt, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "log10", clisp_builtin_math_log10, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "log", clisp_builtin_math_log, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "sin", clisp_builtin_math_sin, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "cos", clisp_builtin_math_cos, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "tan", clisp_builtin_math_tan, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "abs", clisp_builtin_math_abs, CLISP_FUNCTION_EAGER);


    /**
     * Number builtin functions
     */
    clisp_env_put_builtin(env, "number?",  clisp_builtin_number_check_type, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "zero?",  clisp_builtin_number_is_zero, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "positive?",  clisp_builtin_number_is_positive, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "negative?",  clisp_builtin_number_is_negative, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "even?",  clisp_builtin_number_is_even, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "odd?",  clisp_builtin_number_is_odd, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, ">",  clisp_builtin_number_ordering_gt, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, ">=",  clisp_builtin_number_ordering_gte, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "<",  clisp_builtin_number_ordering_lt, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "<=",  clisp_builtin_number_ordering_lte, CLISP_FUNCTION_EAGER);


    /**
     * String builtin functions
     */
    clisp_env_put_builtin(env, "string?",  clisp_builtin_string_check_type, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "string->upper",  clisp_builtin_string_uppercase, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "string->lower",  clisp_builtin_string_lowercase, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "string->split",  clisp_builtin_string_split, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "string->concat",  clisp_builtin_string_concat, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "string->length",  clisp_builtin_string_length, CLISP_FUNCTION_EAGER);


    /**
     * Syntactic builtin functions
     */
    clisp_env_put_builtin(env, "if",  clisp_builtin_syntactic_if, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "def", clisp_builtin_syntactic_def, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "for", clisp_builtin_syntactic_for, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "cond", clisp_builtin_syntactic_cond, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "when", clisp_builtin_syntactic_when, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "unless", clisp_builtin_syntactic_unless, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "fn", clisp_builtin_syntactic_lambda, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "type", clisp_builtin_syntactic_type, CLISP_FUNCTION_EAGER);


#ifdef HAVE_FILESYSTEM
    /**
     * Fs builtin functions
     */
    clisp_env_put_builtin(env, "file-exists?", clisp_builtin_fs_file_exists, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-delete", clisp_builtin_fs_delete_file, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-copy", clisp_builtin_fs_copy_file, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-rename", clisp_builtin_fs_rename_file, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-size", clisp_builtin_fs_file_size, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-read", clisp_builtin_fs_read_file, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-write", clisp_builtin_fs_write_file, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "file-or-directory-permission", clisp_builtin_fs_permission, CLISP_FUNCTION_EAGER);

    clisp_env_put_builtin(env, "dir-exists?", clisp_builtin_fs_directory_exists, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "dir-delete", clisp_builtin_fs_delete_directory, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "dir-rename", clisp_builtin_fs_rename_directory, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "dir-create", clisp_builtin_fs_create_directory, CLISP_FUNCTION_EAGER);
#endif //_HAVE_FILESYSTEM
}
