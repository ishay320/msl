#include "../arrays/dynamic_array.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "../ansi.h"

void print_success(const char* test_name) { printf(AN_GREEN "Test '%s' passed.\n" AN_RESET, test_name); }

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} da_i;
typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} da_p;

void test_da_i_append() {
    da_i arr   = {0};
    int vals[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) assert(da_append(arr, vals[i]));

    assert(arr.size == 5);
    assert(arr.capacity >= 5);
    for (int i = 0; i < 5; i++) assert(arr.data[i] == vals[i]);

    da_destroy(&arr);
    print_success("da_i_append");
}

void test_da_i_double_destroy() {
    da_i arr = {0};
    da_append(arr, 1);
    da_destroy(&arr);
    assert(arr.data == NULL);
    assert(arr.size == 0);
    assert(arr.capacity == 0);
    da_destroy(&arr);
    print_success("da_i_double_destroy");
}

void test_da_p_empty() {
    da_p empty = {0};
    assert(empty.size == 0);
    assert(empty.capacity == 0);
    da_destroy(&empty);
    print_success("da_p_empty");
}

void test_da_p_append() {
    da_p arr = {0};
    int a = 1, b = 2, c = 3;
    void* vals[] = {&a, &b, &c};
    for (int i = 0; i < 3; i++) assert(da_append(arr, vals[i]));

    assert(arr.size == 3);
    for (int i = 0; i < 3; i++) assert(arr.data[i] == vals[i]);

    da_destroy(&arr);
    assert(arr.data == NULL);
    print_success("da_p_append");
}

void test_da_i_single_element() {
    da_i arr = {0};
    assert(da_append(arr, 42));
    assert(arr.size == 1);
    assert(arr.capacity == DA_INITIAL_CAPACITY);
    assert(arr.data[0] == 42);
    da_destroy(&arr);
    print_success("da_i_single_element");
}

void test_da_i_reuse_after_destroy() {
    da_i arr = {0};
    for (int i = 0; i < 5; i++) da_append(arr, i * 10);
    da_destroy(&arr);

    for (int i = 0; i < 3; i++) da_append(arr, i + 100);
    assert(arr.size == 3);
    assert(arr.data[0] == 100);
    assert(arr.data[1] == 101);
    assert(arr.data[2] == 102);

    da_destroy(&arr);
    print_success("da_i_reuse_after_destroy");
}

void test_da_i_capacity_growth() {
    da_i arr = {0};
    for (int i = 0; i < 50; i++) da_append(arr, i);

    assert(arr.size == 50);
    assert(arr.capacity >= 50);
    /* capacity must be power-of-2 due to doubling strategy */
    assert((arr.capacity & (arr.capacity - 1)) == 0);
    assert(arr.data[0] == 0);
    assert(arr.data[49] == 49);

    da_destroy(&arr);
    print_success("da_i_capacity_growth");
}

void test_da_i_boundary_values() {
    da_i arr   = {0};
    int vals[] = {0, -1, -100, INT_MIN, INT_MAX};
    for (int i = 0; i < 5; i++) assert(da_append(arr, vals[i]));

    assert(arr.size == 5);
    for (int i = 0; i < 5; i++) assert(arr.data[i] == vals[i]);

    da_destroy(&arr);
    print_success("da_i_boundary_values");
}

void test_da_i_reserve() {
    da_i arr = {0};
    assert(da_reserve(arr, 100));
    assert(arr.capacity == 100);
    assert(arr.size == 0);

    /* reserve less than current capacity: no-op */
    assert(da_reserve(arr, 10));
    assert(arr.capacity == 100);

    da_append(arr, 42);
    assert(arr.size == 1);
    assert(arr.data[0] == 42);

    da_destroy(&arr);
    print_success("da_i_reserve");
}

int main(void) {
    printf(AN_BOLD AN_CYAN "Running dynamic_array tests..." AN_RESET "\n");
    test_da_i_append();
    test_da_i_double_destroy();
    test_da_p_empty();
    test_da_p_append();
    test_da_i_single_element();
    test_da_i_reuse_after_destroy();
    test_da_i_capacity_growth();
    test_da_i_boundary_values();
    test_da_i_reserve();
    printf(AN_GREEN "All dynamic_array tests passed!\n" AN_RESET);

    return 0;
}
