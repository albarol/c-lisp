#ifndef __CLISP_PRINT__
#define __CLISP_PRINT__

#include <stdio.h>

#include "token.h"

void clisp_print_write(clisp_token_t* token);
void clisp_print_writeln(clisp_token_t* token);
void clisp_print_write_expr(clisp_token_t* token, char open, char close);
char* clisp_print_type_name(clisp_token_type_t token);

#endif
