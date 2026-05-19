#include "../stack/dynamic_stack.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} ds_i;

void test_ds_push_and_top() {
    ds_i s = {0};
    assert(ds_push(s, 10));
    assert(ds_push(s, 20));
    assert(ds_push(s, 30));
    assert(ds_top(s) == 30);
    assert(ds_size(s) == 3);
    ds_destroy(&s);
    printf("ds push and top test passed.\n");
}

void test_ds_pop_order() {
    ds_i s     = {0};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) ds_push(s, vals[i]);

    for (int i = 4; i >= 0; i--) {
        assert(ds_top(s) == vals[i]);
        int v = ds_pop(s);
        assert(v == vals[i]);
    }
    assert(ds_is_empty(s));
    ds_destroy(&s);
    printf("ds pop order test passed.\n");
}

void test_ds_is_empty() {
    ds_i s = {0};
    assert(ds_is_empty(s));
    ds_push(s, 42);
    assert(!ds_is_empty(s));
    (void)ds_pop(s);
    assert(ds_is_empty(s));
    ds_destroy(&s);
    printf("ds is_empty test passed.\n");
}

void test_ds_single_element() {
    ds_i s = {0};
    assert(ds_push(s, 99));
    assert(ds_size(s) == 1);
    assert(ds_top(s) == 99);
    int v = ds_pop(s);
    assert(v == 99);
    assert(ds_is_empty(s));
    ds_destroy(&s);
    printf("ds single element test passed.\n");
}

void test_ds_boundary_values() {
    ds_i s     = {0};
    int vals[] = {0, -1, INT_MIN, INT_MAX};
    for (int i = 0; i < 4; i++) ds_push(s, vals[i]);

    for (int i = 3; i >= 0; i--) assert(ds_pop(s) == vals[i]);
    assert(ds_is_empty(s));
    ds_destroy(&s);
    printf("ds boundary values test passed.\n");
}

void test_ds_push_many() {
    ds_i s = {0};
    for (int i = 0; i < 100; i++) assert(ds_push(s, i));
    assert(ds_size(s) == 100);
    assert(ds_top(s) == 99);
    for (int i = 99; i >= 0; i--) assert(ds_pop(s) == i);
    assert(ds_is_empty(s));
    ds_destroy(&s);
    printf("ds push many test passed.\n");
}

void test_ds_size() {
    ds_i s = {0};
    assert(ds_size(s) == 0);
    ds_push(s, 1);
    assert(ds_size(s) == 1);
    ds_push(s, 2);
    ds_push(s, 3);
    assert(ds_size(s) == 3);
    (void)ds_pop(s);
    assert(ds_size(s) == 2);
    ds_destroy(&s);
    printf("ds size test passed.\n");
}

void test_ds_reuse_after_empty() {
    ds_i s = {0};
    ds_push(s, 1);
    ds_push(s, 2);
    (void)ds_pop(s);
    (void)ds_pop(s);

    ds_push(s, 10);
    ds_push(s, 20);
    assert(ds_size(s) == 2);
    assert(ds_top(s) == 20);
    ds_destroy(&s);
    printf("ds reuse after empty test passed.\n");
}

int main(void) {
    test_ds_push_and_top();
    test_ds_pop_order();
    test_ds_is_empty();
    test_ds_single_element();
    test_ds_boundary_values();
    test_ds_push_many();
    test_ds_size();
    test_ds_reuse_after_empty();
    printf("All dynamic_stack tests passed!\n");
    return 0;
}
