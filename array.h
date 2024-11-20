#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

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

    void* data;
};

#endif  // ARRAY_H
