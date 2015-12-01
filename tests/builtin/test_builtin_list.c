
#include "ptest.h"

#include "../../src/builtin.h"


clisp_chunk_expr_t*
create_list(char *argv[], int argc) {
    clisp_chunk_t* chunk = clisp_chunk_list();

    for (int i = 0; i < argc; i++) {
        clisp_expr_append(chunk->value.list, clisp_chunk_str(argv[i]));
    }

    clisp_chunk_expr_t* expr = clisp_expr_new();
    clisp_expr_append(expr, chunk);

    return expr;
}


PT_SUITE(suite_builtin_list) {

    PT_TEST(test_get_head_element_from_list) {
        char *argv[] = {"item1", "item2"};
        clisp_chunk_expr_t* chunk = create_list(argv, 2);

        clisp_chunk_t* head = clisp_builtin_list_head(chunk);

        PT_ASSERT(head->type == CLISP_STRING);
        PT_ASSERT_STR_EQ(head->value.string, "item1");

        clisp_chunk_delete(head);
    }

    PT_TEST(test_get_head_throws_empty_list) {
        char *argv[] = {};
        clisp_chunk_expr_t* chunk = create_list(argv, 0);
        clisp_chunk_t* head = clisp_builtin_list_head(chunk);

        PT_ASSERT(head->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(head->value.string, "List is empty");

        clisp_chunk_delete(head);
    }

    PT_TEST(test_get_tail_element_from_list) {
        char *argv[] = {"item1", "item2", "item3"};
        clisp_chunk_expr_t* chunk = create_list(argv, 3);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk);

        PT_ASSERT(tail->type == CLISP_LIST);
        PT_ASSERT(tail->value.list->count == 2);

        clisp_chunk_delete(tail);
    }

    PT_TEST(test_get_tail_throws_empty_list) {
        char *argv[] = {};
        clisp_chunk_expr_t* chunk = create_list(argv, 0);

        clisp_chunk_t* tail = clisp_builtin_list_tail(chunk);

        PT_ASSERT(tail->type == CLISP_ERROR);
        PT_ASSERT_STR_EQ(tail->value.string, "List is empty");

        clisp_chunk_delete(tail);
    }
}