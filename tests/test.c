
#include "ptest.h"

void suite_types(void);

int main(int argc, char** argv) {
    (void) argc; (void) argv;
    pt_add_suite(suite_types);
    return pt_run();
}