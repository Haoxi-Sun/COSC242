#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "graph.h"

int main(void) {
    graph g;
    int size, u, v;

    if (1 == scanf("%d", &size)){
        g = graph_new(size);
    } else {
        exit(EXIT_FAILURE);
    }

    while (2 == scanf("%d%d", &u, &v)){
        graph_add_2edges(g, u, v);
    }
    graph_bfs(g, 1);

    graph_print_list(g);
    g = graph_free(g);
    return EXIT_SUCCESS;
}
