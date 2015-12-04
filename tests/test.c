
#include "ptest.h"

void suite_types(void);
void suite_env(void);
void suite_expr(void);

void suite_builtin_math(void);
void suite_builtin_list(void);
void suite_builtin_ordering(void);
void suite_builtin_comparison(void);
void suite_builtin_conditionals(void);
void suite_builtin_magic(void);

void suite_ast(void);
void suite_ast_builtin_list(void);
void suite_ast_builtin_math(void);
void suite_ast_builtin_ordering(void);
void suite_ast_builtin_comparison(void);
void suite_ast_builtin_conditionals(void);

int main(int argc, char** argv) {
    (void) argc; (void) argv;
    pt_add_suite(suite_types);
    pt_add_suite(suite_env);
    pt_add_suite(suite_expr);

    pt_add_suite(suite_builtin_math);
    pt_add_suite(suite_builtin_list);
    pt_add_suite(suite_builtin_ordering);
    pt_add_suite(suite_builtin_comparison);
    pt_add_suite(suite_builtin_conditionals);
    pt_add_suite(suite_builtin_magic);

    pt_add_suite(suite_ast);
    pt_add_suite(suite_ast_builtin_list);
    pt_add_suite(suite_ast_builtin_math);
    pt_add_suite(suite_ast_builtin_ordering);
    pt_add_suite(suite_ast_builtin_comparison);
    pt_add_suite(suite_ast_builtin_conditionals);

    return pt_run();
}