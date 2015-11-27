
#include "ptest.h"

void suite_types(void);
void suite_env(void);

int main(int argc, char** argv) {
    (void) argc; (void) argv;
    pt_add_suite(suite_types);
    pt_add_suite(suite_env);
    return pt_run();
}