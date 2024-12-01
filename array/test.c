#include <assert.h>
#include <stdio.h>

#include "array.h"

void test_array_initialization()
{
    int* arr = array_init(int);
    assert(arr != NULL);  // Verify array is initialized
    array_free(arr);
    printf("Initialization test passed.\n");
}

void test_array_init_sized()
{
    int* arr = array_init_sized(int, 10);
    assert(arr != NULL);  // Verify array is initialized
    struct array* header = (struct array*)(((uint8_t*)arr) - ARRAY_HEADER_SIZE);
    assert(header->cap == 10);
    array_free(arr);
    printf("Initialization with size test passed.\n");
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

void test_array_resizing_dynamicly()
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
    printf("Resizing dynamicly test passed.\n");
}

void test_array_free()
{
    int* arr = array_init(int);
    array_push_rval(arr, 10);
    array_free(arr);
    assert(arr == NULL);  // Verify array pointer is null after free
    printf("Free test passed.\n");
}

void test_array_cap()
{
    int* arr             = array_init_sized(int, 50);
    struct array* header = (struct array*)(((uint8_t*)arr) - ARRAY_HEADER_SIZE);
    assert(array_cap(arr) == header->cap);
    assert(header->cap == 50);
    array_free(arr);
    printf("Capacity test passed.\n");
}

void test_array_len()
{
    int* arr = array_init(int);
    assert(array_len(arr) == 0);  // Initially, the length should be 0.

    array_push_rval(arr, 42);
    assert(array_len(arr) == 1);  // After one push, the length should be 1.

    array_push_rval(arr, 100);
    assert(array_len(arr) == 2);  // After two pushes, the length should be 2.

    array_free(arr);
    printf("Length test passed.\n");
}

void test_array_stride()
{
    int* int_arr = array_init(int);
    assert(array_stride(int_arr) ==
           sizeof(int));  // Stride for int array should match sizeof(int).

    double* double_arr = array_init(double);
    assert(
        array_stride(double_arr) ==
        sizeof(
            double));  // Stride for double array should match sizeof(double).

    array_free(int_arr);
    array_free(double_arr);
    printf("Stride test passed.\n");
}

int main(void)
{
    test_array_initialization();
    test_array_init_sized();
    test_array_push_rval();
    test_array_push();
    test_array_resizing_dynamicly();
    test_array_free();
    test_array_cap();
    test_array_len();
    test_array_stride();
    printf("All tests passed!\n");
    return 0;
}
