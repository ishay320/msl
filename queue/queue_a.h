#ifndef QUEUE_A_H
#define QUEUE_A_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Initialize a queue with a given capacity
 *
 * @param qtype The type of the queue struct to initialize
 * @param capacity The maximum number of elements the queue can hold
 * @return The initialized queue struct
 */
#define qa_init(qtype, capacity)                      \
    ({                                                \
        qtype q = {0};                                \
        q.data  = malloc(sizeof(*q.data) * capacity); \
        if (q.data) {                                 \
            q.cap = capacity;                         \
        }                                             \
        q;                                            \
    })

/**
 * @brief Push an element to the back of the queue
 *
 * @param q The queue struct
 * @param d The data element to push
 * @return true if the element was pushed successfully, false if the queue is full
 */
#define qa_push(q, d)            \
    ({                           \
        bool __ret = false;      \
        if (!qa_is_full(q)) {    \
            q.data[q.end++] = d; \
            q.size++;            \
            q.end %= q.cap;      \
            __ret = true;        \
        }                        \
        __ret;                   \
    })

/**
 * @brief Pop an element from the front of the queue
 *
 * @param q The queue struct
 * @param out The variable to store the popped element
 * @return true if the element was popped successfully, false if the queue is empty
 */
#define qa_pop(q, out)               \
    ({                               \
        bool __ret = false;          \
        if (!qa_is_empty(q)) {       \
            out = q.data[q.start++]; \
            q.size--;                \
            q.start %= q.cap;        \
            __ret = true;            \
        }                            \
        __ret;                       \
    })

/**
 * @brief Get the front element of the queue without popping it (the next to be popped)
 *
 * @param q The queue struct
 * @param out The variable to store the front element
 * @return true if the front element was retrieved successfully, false if the queue is empty
 */
#define qa_front(q, out)             \
    ({                               \
        bool __ret = false;          \
        if (!qa_is_empty(q)) {       \
            out   = q.data[q.start]; \
            __ret = true;            \
        }                            \
        __ret;                       \
    })

/**
 * @brief Get the back element of the queue without popping it (the most recently pushed)
 *
 * @param q The queue struct
 * @param out The variable to store the back element
 * @return true if the back element was retrieved successfully, false if the queue is empty
 */
#define qa_back(q, out)                                  \
    ({                                                   \
        bool __ret = false;                              \
        if (!qa_is_empty(q)) {                           \
            out   = q.data[(q.end + q.cap - 1) % q.cap]; \
            __ret = true;                                \
        }                                                \
        __ret;                                           \
    })

/**
 * @brief Check if the queue is empty
 *
 * @param q The queue struct
 * @return true if the queue contains no elements, false otherwise
 */
#define qa_is_empty(q) ({ q.size == 0; })

/**
 * @brief Check if the queue is full
 *
 * @param q The queue struct
 * @return true if the queue is at capacity, false otherwise
 */
#define qa_is_full(q) ({ q.size == q.cap; })

/**
 * @brief Get the number of elements in the queue
 *
 * @param q The queue struct
 * @return The current number of elements
 */
#define qa_size(q) ({ q.size; })

/**
 * @brief Reset the queue to empty without freeing memory
 *
 * @param q The queue struct
 */
#define qa_clear(q)  \
    ({               \
        q.size  = 0; \
        q.start = 0; \
        q.end   = 0; \
    })

/**
 * @brief Free the queue's data pointer and set it to NULL
 *
 * @param q Pointer to the queue's data array
 */
#define qa_destroy(q)       \
    ({                      \
        if (q.data) {       \
            free(q.data);   \
            q.data  = NULL; \
            q.size  = 0;    \
            q.cap   = 0;    \
            q.start = 0;    \
            q.end   = 0;    \
        }                   \
    })

#endif  // QUEUE_A_H