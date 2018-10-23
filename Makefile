CFLAGS = -Wall -Wextra -std=c99

all: test_shvec

test_shvec: test_shvec.c shvec.h shutil.h
	gcc $(CFLAGS) -o test_shvec test_shvec.c

clean:
	rm -f test_shvec
