// here will be graph structure and support functions for it

#include <stdbool.h>
#include <stddef.h>

#include "array.h"

// Graph base on arrays:
// 1. Nodes array which holds the nodes
// 2. Edges array which holds the edges - every one is 1 connection between
//    nodes and data associated with it

struct node {};
struct edge {};

struct gr_nodes {
    struct node* data;
    size_t len;
    size_t cap;
};

struct gr_edges {
    struct edge* data;
    size_t len;
    size_t cap;
};

struct graph {
    struct gr_nodes nodes;
    struct gr_edges edges;
};

struct graph init_graph();

size_t push_node(struct graph* g, struct node* node);

bool connect_nodes(struct graph* g, size_t node_id_a, size_t node_id_b);
struct node get_node(struct graph* g, size_t node_id);
struct eadge get_eadges(struct graph* g, size_t node_id);
