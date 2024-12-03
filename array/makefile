
CFLAGS = -Wall -Wextra -g

test: ./test.c ./array.h
	cc ${CFLAGS} -Werror=extra -fsanitize=address,undefined $< -o $@ -ggdb3
	./$@
