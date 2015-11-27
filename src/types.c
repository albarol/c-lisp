
#include "types.h"

clisp_chunk_t*
clisp_chunk_new(clisp_chunk_type_t type) {
    clisp_chunk_t* chunk = malloc(sizeof(clisp_chunk_t));
    chunk->type = type;
    return chunk;
}

void
clisp_chunk_delete(clisp_chunk_t* chunk) {

}

clisp_chunk_t*
clisp_chunk_number(float num) {
    clisp_chunk_t* chunk = clisp_chunk_new(CLISP_NUMBER);
    chunk->number = num;
    return chunk;
}