#ifndef ARRAY_H
#define ARRAY_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Simple dynamic array implementation in C.
 *
 * Usage:
 * 1. Initialize with `array_init(type)` or `array_init_sized(type, size)`.
 * 2. Add elements using `array_push()` or `array_push_rval()`.
 * 3. Access elements with `array[x]` and get the size using
 * `array_size(array)`.
 * 4. Free memory with `array_free(array)`.
 *
 * Example:
 *
 * int* arr = array_init(int);
 * array_push_rval(arr, 42);
 * printf("%d\n", arr[0]);
 * array_free(arr);
 */

struct array {
    size_t len;
    size_t cap;
    size_t stride;

    uint8_t data[];
};

#define ARRAY_HEADER_SIZE (sizeof(size_t) * 3)

void* f_array_init(size_t stride, size_t cap)
{
    struct array* header = malloc(ARRAY_HEADER_SIZE + (stride * cap));
    if (!header) {
        perror("could not create dynamic array");
        return NULL;
    }

    header->cap    = cap;
    header->len    = 0;
    header->stride = stride;

    return header->data;
}

bool f_array_push(void** array, void* element)
{
    assert(*array);
    struct array* header = (*array) - ARRAY_HEADER_SIZE;
    if (header->len == header->cap) {
        size_t new_cap = header->cap * 2;
        void* new_ptr =
            realloc(header, new_cap * header->stride + ARRAY_HEADER_SIZE);
        if (!new_ptr) {
            perror("could not create dynamic array");
            return false;
        }
        header      = new_ptr;
        header->cap = new_cap;

        // update the outside ptr to the new position
        *array = header->data;
    }

    void* insert_pos = header->data + (header->stride * header->len);
    memcpy(insert_pos, element, header->stride);
    header->len++;

    return true;
}

void f_array_free(void** array)
{
    assert(*array);
    struct array* header = (*array) - ARRAY_HEADER_SIZE;
    free(header);
    *array = NULL;
}

/**
 * Initialisation of the dynamic array
 *
 * @param type is the array to init.
 * @return type* of the new array.
 */
#define array_init(type) (type*)f_array_init(sizeof(type), 1)

/**
 * Initialisation of the dynamic array with an starting size
 *
 * @param type is the array to init.
 * @param size is the number of elements that the array will start with.
 * @return type* of the new array.
 */
#define array_init_sized(type, size) (type*)f_array_init(sizeof(type), size)

/**
 * Free the dynamic array
 *
 * @param array is the array to free.
 */
#define array_free(array) f_array_free((void**)&array)

/**
 * Push an element to the array
 *
 * @param array is the array to push to.
 * @param element is the element to push into the array.
 * @return bool of if pushed successfully.
 */
#define array_push(array, element) f_array_push((void**)&array, &element)

/**
 * Push an r value element to the array
 * - r value is element without memory example: 1 + 3
 *
 * @param array is the array to push to.
 * @param element is the element to push into the array.
 * @return bool of if pushed successfully.
 */
#define array_push_rval(array, element)          \
    ({                                           \
        typeof(element) __tmp_value = (element); \
        array_push((array), __tmp_value);        \
    })

#endif  // ARRAY_H
