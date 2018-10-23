#include <stdio.h>

#include "shunit/shunit.h"

#include "shvec.h"

/**
 * An example of a typedef'd vector type.
 */
typedef SHVEC(long) long_vec_t;

void test_int_vec(void) {
    SHVEC(int) my_int_vec = SHVEC_EMPTY();

    TEST("SHVEC_APPEND") {
        int expected[] = {12, 15, 18, -1};

        ASSERT(SHVEC_APPEND(my_int_vec, 12) == 0);
        ASSERT(my_int_vec.cap == 1);
        ASSERT(my_int_vec.sz == 1);
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 1);

        ASSERT(SHVEC_APPEND(my_int_vec, 15) == 1);
        ASSERT(my_int_vec.cap == 2);
        ASSERT(my_int_vec.sz == 2);
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 2);

        ASSERT(SHVEC_APPEND(my_int_vec, 18) == 2);
        ASSERT(my_int_vec.cap == 4);
        ASSERT(my_int_vec.sz == 3);
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 3);

        ASSERT(SHVEC_APPEND(my_int_vec, -1) == 3);
        ASSERT(my_int_vec.cap == 4);
        ASSERT(my_int_vec.sz == 4);
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 4);
    }

    TEST("SHVEC_SET") {
        ASSERT(SHVEC_SET(my_int_vec, 0, 150) == 1);
        ASSERT(SHVEC_SET(my_int_vec, 1, 200) == 1);
        ASSERT(SHVEC_SET(my_int_vec, 8, 400) == 0);

        ASSERT(my_int_vec.cap == 4);
        ASSERT(my_int_vec.sz == 4);

        int expected[] = {150, 200, 18, -1};
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 4);
    }

    TEST("SHVEC_INSERT") {
        ASSERT(SHVEC_INSERT(my_int_vec, 0, -3) == 1);
        ASSERT(SHVEC_INSERT(my_int_vec, 2, -4) == 1);
        ASSERT(SHVEC_INSERT(my_int_vec, 5, -5) == 1);
        ASSERT(SHVEC_INSERT(my_int_vec, 7, -7) == 1);

        ASSERT(my_int_vec.cap == 8);
        ASSERT(my_int_vec.sz == 8);

        int expected[] = {-3, 150, -4, 200, 18, -5, -1, -7};
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 8);
    }

    TEST("SHVEC_EXTEND") {
        ASSERT(SHVEC_EXTEND(my_int_vec, 5) == 0);
        ASSERT(SHVEC_EXTEND(my_int_vec, 12) == 1);
        ASSERT(SHVEC_EXTEND(my_int_vec, 12) == 0);

        ASSERT(my_int_vec.cap == 16);
        ASSERT(my_int_vec.sz == 12);

        int expected[] = {-3, 150, -4, 200, 18, -5, -1, -7, 0, 0, 0, 0};
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 12);
    }

    TEST("SHVEC_REMOVE") {
        ASSERT(SHVEC_REMOVE(my_int_vec, 11) == 1);
        ASSERT(SHVEC_REMOVE(my_int_vec, 11) == 0);
        ASSERT(SHVEC_REMOVE(my_int_vec, 10) == 1);
        ASSERT(SHVEC_REMOVE(my_int_vec, 3) == 1);
        ASSERT(SHVEC_REMOVE(my_int_vec, 0) == 1);
        ASSERT(SHVEC_REMOVE(my_int_vec, 12) == 0);

        ASSERT(my_int_vec.cap == 16);
        ASSERT(my_int_vec.sz == 8);

        int expected[] = {150, -4, 18, -5, -1, -7, 0, 0};
        ASSERT_MEM_MATCHES(my_int_vec.values, expected, 8);
    }


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
