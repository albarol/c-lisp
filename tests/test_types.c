
#include "ptest.h"

#include "../src/types.h"


PT_SUITE(suite_types) {

    PT_TEST(test_new_chunk_number) {
        clisp_chunk_t* chunk = clisp_chunk_number(5);

        PT_ASSERT(chunk->number == 5);
        PT_ASSERT(chunk->type == CLISP_NUMBER);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_symbol) {
        clisp_chunk_t* chunk = clisp_chunk_symbol("symbol");

        PT_ASSERT(strcmp(chunk->symbol, "symbol") == 0);
        PT_ASSERT(chunk->type == CLISP_SYMBOL);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_string) {
        clisp_chunk_t* chunk = clisp_chunk_str("string");

        PT_ASSERT(strcmp(chunk->str, "string") == 0);
        PT_ASSERT(chunk->type == CLISP_STRING);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_error) {
        clisp_chunk_t* chunk = clisp_chunk_error("Error %i", 1);

        PT_ASSERT(strcmp(chunk->error, "Error 1") == 0);
        PT_ASSERT(chunk->type == CLISP_ERROR);

        clisp_chunk_delete(chunk);
    }

    PT_TEST(test_new_chunk_sexpr) {
        clisp_chunk_t* chunk = clisp_chunk_sexpr();

        PT_ASSERT(chunk->count == 0);
        PT_ASSERT(chunk->type == CLISP_ATOM);

        clisp_chunk_delete(chunk);
    }
}