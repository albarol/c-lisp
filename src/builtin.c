#include "builtin.h"


/**
 * Load all builtin functions
 */
void
clisp_builtin_load_functions(clisp_env_t* env) {

    clisp_env_put_builtin(env, "+", clisp_builtin_math_add, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "-", clisp_builtin_math_sub, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "*", clisp_builtin_math_mul, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "/", clisp_builtin_math_div, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "%", clisp_builtin_math_mod, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "^", clisp_builtin_math_pow, CLISP_FUNCTION_EAGER);

    clisp_env_put_builtin(env, "head", clisp_builtin_list_head, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "tail", clisp_builtin_list_tail, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "append", clisp_builtin_list_join, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "list?", clisp_builtin_list_eq, CLISP_FUNCTION_EAGER);

    clisp_env_put_builtin(env, ">",  clisp_builtin_ord_gt, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, ">=",  clisp_builtin_ord_gte, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "<",  clisp_builtin_ord_lt, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "<=",  clisp_builtin_ord_lte, CLISP_FUNCTION_EAGER);

    clisp_env_put_builtin(env, "eq",  clisp_builtin_cmp_eq, CLISP_FUNCTION_EAGER);
    clisp_env_put_builtin(env, "ne",  clisp_builtin_cmp_ne, CLISP_FUNCTION_EAGER);

    clisp_env_put_builtin(env, "if",  clisp_builtin_cond_if, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "def", clisp_builtin_cond_def, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "for", clisp_builtin_cond_for, CLISP_FUNCTION_LAZY);

    clisp_env_put_builtin(env, "display", clisp_builtin_magic_display, CLISP_FUNCTION_LAZY);
    clisp_env_put_builtin(env, "%exit", clisp_builtin_magic_exit, CLISP_FUNCTION_LAZY);
}