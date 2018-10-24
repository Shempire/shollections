CFLAGS = -Wall -Wextra -std=c99
UTIL_HEADERS = shutil.h shunit/shunit.h

all: test_shvec test_shbitvec

test_shvec: test_shvec.c shvec.h $(UTIL_HEADERS)
	gcc $(CFLAGS) -o test_shvec test_shvec.c

test_shbitvec: test_shbitvec.c shbitvec.h shvec.h $(UTIL_HEADERS)
	gcc $(CFLAGS) -o test_shbitvec test_shbitvec.c

test: test_shvec test_shbitvec
	./test_shvec
	./test_shbitvec

clean:
	rm -f test_shvec test_shbitvec
