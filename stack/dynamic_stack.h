#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include "dynamic_array.h"

/*
 * Generic dynamic stack via macros, built on top of dynamic_array.
 * Define an empty struct with size, capacity, data and use:
 *   ds_push(stack, item)  -- push item onto stack, returns bool (false on alloc fail)
 *   ds_pop(stack)         -- remove and return top item (undefined if empty)
 *   ds_top(stack)         -- peek at top item without removing (undefined if empty)
 *   ds_is_empty(stack)    -- returns true if stack has no elements
 *
 * Example:
 *   typedef struct { size_t size; size_t capacity; int* data; } ds_i;
 *   ds_i s = {0};
 *   ds_push(s, 42);
 *   int v = ds_pop(s);
 *   da_destroy(&s);
 */

/**
 * @brief Push an item onto the stack
 *
 * @param stack The stack struct (size, capacity, data)
 * @param item  The item to push
 * @return true if the item was pushed successfully, false on allocation failure
 */
#define ds_push(stack, item) da_append(stack, item)

/**
 * @brief Remove and return the top item from the stack
 *
 * @param stack The stack struct (size, capacity, data)
 * @return The top item; behavior is undefined if stack is empty
 */
#define ds_pop(stack) ((stack).data[--(stack).size])

/**
 * @brief Peek at the top item without removing it
 *
 * @param stack The stack struct (size, capacity, data)
 * @return The top item; behavior is undefined if stack is empty
 */
#define ds_top(stack) ((stack).data[(stack).size - 1])

/**
 * @brief Get the number of elements in the stack
 *
 * @param stack The stack struct (size, capacity, data)
 * @return The number of elements in the stack
 */
#define ds_size(stack) ((stack).size)

/**
 * @brief Check whether the stack is empty
 *
 * @param stack The stack struct (size, capacity, data)
 * @return true if the stack contains no elements, false otherwise
 */
#define ds_is_empty(stack) ((stack).size == 0)

/**
 * @brief Destroy the stack and free its resources
 *
 * @param stack The stack struct (size, capacity, data)
 */
#define ds_destroy(stack) da_destroy(stack)

#endif  // DYNAMIC_STACK_H
