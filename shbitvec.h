/*
 * shbitvec -- an auto-expanding, bounds-checking bit-vector implementation
 */

#ifndef _SHBITVEC_H_
#define _SHBITVEC_H_

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shutil.h"
#include "shvec.h"

typedef struct {
    size_t sz;
    SHVEC(unsigned long) vecs;
} shbitvec;

/**
 * An empty shbitvec, useful for initialization. shbitvec structs can also be
 * initialized by just zeroing them out.
 */
#define SHBITVEC_EMPTY() { 0, SHVEC_EMPTY() }

#define _SHBITVEC_BITS (sizeof(unsigned long) * CHAR_BIT)

/**
 * Clear a shbitvec, freeing any memory used by it.
 */
inline static void shbitvec_clear(shbitvec *bitvec) {
    (void) SHVEC_CLEAR(bitvec->vecs);
    bitvec->sz = 0;
}

/**
 * Get a bit from the bit-vector, without doing a bounds-check first.
 */
inline static _Bool shbitvec_get_unsafe(shbitvec *bitvec, size_t index) {
    return bitvec->vecs.values[index / _SHBITVEC_BITS]
        & (1UL << (index % _SHBITVEC_BITS));
}

/**
 * Get a bit from the vector. Returns 1 if the bit is set, 0 if it is not set,
 * or -1 if the index is out-of-bounds.
 */
inline static int shbitvec_get(shbitvec *bitvec, size_t index) {
    if (index >= bitvec->sz) return -1;
    return shbitvec_get_unsafe(bitvec, index);
}

/**
 * Set a bit in the bit-vector, without doing a bounds-check first.
 */
inline static void shbitvec_set_unsafe(shbitvec *bitvec, size_t index, _Bool value) {
    if (value) {
        bitvec->vecs.values[index / _SHBITVEC_BITS] |=
            (1UL << (index % _SHBITVEC_BITS));
    } else {
        bitvec->vecs.values[index / _SHBITVEC_BITS] &=
            ~(1UL << (index % _SHBITVEC_BITS));
    }
}

/**
 * Set a bit in the bit-vector. Returns 1 if the bit was set successfully, or
 * 0 if the index is out-of-bounds.
 */
inline static _Bool shbitvec_set(shbitvec *bitvec, size_t index, _Bool value) {
    if (index >= bitvec->sz) return 0;
    shbitvec_set_unsafe(bitvec, index, value);
    return 1;
}

/**
 * Append a bit to the end of the bit-vector. Returns the index that the bit
 * was inserted at, or -1 if there was an error allocating memory (in which
 * case "errno" should be set apprioriately).
 */
inline static ssize_t shbitvec_append(shbitvec *bitvec, _Bool value) {
    size_t required_vecs = bitvec->sz / _SHBITVEC_BITS + 1;
    if (SHVEC_EXTEND(bitvec->vecs, required_vecs) == -1) {
        return -1;
    }
    ssize_t new_index = bitvec->sz++;
    shbitvec_set_unsafe(bitvec, new_index, value);
    return new_index;
}

/**
 * Ensure the bit-vector is at least a certain size. If the new size is larger
 * than the current size, new bits will be added to the end with the value 0.
 * Returns 1 if bits were added, 0 if no bits were added, or -1 if there was
 * an error allocating memory (in which case "errno" should be set
 * apprioriately).
 */
inline static int shbitvec_extend(shbitvec *bitvec, size_t size) {
    if (size == 0 || bitvec->sz >= size) {
        return 0;
    }
    size_t required_vecs = (size - 1) / _SHBITVEC_BITS + 1;
    if (SHVEC_EXTEND(bitvec->vecs, required_vecs) == -1) {
        return -1;
    }
    bitvec->sz = size;
    return 1;
}

#endif /* _SHBITVEC_H_ */
