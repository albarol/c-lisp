
#include "ptest.h"

#include "../src/types.h"

void test_new_chunk_number(void) {
    clisp_chunk_t* chunk = clisp_chunk_number(5);

    PT_ASSERT(chunk->number == 5);
    PT_ASSERT(chunk->type == CLISP_NUMBER);
}



void suite_types(void) {
    pt_add_test(test_new_chunk_number, "Test New Number", "Suite Types");
}