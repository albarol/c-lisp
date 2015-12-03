#include "builtin.h"


/**
 * Load all builtin functions
 */
void
clisp_builtin_load_functions(clisp_env_t* env) {

    clisp_env_put_builtin(env, "+", clisp_builtin_math_add);
    clisp_env_put_builtin(env, "-", clisp_builtin_math_sub);
    clisp_env_put_builtin(env, "*", clisp_builtin_math_mul);
    clisp_env_put_builtin(env, "/", clisp_builtin_math_div);
    clisp_env_put_builtin(env, "%", clisp_builtin_math_mod);
    clisp_env_put_builtin(env, "^", clisp_builtin_math_pow);

    clisp_env_put_builtin(env, "head", clisp_builtin_list_head);
    clisp_env_put_builtin(env, "tail", clisp_builtin_list_tail);
    clisp_env_put_builtin(env, "append", clisp_builtin_list_join);
    clisp_env_put_builtin(env, "list?", clisp_builtin_list_eq);

    clisp_env_put_builtin(env, ">",  clisp_builtin_ord_gt);
    clisp_env_put_builtin(env, ">=",  clisp_builtin_ord_gte);
    clisp_env_put_builtin(env, "<",  clisp_builtin_ord_lt);
    clisp_env_put_builtin(env, "<=",  clisp_builtin_ord_lte);

    clisp_env_put_builtin(env, "==",  clisp_builtin_cmp_eq);
    clisp_env_put_builtin(env, "!=",  clisp_builtin_cmp_ne);

    clisp_env_put_builtin(env, "if",  clisp_builtin_cond_if);
    clisp_env_put_builtin(env, "def", clisp_builtin_cond_def);
}