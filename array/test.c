#include <assert.h>

#include "array.h"

void test_array_initialization()
{
    int* arr = array_init(int);
    assert(arr != NULL);  // Verify array is initialized
    array_free(arr);
    printf("Initialization test passed.\n");
}

void test_array_push_rval()
{
    int* arr = array_init(int);
    array_push_rval(arr, 42);
    struct array* header = (struct array*)(((uint8_t*)arr) - ARRAY_HEADER_SIZE);
    assert(header->len == 1);
    assert(arr[0] == 42);
    array_free(arr);
    printf("Push r_val test passed.\n");
}

void test_array_push()
{
    int* arr = array_init(int);
    int item = 42;
    array_push(arr, item);
    struct array* header = (struct array*)(((uint8_t*)arr) - ARRAY_HEADER_SIZE);
    assert(header->len == 1);
    assert(arr[0] == 42);
    array_free(arr);
    printf("Push test passed.\n");
}

void test_array_resizing()
{
    int* arr = array_init(int);
    for (int i = 0; i < 100; i++) {
        array_push(arr, i);
    }
    struct array* header = (struct array*)(((uint8_t*)arr) - ARRAY_HEADER_SIZE);
    assert(header->cap >= 100);
    assert(header->len == 100);
    for (int i = 0; i < 100; i++) {
        assert(arr[i] == i);
    }
    array_free(arr);
    printf("Resizing test passed.\n");
}

void test_array_free()
{
    int* arr = array_init(int);
    array_push_rval(arr, 10);
    array_free(arr);
    assert(arr == NULL);  // Verify array pointer is null after free
    printf("Free test passed.\n");
}

int main()
{
    test_array_initialization();
    test_array_push_rval();
    test_array_push();
    test_array_resizing();
    test_array_free();
    printf("All tests passed!\n");
    return 0;
}
