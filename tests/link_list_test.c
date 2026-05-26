#include "link_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ansi.h"

typedef struct node_i_s {
    struct node_i_s* next;
    int data;
} node_i_s;

static int find_data_1(node_i_s* n) { return n->data == 1; }
static int find_data_2(node_i_s* n) { return n->data == 2; }
static int find_data_99(node_i_s* n) { return n->data == 99; }

void print_success(const char* test_name) { printf(AN_GREEN "Test '%s' passed.\n" AN_RESET, test_name); }

int main(void) {
    printf(AN_BOLD AN_CYAN "Running link list tests..." AN_RESET "\n");
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
        print_success("ll_insert_next");
    }

    // test ll_is_empty
    {
        node_i_s a = {.data = 1};
        assert(ll_is_empty(a));
        node_i_s b = {.data = 2};
        ll_insert_next(&a, &b);
        assert(!ll_is_empty(a));
        print_success("ll_is_empty");
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
        print_success("ll_remove_next");
    }

    // test ll_remove_next: a -> b, remove last => a -> NULL
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        ll_insert_next(&a, &b);
        ll_remove_next(&a);
        assert(a.next == NULL);
        print_success("ll_remove_next");
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
        print_success("ll_count");
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
        print_success("ll_find");
    }

    // test ll_insert_tail: a, insert &b => a -> b
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        ll_insert_tail(&a, &b);
        assert(a.next == &b);
        assert(b.next == NULL);
        print_success("ll_insert_tail");
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
        print_success("ll_insert_tail");
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
        print_success("ll_insert_tail");
    }

    // test ll_for_each_func: sum all node data
    {
        node_i_s a = {.data = 1};
        node_i_s b = {.data = 2};
        node_i_s c = {.data = 3};
        ll_insert_next(&a, &b);
        ll_insert_next(&b, &c);
        int sum = 0;
        ll_for_each(a, i) { sum += i->data; }
        assert(sum == 6);
        print_success("ll_for_each_func");
    }

    {
        node_i_s* base = calloc(1, sizeof(node_i_s));
        base->data     = 1;
        for (int i = 0; i < 10; i++) {
            node_i_s* n = calloc(1, sizeof(node_i_s));
            n->data     = i;
            ll_insert_tail(base, n);
        }
        assert(ll_count(*base) == 11);

        for (typeof(base) cur = base, next; cur != NULL; cur = next) {
            next = cur->next;
            free(cur);
        }

        print_success("ll_free");
    }

    printf(AN_GREEN "All tests passed!\n" AN_RESET);
    return 0;
}
