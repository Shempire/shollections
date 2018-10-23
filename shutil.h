#ifndef _SHUTIL_H_
#define _SHUTIL_H_

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __has_builtin
#define __has_builtin(x) 0
#define _SHUTIL_H_DEFINED_HAS_BUILTIN_
#endif

// __builtin_clz supported by clang (checked with __has_builtin) and GCC >= 3.4
#if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))                \
    || (__has_builtin(__builtin_clz))
/**
 * Round x up to the nearest power of 2.
 */
inline static size_t shutil_pow2_ceil(size_t x) {
    if (x <= 1) return 1;
    return 1 << ((sizeof(x) * CHAR_BIT) - __builtin_clz(x - 1));
}
#else
/**
 * Round x up to the nearest power of 2.
 */
inline static size_t shutil_pow2_ceil(size_t x) {
    if (x <= 1) return 1;
    x--;
    for (size_t i = 1; i < sizeof(x) * CHAR_BIT; i *= 2) {
        x |= x >> i;
    }
    x++;
    return x;
}
#endif

#ifdef _SHUTIL_H_DEFINED_HAS_BUILTIN_
#undef _SHUTIL_H_DEFINED_HAS_BUILTIN_
#endif

#endif /* _SHUTIL_H_ */
