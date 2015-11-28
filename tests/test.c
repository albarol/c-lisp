
#include "ptest.h"

void suite_types(void);
void suite_env(void);
void suite_expr(void);

void suite_builtin_math(void);

int main(int argc, char** argv) {
    (void) argc; (void) argv;
    pt_add_suite(suite_types);
    pt_add_suite(suite_env);
    pt_add_suite(suite_expr);
    pt_add_suite(suite_builtin_math);
    return pt_run();
}