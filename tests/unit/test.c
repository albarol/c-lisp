
#include "ptest.h"

void suite_types(void);
void suite_env(void);
void suite_expr(void);

void suite_builtin_bool(void);
void suite_builtin_exception(void);
void suite_builtin_io(void);
void suite_builtin_list(void);
void suite_builtin_math(void);
void suite_builtin_number(void);
void suite_builtin_string(void);
void suite_builtin_string(void);
void suite_builtin_syntactic(void);

void suite_ast(void);

int main(int argc, char** argv) {
    (void) argc; (void) argv;

    // Core tests
    pt_add_suite(suite_types);
    pt_add_suite(suite_env);
    pt_add_suite(suite_expr);

    // Builtin tests
    pt_add_suite(suite_builtin_bool);
    pt_add_suite(suite_builtin_exception);
    pt_add_suite(suite_builtin_io);
    pt_add_suite(suite_builtin_list);
    pt_add_suite(suite_builtin_math);
    pt_add_suite(suite_builtin_number);
    pt_add_suite(suite_builtin_string);
    pt_add_suite(suite_builtin_syntactic);


    // AST tests
    pt_add_suite(suite_ast);

    return pt_run();
}