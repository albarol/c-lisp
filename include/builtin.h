#ifndef __CLISP_BUILTIN__
#define __CLISP_BUILTIN__

#include <builtin/bool.h>
#include <builtin/exception.h>
#include <builtin/io.h>
#include <builtin/list.h>
#include <builtin/magic.h>
#include <builtin/math.h>
#include <builtin/number.h>
#include <builtin/string.h>
#include <builtin/syntactic.h>

#include "ast.h"
#include "types.h"
#include "error.h"
#include "print.h"

void clisp_builtin_load_functions(clisp_env_t* env);

#endif