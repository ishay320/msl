# Multiple Small Libraries

This repo contains my standard libraries in c that help me not write everything from scratch every time because c...


## Array

A simple dynamic array implementation that works with any data type.

### Key Features:

- Dynamically resizable to accommodate varying data sizes.
- Type-agnostic: Operates based on the size of the stored data, allowing flexibility without hardcoding types.
- Lightweight: Focused on speed and efficiency.

>Important Note:
This library does not perform runtime type checks. The correct type and size must be carefully managed to avoid runtime errors.

### Usage:

```c
#include "array.h"

int main(int argc, char* argv[])
{
    int* array = array_init(int);
    for (int i = 0; i < 50; i++) {
        array_push(array, i);
    }
    for (size_t i = 0; i < 50; i++) {
        printf("%d\n", array[i]);
    }

    array_free(array);
    return 0;
}
```

## Graph

A lightweight and versatile graph implementation based on dynamic arrays.

### Key Features:

- Dynamic Node and Edge Management: Nodes and edges are stored in dynamically resizable arrays for flexibility(easier for user to iterate over all of them).
- Type-Agnostic Node Data: Nodes can store any type of data.

>Important Note:
This library at the moment wont free your data on 'graph_free', so clean it up yourself.

### Usage:

```c

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Initialize the graph
    struct graph* g = graph_init();

    // Create node data
    int* data1 = malloc(sizeof(*data1));
    int* data2 = malloc(sizeof(*data2));
    *data1 = 42;
    *data2 = 99;

    // Add nodes to the graph
    size_t id1 = graph_node_push(g, data1);
    size_t id2 = graph_node_push(g, data2);

    // Connect nodes with an edge
    if (graph_eadge_create(g, id1, id2)) {
        printf("Edge created between nodes %zu and %zu.\n", id1, id2);
    } else {
        printf("Failed to create edge.\n");
    }

    // Retrieve and print node data
    struct node* node = graph_node_get(g, id1);
    if (node) {
        printf("Node %zu data: %d\n", node->id, *((int*)node->data));
    }

    // Clean up
    graph_free(g);
    free(data1);
    free(data2);

    return 0;
}
```
