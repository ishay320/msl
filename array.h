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
void array_free(void* array);

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

/**
 * Get the header from the array pointer
 *
 * @param a is the array.
 * @return header of the array
 */
#define array_get_header(a) (void*)(a) - ARRAY_HEADER_SIZE;

/**
 * Reserves space in the array, if the array is bigger then the reserve size, it
 * wont do nothing
 *
 * @param array is the array to reserve.
 * @param reserve is the size to reserve.
 * @return bool of if reserved successfully.
 */
#define array_reserve(array, reserve) f_array_reserve((void**)(&array), reserve)

/**
 * Resize space in the array, it can make the array smaller or bigger
 *
 * @param array is the array to reserve.
 * @param resize is the size to resize to.
 * @return bool of if resized successfully.
 */
#define array_resize(array, resize) f_array_resize((void**)(&array), resize)

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

void array_free(void* array)
{
    assert(array);
    struct array* header = array_get_header(array);
    free(header);
}

bool f_array_resize(void** array, size_t size)
{
    assert(*array);
    struct array* header = array_get_header(*array);
    void* new_ptr = realloc(header, size * header->stride + ARRAY_HEADER_SIZE);
    if (!new_ptr) {
        perror("could not resize array");
        return false;
    }

    header      = new_ptr;
    header->cap = size;
    if (header->cap < header->len) {
        header->len = header->cap;
    }

    // update the outside ptr to the new position
    *array = header->data;
    return true;
}

bool f_array_reserve(void** array, size_t size)
{
    assert(*array);
    struct array* header = array_get_header(*array);
    if (header->cap >= size) {
        return true;
    }

    return f_array_resize(array, size);
}

bool f_array_push(void** array, void* element)
{
    assert(*array);
    struct array* header = array_get_header(*array);
    if (header->len == header->cap) {
        size_t new_cap = header->cap * 2;
        if (!f_array_resize(array, new_cap)) {
            return false;
        }
        header = array_get_header(*array);
    }

    void* insert_pos = header->data + (header->stride * header->len);
    memcpy(insert_pos, element, header->stride);
    header->len++;

    return true;
}

/**
 * Remove from the array using index
 *
 * @param array pointer to the array.
 * @param index at the position to remove
 */
void array_remove_index(void* array, size_t index)
{
    assert(array);
    struct array* header = array_get_header(array);
    assert(header->len > index);

    memmove(header->data + index, header->data + ((index + 1) * header->stride),
            (header->len - 1 - index) * header->stride);
    header->len--;
}

/**
 * Get the capacity of the array.
 *
 * @param array pointer to the array.
 * @return The capacity of the array.
 */
size_t array_cap(void* array)
{
    assert(array);
    struct array* header = array_get_header(array);
    return header->cap;
}

/**
 * Get the length of the array.
 *
 * @param array pointer to the array.
 * @return The number of elements currently in the array.
 */
size_t array_len(void* array)
{
    assert(array);
    struct array* header = array_get_header(array);
    return header->len;
}

/**
 * Get the stride (size of each element) of the dynamic array.
 *
 * @param array pointer to the dynamic array.
 * @return The size in bytes of each element in the array.
 */
size_t array_stride(void* array)
{
    assert(array);
    struct array* header = array_get_header(array);
    return header->stride;
}

#endif  // ARRAY_H
