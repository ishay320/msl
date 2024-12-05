#include "../graph.h"

int main()
{
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
