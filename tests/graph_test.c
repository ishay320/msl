#include "../graph.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_graph_initialization()
{
    struct graph* g = graph_init();
    assert(g != NULL);
    assert(g->nodes != NULL);
    assert(g->edges != NULL);
    assert(g->inc_id == 0);

    graph_free(g);
    printf("Graph initialization test passed.\n");
}

void test_push_node()
{
    struct graph* g = graph_init();
    int* p          = malloc(sizeof(*p));

    size_t id1 = graph_node_push(g, p);
    size_t id2 = graph_node_push(g, p);

    assert(array_len(g->nodes) == 2);
    assert(g->nodes[0].id == id1);
    assert(g->nodes[1].id == id2);

    assert(g->nodes[0].data == p);
    assert(g->nodes[1].data == p);

    graph_free(g);
    free(p);
    printf("Push node test passed.\n");
}

void test_connect_nodes()
{
    struct graph* g = graph_init();
    int* p          = malloc(sizeof(*p));

    size_t id1 = graph_node_push(g, p);
    size_t id2 = graph_node_push(g, p);

    assert(graph_eadge_create(g, id1, id2) == true);
    assert(array_len(g->edges) == 1);

    struct edge e = g->edges[0];
    assert(e.id_node_from == id1);
    assert(e.id_node_to == id2);

    assert(graph_eadge_create(g, id1, 999) == false);

    graph_free(g);
    free(p);
    printf("Connect nodes test passed.\n");
}

void test_free_graph()
{
    struct graph* g = graph_init();
    int* p          = malloc(sizeof(*p));

    graph_node_push(g, p);
    graph_free(g);
    free(p);
    printf("Free graph test passed.\n");
}

int main()
{
    test_graph_initialization();
    test_push_node();
    test_connect_nodes();
    test_free_graph();
    printf("All graph tests passed!\n");

    return 0;
}
