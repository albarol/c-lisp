#ifndef __CLISP_PRINT__
#define __CLISP_PRINT__

#include <stdio.h>
#include <mpc.h>

#include "token.h"
#include "utils.h"

void clisp_print_write(clisp_chunk_t* token);
void clisp_print_writeln(clisp_chunk_t* token);
void clisp_print_write_expr(clisp_chunk_expr_t* expr, char open, char close);
void clisp_print_write_str(clisp_chunk_t* token);
char* clisp_print_type_name(clisp_chunk_type_t token);

#endif
