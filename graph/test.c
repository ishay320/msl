#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../array/array.h"

// Graph base on arrays:
// 1. Nodes array which holds the nodes
// 2. Edges array which holds the edges - every one is 1 connection between
//    nodes and data associated with it

struct payload {};

struct edge {
    size_t id_node_from;
    size_t id_node_to;
};

struct node {
    size_t id;
    struct payload data;
};

// struct gr_nodes {
//     struct node** data;
//     size_t len;
//     size_t cap;
// };
//
// struct gr_edges {
//     struct edge** data;
//     size_t len;
//     size_t cap;
// };

struct graph {
    struct node* nodes;
    struct edge* edges;

    size_t inc_id;
};

struct graph* init_graph()
{
    struct graph* g = malloc(sizeof(struct graph));
    g->nodes        = array_init(struct node);
    g->edges        = array_init(struct edge);
    g->inc_id       = 0;

    return g;
}

size_t push_node(struct graph* g, struct payload p)
{
    struct node node;
    node.id   = g->inc_id++;
    node.data = p;

    array_push(g->nodes, node);

    return node.id;
}

bool connect_nodes(struct graph* g, size_t node_id_a, size_t node_id_b)
{
    if (node_id_b != node_id_a || node_id_a < g->inc_id ||
        node_id_b < g->inc_id) {
        return false;
    }

    bool a_exists = false;
    bool b_exists = false;
    for (size_t i = 0; i < array_len(g->nodes); i++) {
        if (g->nodes[i].id == node_id_a) {
            a_exists = true;
        }
        if (g->nodes[i].id == node_id_b) {
            b_exists = true;
        }
    }
    if (a_exists && b_exists) {
        struct edge e;
        array_push(g->edges, e);
        return true;
    }
    return false;
}

void free_graph(struct graph* g)
{
    array_free(g->nodes);
    array_free(g->edges);
    g->nodes = NULL;
    g->edges = NULL;

    free(g);
}

struct node* get_node(struct graph* g, size_t node_id);
struct node* find_node(struct graph* g, bool (*equals)(struct node*));
struct eadge get_node_eadges(struct graph* g, size_t node_id);

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    struct graph* g = init_graph();

    size_t node_ids[10];
    for (int i = 0; i < 10; i++) {
        struct payload p;
        node_ids[i] = push_node(g, p);
    }

    for (size_t i = 0; i < 4; i++) {
        connect_nodes(g, node_ids[rand() % 10], node_ids[rand() % 10]);
    }

    free_graph(g);
    return 0;
}
