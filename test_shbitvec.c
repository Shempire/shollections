#include <stdio.h>

#include "shunit/shunit.h"

#include "shbitvec.h"

void test_bitvec(void) {
    shbitvec my_bitvec = SHBITVEC_EMPTY();

    TEST("shbitvec_append") {
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  -1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 1),  -1);

        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 1),  0);

        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 1),  -1);
        ASSERT_UINT_EQ( my_bitvec.sz,  1);
        ASSERT_UINT_EQ( my_bitvec.vecs.values[0],  1);

        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 0),  1);

        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 1),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 2),  -1);
        ASSERT_UINT_EQ( my_bitvec.sz,  2);
        ASSERT_UINT_EQ( my_bitvec.vecs.values[0],  1);

        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 1),  2);
        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 0),  3);
        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 0),  4);
        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 1),  5);
        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 0),  6);

        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 1),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 2),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 3),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 4),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 5),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 6),  0);
        ASSERT_UINT_EQ( my_bitvec.sz,  7);
        ASSERT_UINT_EQ( my_bitvec.vecs.values[0], 1 | (1 << 2) | (1 << 5));
    }

    TEST("shbitvec_set") {
        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 0, 0),  1);
        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 2, 1),  1);
        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 4, 1),  1);
        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 5, 0),  1);
        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 7, 1),  0);

        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 1),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 2),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 3),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 4),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 5),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 6),  0);
        ASSERT_UINT_EQ( my_bitvec.sz,  7);
        ASSERT_UINT_EQ( my_bitvec.vecs.values[0], (1 << 2) | (1 << 4));
    }

    TEST("shbitvec_extend") {
        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 6),  0);
        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 7),  0);
        ASSERT_UINT_EQ( my_bitvec.sz, 7);
        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 8),  1);
        ASSERT_UINT_EQ( my_bitvec.sz, 8);

        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 63),  1);
        ASSERT_UINT_EQ( my_bitvec.sz,  63);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  1);

        for (int i = 7; i < 63; i++) {
            ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 0),  0);
        }

        ASSERT_INT_EQ(  shbitvec_set(&my_bitvec, 62, 1),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 62),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 63),  -1);

        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 64),  1);
        ASSERT_UINT_EQ( my_bitvec.sz,  64);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  1);

        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 66),  1);
        ASSERT_UINT_EQ( my_bitvec.sz,  66);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  2);


        ASSERT_INT_EQ(  shbitvec_extend(&my_bitvec, 127),  1);
        ASSERT_UINT_EQ( my_bitvec.sz,  127);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  2);


        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 1),  127);
        ASSERT_UINT_EQ( my_bitvec.sz,  128);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  2);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 126),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 127),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 128),  -1);

        ASSERT_INT_EQ(  shbitvec_append(&my_bitvec, 1),  128);
        ASSERT_UINT_EQ( my_bitvec.sz,  129);
        ASSERT_UINT_EQ( my_bitvec.vecs.sz,  3);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 126),  0);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 127),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 128),  1);
        ASSERT_INT_EQ(  shbitvec_get(&my_bitvec, 129),  -1);
    }
}

int main(void) {
    printf("------ test_bitvec\n");
    test_bitvec();
}
