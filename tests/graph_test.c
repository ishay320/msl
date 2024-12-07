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

void test_graph_node_get()
{
    struct graph* g = graph_init();
    int* p1         = malloc(sizeof(*p1));
    int* p2         = malloc(sizeof(*p2));

    size_t id1 = graph_node_push(g, p1);
    size_t id2 = graph_node_push(g, p2);

    struct node* n1 = graph_node_get(g, id1);
    struct node* n2 = graph_node_get(g, id2);

    assert(n1 != NULL);
    assert(n2 != NULL);

    assert(n1->id == id1);
    assert(n2->id == id2);

    assert(n1->data == p1);
    assert(n2->data == p2);

    assert(graph_node_get(g, 999) == NULL);

    graph_free(g);
    free(p1);
    free(p2);
    printf("Graph node get test passed.\n");
}

bool node_equals(struct node n) { return *((int*)n.data) == 42; }

void test_graph_node_find()
{
    struct graph* g = graph_init();
    int* p1         = malloc(sizeof(*p1));
    int* p2         = malloc(sizeof(*p2));

    *p1 = 42;
    *p2 = 99;

    graph_node_push(g, p1);
    graph_node_push(g, p2);

    struct node* found = graph_node_find(g, node_equals);

    assert(found != NULL);
    assert(*((int*)found->data) == 42);

    graph_free(g);
    free(p1);
    free(p2);
    printf("Graph node find test passed.\n");
}

void test_graph_edge_creation_memory_safety()
{
    struct graph* g = graph_init();
    assert(graph_eadge_create(g, 1, 2) == false);
    assert(array_len(g->edges) == 0);

    graph_free(g);
    printf("Edge creation memory safety test passed.\n");
}

int main()
{
    test_graph_initialization();
    test_push_node();
    test_connect_nodes();
    test_free_graph();
    test_graph_node_get();
    test_graph_node_find();
    test_graph_edge_creation_memory_safety();
    printf("All graph tests passed!\n");

    return 0;
}
