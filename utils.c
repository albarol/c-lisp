
#include "utils.h"

int
clisp_utils_isint(float number) {
    float fractpart, intpart;
    fractpart = modf(number, &intpart);
    return isless(fractpart, 0.01) ? 1 : 0;
}
