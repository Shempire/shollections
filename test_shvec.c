#include <stdio.h>

#include "shvec.h"

/**
 * An example of a typedef'd vector type.
 */
typedef SHVEC(long) long_vec_t;

void test_int_vec(void) {
    SHVEC(int) my_int_vec = SHVEC_EMPTY();

    printf("---\n");
    printf("APPEND(12): %zu\n", SHVEC_APPEND(my_int_vec, 12));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);

    printf("---\n");
    printf("APPEND(15): %zu\n", SHVEC_APPEND(my_int_vec, 15));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);

    printf("---\n");
    printf("APPEND(18): %zu\n", SHVEC_APPEND(my_int_vec, 18));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);

    printf("---\n");
    printf("APPEND(-1): %zu\n", SHVEC_APPEND(my_int_vec, -1));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);
    printf(" 3: %d\n", my_int_vec.values[3]);

    printf("---\n");
    printf("SET(0, 150): %d\n", SHVEC_SET(my_int_vec, 0, 150));
    printf("SET(1, 200): %d\n", SHVEC_SET(my_int_vec, 1, 200));
    printf("SET(8, 400): %d\n", SHVEC_SET(my_int_vec, 8, 400));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);
    printf(" 3: %d\n", my_int_vec.values[3]);

    printf("---\n");
    printf("INSERT(0, -3): %d\n", SHVEC_INSERT(my_int_vec, 0, -3));
    printf("INSERT(2, -4): %d\n", SHVEC_INSERT(my_int_vec, 2, -4));
    printf("INSERT(5, -5): %d\n", SHVEC_INSERT(my_int_vec, 5, -5));
    printf("INSERT(7, -7): %d\n", SHVEC_INSERT(my_int_vec, 7, -7));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);
    printf(" 3: %d\n", my_int_vec.values[3]);
    printf(" 4: %d\n", my_int_vec.values[4]);
    printf(" 5: %d\n", my_int_vec.values[5]);
    printf(" 6: %d\n", my_int_vec.values[6]);
    printf(" 7: %d\n", my_int_vec.values[7]);

    printf("---\n");
    SHVEC_EXTEND(my_int_vec, 12, 101);
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);
    printf(" 3: %d\n", my_int_vec.values[3]);
    printf(" 4: %d\n", my_int_vec.values[4]);
    printf(" 5: %d\n", my_int_vec.values[5]);
    printf(" 6: %d\n", my_int_vec.values[6]);
    printf(" 7: %d\n", my_int_vec.values[7]);
    printf(" 8: %d\n", my_int_vec.values[8]);
    printf(" 9: %d\n", my_int_vec.values[9]);
    printf("10: %d\n", my_int_vec.values[10]);
    printf("11: %d\n", my_int_vec.values[11]);

    printf("---\n");
    printf("REMOVE(11): %d\n", SHVEC_REMOVE(my_int_vec, 11));
    printf("REMOVE(10): %d\n", SHVEC_REMOVE(my_int_vec, 10));
    printf("REMOVE(3): %d\n", SHVEC_REMOVE(my_int_vec, 3));
    printf("REMOVE(0): %d\n", SHVEC_REMOVE(my_int_vec, 0));
    printf("cap: %zu sz: %zu\n", my_int_vec.cap, my_int_vec.sz);
    printf(" 0: %d\n", my_int_vec.values[0]);
    printf(" 1: %d\n", my_int_vec.values[1]);
    printf(" 2: %d\n", my_int_vec.values[2]);
    printf(" 3: %d\n", my_int_vec.values[3]);
    printf(" 4: %d\n", my_int_vec.values[4]);
    printf(" 5: %d\n", my_int_vec.values[5]);
    printf(" 6: %d\n", my_int_vec.values[6]);
    printf(" 7: %d\n", my_int_vec.values[7]);


    // Will cause warnings
    //SHVEC_SET(my_int_vec, 0, "abc");
    //SHVEC_APPEND(my_int_vec, "def");
    //SHVEC_INSERT(my_int_vec, 3, "ghi");
}

int main(void) {
    printf("------ test_int_vec\n");
    test_int_vec();

    //long_vec_t my_long_vec = SHVEC_EMPTY();
}
