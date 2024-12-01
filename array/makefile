
CFLAGS = -Wall -Wextra -g

array: ./main.c ./array.h
	${CC} ${CFLAGS} ./main.c -o $@ -ggdb3

test: ./test.c ./array.h
	cc ${CFLAGS} -Werror=extra -fsanitize=address,undefined $< -o $@ -ggdb3
	./$@
