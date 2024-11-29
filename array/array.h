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
 * TODO: make it so:
 * 1. user creates pointer with the type of his choosing
 * 2. calls create_array(T)
 * 3. use push() and push_r_val()
 * 4. use the normal [] for getting element and get_size(array) for size
 * the create_array function creates memory with header of {len,cap,stride,data}
 * and gives the user pointer to data, and when the functions calls, it back
 * step to the header and do his stuff
 */

struct array {
    size_t len;
    size_t cap;
    size_t stride;

    uint8_t data;
};

#define ARRAY_HEADER_SIZE (sizeof(size_t) * 3)

void* f_array_init(size_t cap, size_t stride)
{
    struct array* header = malloc(ARRAY_HEADER_SIZE + (stride * cap));
    if (!header) {
        perror("could not create dynamic array");
        return NULL;
    }

    header->cap    = cap;
    header->len    = 0;
    header->stride = stride;

    return &header->data;
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
        *array = &header->data;
    }

    void* insert_pos = (&header->data) + (header->stride * header->len);
    memcpy(insert_pos, element, header->stride);
    header->len++;

    return true;
}

void f_array_free(void** array)
{
    struct array* header = (*array) - ARRAY_HEADER_SIZE;
    free(header);
    *array = NULL;
}

#define array_init(type) (type*)f_array_init(1, sizeof(type))
#define array_free(array) f_array_free((void**)&array)
#define array_push(array, element) f_array_push((void**)&array, &element)
#define array_push_rval(array, element)          \
    ({                                           \
        typeof(element) __tmp_value = (element); \
        array_push((array), __tmp_value);        \
    })

#endif  // ARRAY_H
