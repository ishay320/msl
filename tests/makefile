CFLAGS = -Wall -Wextra -g

all: graph array
.PHONY: all

graph: ./graph_test.c ../graph.h
	cc ${CFLAGS} -Werror=extra -fsanitize=address,undefined $< -o $@ -ggdb3
	./$@

array: ./array_test.c ../array.h
	cc ${CFLAGS} -Werror=extra -fsanitize=address,undefined $< -o $@ -ggdb3
	./$@
