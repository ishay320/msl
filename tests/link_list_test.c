#include "link_list.h"

#include <assert.h>
#include <stdio.h>

typedef struct node_i_s {
    struct node_i_s* next;
    int data;
} node_i_s;

static int find_data_1(node_i_s* n) { return n->data == 1; }
static int find_data_2(node_i_s* n) { return n->data == 2; }
static int find_data_99(node_i_s* n) { return n->data == 99; }

static int g_sum = 0;
static void sum_node(node_i_s* n) { g_sum += n->data; }

int main(void) {
    // test ll_insert_next: a -> b -> c
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        assert(a.next == &b);
        assert(b.next == &c);
        assert(a.next->next->data == 3);
        printf("ll_insert_next passed.\n");
    }

    // test ll_is_empty
    {
        node_i_s a = {.data = 1};
        assert(ll_is_empty(a));
        node_i_s b = {.data = 2};
        ll_insert_next(&a, &b);
        assert(!ll_is_empty(a));
        printf("ll_is_empty passed.\n");
    }

    // test ll_remove_next: a -> b -> c, remove b => a -> c
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        ll_remove_next(&a);
        assert(a.next == &c);
        assert(a.next->data == 3);
        printf("ll_remove_next middle passed.\n");
    }

    // test ll_remove_next: a -> b, remove last => a -> NULL
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        ll_insert_next(&a, &b);
        ll_remove_next(&a);
        assert(a.next == NULL);
        printf("ll_remove_next last passed.\n");
    }

    // test ll_count
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        assert(ll_count(a) == 1);
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        assert(ll_count(a) == 3);
        printf("ll_count passed.\n");
    }

    // test ll_find
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        node_i_s* head_found = ll_find(a, find_data_1);
        assert(head_found == &a);
        node_i_s* found = ll_find(a, find_data_2);
        assert(found == &b);
        node_i_s* not_found = ll_find(a, find_data_99);
        assert(not_found == NULL);
        printf("ll_find passed.\n");
    }

    // test ll_insert_tail: a, insert &b => a -> b
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        ll_insert_tail(&a, &b);
        assert(a.next == &b);
        assert(b.next == NULL);
        printf("ll_insert_tail single passed.\n");
    }

    // test ll_insert_tail chain: a -> b, insert &c => a -> b -> c
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_tail(&a, &c);
        assert(a.next == &b);
        assert(b.next == &c);
        assert(c.next == NULL);
        printf("ll_insert_tail chain passed.\n");
    }

    // test ll_insert_tail deep: a -> b -> c, insert &d => reaches actual tail
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        node_i_s d = {.data = 4};
        ll_insert_next(&a, &b);
        ll_insert_tail(&b, &c);
        ll_insert_tail(&a, &d);
        assert(c.next == &d);
        assert(d.next == NULL);
        printf("ll_insert_tail deep passed.\n");
    }

    // test ll_for_each_func: sum all node data
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        g_sum = 0;
        ll_for_each_func(a, sum_node);
        assert(g_sum == 6);
        printf("ll_for_each_func passed.\n");
    }

    printf("All tests passed!\n");
    return 0;
}
