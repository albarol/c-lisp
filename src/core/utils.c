
#include "utils.h"

int
clisp_utils_isint(float number) {
    float diff = number - (int)number;
    return diff != 0;
}
