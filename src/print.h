#ifndef __CLISP_PRINT__
#define __CLISP_PRINT__

#include <stdio.h>
#include <mpc.h>

#include "token.h"
#include "utils.h"

void clisp_print_write(clisp_token_t* token);
void clisp_print_writeln(clisp_token_t* token);
void clisp_print_write_expr(clisp_token_t* token, char open, char close);
void clisp_print_write_str(clisp_token_t* token);
char* clisp_print_type_name(clisp_chunk_type token);

#endif
