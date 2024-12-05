CFLAGS = -Wall -Wextra -g -Werror=extra -fsanitize=address,undefined 

all: graph array

test: graph array
	./graph
	./array

.PHONY: all test

graph: ./graph_test.c ../graph.h
	cc ${CFLAGS} $< -o $@ -ggdb3

array: ./array_test.c ../array.h
	cc ${CFLAGS} $< -o $@ -ggdb3

