#include "../array.h"

#include <assert.h>
#include <stdio.h>

void test_array_initialization()
{
    int* arr = array_init(int);
    assert(arr != NULL);  // verify array is initialized
    array_free(arr);
    printf("Initialization test passed.\n");
}

void test_array_init_sized()
{
    int* arr = array_init_sized(int, 10);
    assert(arr != NULL);  // verify array is initialized
    struct array* header = array_get_header(arr);
    assert(header->cap == 10);
    array_free(arr);
    printf("Initialization with size test passed.\n");
}

void test_array_push_rval()
{
    int* arr = array_init(int);
    array_push_rval(arr, 42);
    struct array* header = array_get_header(arr);
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
    struct array* header = array_get_header(arr);
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
    struct array* header = array_get_header(arr);
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
    printf("Free test passed.\n");
}

void test_array_cap()
{
    int* arr             = array_init_sized(int, 50);
    struct array* header = array_get_header(arr);
    assert(array_cap(arr) == header->cap);
    assert(header->cap == 50);
    array_free(arr);
    printf("Capacity test passed.\n");
}

void test_array_len()
{
    int* arr = array_init(int);
    assert(array_len(arr) == 0);  // initially, the length should be 0

    array_push_rval(arr, 42);
    assert(array_len(arr) == 1);  // after one push, the length should be 1

    array_push_rval(arr, 100);
    assert(array_len(arr) == 2);  // after two pushes, the length should be 2

    array_free(arr);
    printf("Length test passed.\n");
}

void test_array_stride()
{
    int* int_arr = array_init(int);
    assert(array_stride(int_arr) ==
           sizeof(int));  // stride for int array should match sizeof(int)

    double* double_arr = array_init(double);
    assert(
        array_stride(double_arr) ==
        sizeof(double));  // stride for double array should match sizeof(double)

    array_free(int_arr);
    array_free(double_arr);
    printf("Stride test passed.\n");
}

void test_array_reserve()
{
    int* array = array_init(int);
    assert(array_reserve(array, 10));
    assert(array_cap(array) == 10);
    assert(array_reserve(array, 5));
    assert(array_cap(array) == 10);
    assert(array_reserve(array, 30));
    assert(array_cap(array) == 30);

    array_free(array);
    printf("Reserve test passed.\n");
}

void test_array_resize()
{
    int* array = array_init(int);
    assert(array_resize(array, 10));
    assert(array_cap(array) == 10);
    assert(array_resize(array, 7));
    assert(array_cap(array) == 7);
    assert(array_resize(array, 30));
    assert(array_cap(array) == 30);

    array_free(array);
    printf("Resize test passed.\n");
}

void test_array_remove_index()
{
    int* array = array_init(int);

    array_push_rval(array, 12);
    assert(array_len(array) == 1);
    array_remove_index(array, 0);
    assert(array_len(array) == 0);

    array_push_rval(array, 42);
    array_push_rval(array, 52);
    array_push_rval(array, 22);
    assert(array[0] == 42);
    assert(array_len(array) == 3);

    array_remove_index(array, 0);
    assert(array_len(array) == 2);
    assert(array[0] == 52);

    array_push_rval(array, 25);
    assert(array_len(array) == 3);
    assert(array[2] == 25);
    array_remove_index(array, 0);
    assert(array[1] == 25);
    assert(array_len(array) == 2);

    array_free(array);
    printf("Remove index test passed.\n");
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
    test_array_resize();
    test_array_reserve();
    test_array_remove_index();
    printf("All array tests passed!\n");

    return 0;
}
