

CFLAGS = -Wall -Wextra -g

test: ./test.c ./graph.h
	cc ${CFLAGS} -Werror=extra -fsanitize=address,undefined $< -o $@ -ggdb3
	./$@
