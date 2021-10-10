#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

typedef enum state {UNVISITED, VISITED_SELF, VISITED_DESCENDENTS} state_t;



graph graph_new(int num_vertices){
  
}

graph graph_free(graph g){
}

void graph_add_edge(graph g, int u, int v){
}

void graph_add_2edges(graph g, int u, int v){
}

void graph_print_list(graph g){
}

void graph_print_state(graph g){
}

void graph_bfs(graph g, int source){
}
