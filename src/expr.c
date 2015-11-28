
#include "types.h"

clisp_chunk_t*
clisp_expr_append(clisp_chunk_t* super, clisp_chunk_t* child) {
    super->value.expr.count++;
    super->value.expr.chunks = realloc(super->value.expr.chunks, sizeof(clisp_chunk_t*) * super->value.expr.count);
    super->value.expr.chunks[super->value.expr.count-1] = child;
    return super;
}


clisp_chunk_t*
clisp_expr_pop(clisp_chunk_t* super, int position) {

    clisp_chunk_t* item = super->value.expr.chunks[position];

    memmove(&super->value.expr.chunks[position], &super->value.expr.chunks[position + 1],
            sizeof(clisp_chunk_t*) * (super->value.expr.count - position - 1));

    super->value.expr.count--;

    super->value.expr.chunks = realloc(super->value.expr.chunks, sizeof(clisp_chunk_t*) * (super->value.expr.count));
    return item;
}

clisp_chunk_t*
clisp_expr_take(clisp_chunk_t* super, int position) {
    clisp_chunk_t* item = clisp_expr_pop(super, position);
    clisp_chunk_delete(super);
    return item;
}

clisp_chunk_t*
clisp_expr_join(clisp_chunk_t* first, clisp_chunk_t* second) {
    while (second->value.expr.count) {
        first = clisp_expr_append(first, clisp_expr_pop(second, 0));
    }

    clisp_chunk_delete(second);
    return first;
}