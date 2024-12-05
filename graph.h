#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "array.h"

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

bool connect_nodes(struct graph* g, size_t node_id_from, size_t node_id_to)
{
    if (node_id_to == node_id_from || node_id_from > g->inc_id ||
        node_id_to > g->inc_id) {
        return false;
    }

    bool a_exists = false;
    bool b_exists = false;
    for (size_t i = 0; i < array_len(g->nodes); i++) {
        if (g->nodes[i].id == node_id_from) {
            a_exists = true;
        }
        if (g->nodes[i].id == node_id_to) {
            b_exists = true;
        }
    }
    if (a_exists && b_exists) {
        struct edge e;
        e.id_node_from = node_id_from;
        e.id_node_to   = node_id_to;
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

#endif  // GRAPH_H
