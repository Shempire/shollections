/*
 * shvec -- an auto-expanding, type-safe, bounds-checking vector implementation
 */

#ifndef _SHVEC_H_
#define _SHVEC_H_

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shutil.h"

/**
 * Define a SHVEC struct. This is an anonymous struct that can be used as the
 * type of a variable, type of a member in another struct, or type in a
 * typedef.
 */
#define SHVEC(_type) struct { size_t sz; size_t cap; _type *values; }

/**
 * An empty SHVEC struct, useful for initialization. SHVEC structs can also
 * be initialized by just zeroing them out.
 */
#define SHVEC_EMPTY() { 0, 0, NULL }

/**
 * Ensure the SHVEC capacity is at least a certain capacity. The actual
 * implementation will round the capacity up to the next power of 2, but this
 * is subject to change in the future.
 *
 * Returns 1 if successful, or 0 if there was an error allocating memory (in
 * which case "errno" should be set appropriately).
 */
inline static _Bool _shvec_ensure_cap(
        size_t *sz,
        size_t *cap,
        void **values,
        size_t new_cap,
        size_t value_size) {
    new_cap = shutil_pow2_ceil(new_cap);
    if (*values == NULL) {
        *values = malloc(value_size * new_cap);
        if (*values == NULL) return 0;
        *sz = 0;
        *cap = new_cap;
    } else if (*cap < new_cap) {
        *values = realloc(*values, value_size * new_cap);
        if (*values == NULL) return 0;
        *cap = new_cap;
    }
    return 1;
}

/**
 * Convenience macro wrapping _shvec_ensure_cap.
 */
#define _SHVEC_ENSURE_CAP(_struct, _cap)                                    \
    _shvec_ensure_cap(                                                      \
            &(_struct).sz,                                                  \
            &(_struct).cap,                                                 \
            (void **) &(_struct).values,                                    \
            (_cap),                                                         \
            sizeof(*(_struct).values))

/**
 * Clear a SHVEC struct, freeing any memory used by it.
 */
#define SHVEC_CLEAR(_struct)                                                \
    (                                                                       \
        (                                                                   \
            ((_struct).values != NULL)                                      \
                ? (free((_struct).values), ((_struct).values = NULL))       \
                : NULL                                                      \
        ),                                                                  \
        ((_struct).sz = (_struct).cap = 0),                                 \
        1                                                                   \
    )

/**
 * Get an item by index. If the index is out-of-bounds, return the default
 * specified.
 */
#define SHVEC_GET(_struct, _index, _default)                                \
    (                                                                       \
        ((_index) >= (_struct).sz)                                          \
            ? (_default)                                                    \
            : (_struct).values[(_index)]                                    \
    )

/**
 * Get an item by index, without doing a bounds check first.
 */
#define SHVEC_GET_UNSAFE(_struct, _index) ((_struct).values[(_index)])

/**
 * Set an item by index. Returns 1 if successful, or 0 if the index is out-of-
 * bounds.
 */
#define SHVEC_SET(_struct, _index, _value)                                  \
    (                                                                       \
        ((_index) >= (_struct).sz)                                          \
            ? 0                                                             \
            : ((_struct).values[(_index)] = (_value), 1)                    \
    )

/**
 * Set an item by index, without doing a bounds check first.
 */
#define SHVEC_SET_UNSAFE(_struct, _index, _value)                           \
    ((_struct).values[(_index)] = (_value_))

/**
 * Append an item to the end of the vector. Returns the index that the item was
 * inserted at, or -1 if there was an error allocating memory (in which case
 * "errno" should be set apprioriately).
 */
#define SHVEC_APPEND(_struct, _value)                                       \
    (                                                                       \
        _SHVEC_ENSURE_CAP((_struct), (_struct).sz + 1)                      \
            ? (                                                             \
                ((_struct).values[(_struct).sz] = (_value)),                \
                ((ssize_t) ((_struct).sz++))                                \
              )                                                             \
            : -1                                                            \
    )

/**
 * Insert an item at a specific index in the vector. Returns 1 if successful,
 * 0 if the index is out-of-bounds, or -1 if there was an error allocating
 * memory (in which case "errno" should be set apprioriately).
 *
 * Valid indices are between 0 and the size of the vector, inclusive.
 */
#define SHVEC_INSERT(_struct, _index, _value)                               \
    (                                                                       \
        ((_index) > (_struct).sz)                                           \
            ? 0                                                             \
            : (                                                             \
                _SHVEC_ENSURE_CAP((_struct), (_struct).sz + 1)              \
                    ? (                                                     \
                        memmove(                                            \
                            (_struct).values + ((_index) + 1),              \
                            (_struct).values + (_index),                    \
                            ((_struct).sz - (_index))                       \
                                * sizeof(*(_struct).values)),               \
                        ((_struct).values[(_index)] = (_value)),            \
                        ((_struct).sz += 1),                                \
                        1                                                   \
                      )                                                     \
                    : -1                                                    \
              )                                                             \
    )

/**
 * Remove an item at a specific index in the vector. Returns 1 if successful,
 * or 0 if the index is out-of-bounds.
 */
#define SHVEC_REMOVE(_struct, _index)                                       \
    (                                                                       \
        ((_index) >= (_struct).sz)                                          \
            ? 0                                                             \
            : (                                                             \
                memmove(                                                    \
                    (_struct).values + (_index),                            \
                    (_struct).values + ((_index) + 1),                      \
                    ((_struct).sz - (_index) - 1)                           \
                        * sizeof(*(_struct).values)),                       \
                ((_struct).sz -= 1),                                        \
                1                                                           \
              )                                                             \
    )

/**
 * Ensure the vector is at least a certain size. If the new size is larger than
 * the current size, new elements will be added to the end with the value 0.
 * Returns 1 if elements were added, 0 if no elements were added, or -1 if
 * there was an error allocating memory (in which case "errno" should be set
 * apprioriately).
 */
#define SHVEC_EXTEND(_struct, _size)                                        \
    (                                                                       \
        _SHVEC_ENSURE_CAP((_struct), (_size))                               \
            ? (                                                             \
                ((_size) > (_struct).sz)                                    \
                    ? (                                                     \
                        memset(                                             \
                            (_struct).values + (_struct).sz,                \
                            0,                                              \
                            ((_size) - (_struct).sz)                        \
                                * sizeof(*(_struct).values)),               \
                        (_struct).sz = (_size),                             \
                        1                                                   \
                      )                                                     \
                    : 0                                                     \
              )                                                             \
            : -1                                                            \
    )

#endif /* _SHVEC_H_ */
