#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

typedef enum state {UNVISITED, VISITED_SELF, VISITED_DESCENDENTS} state_t;

static int step = 0;

struct vertex{
    int predecessor;
    int distance;
    state_t state;
    int finish;
};

struct graphrec{
    int **edges;
    struct vertex *vertices;
    int capacity;
};

graph graph_new(int num_vertices){
    int i, j;
    graph result = emalloc(sizeof *result);

    result->capacity = num_vertices;
    result->vertices = emalloc(result->capacity *sizeof result->vertices[0]);
    result->edges = emalloc(result->capacity *sizeof result->edges[0]);
    for(i=0;i<result->capacity;i++){
        result->edges[i] = emalloc(result->capacity *sizeof result->edges[i][0]);
        for(j=0;j<result->capacity;j++){
            result->edges[i][j] = 0;
        }
    }
    
    return result;
}

graph graph_free(graph g) {
    int i;
    for(i=0;i<g->capacity;i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
    return g;
}

void graph_add_2edges(graph g, int u, int  v) {
    g->edges[u][v] = 1;
    g->edges[v][u] = 1;
}

void graph_add_edge(graph g, int u, int v) {
    g->edges[u][v] = 1;
}

void graph_print_list(graph g) {
    int i, j, count;
    printf("adjacency list:\n");
    for(i=0;i<g->capacity;i++){
        printf("%d | ", i);
        count = 0;
        for(j=0;j<g->capacity;j++){
            if(g->edges[i][j] == 1){
                if(count>0){
                    printf(", %d", j);
                    count++;
                }else{
                    printf("%d", j);
                    count++;
                }
            }
        }
        printf("\n");
    }
    printf("vertex distance pred finish\n");
    for(i=0;i<g->capacity;i++){
        printf("%5d %6d%6d%6d\n", i, g->vertices[i].distance, g->vertices[i].predecessor,
               g->vertices[i].finish);
    }
}


void graph_dfs(graph g) {
    int i, v;
    for(i=0;i<g->capacity;i++){
        g->vertices[i].state = UNVISITED;
        g->vertices[i].predecessor = -1;
    }
    step = 0;
    for(v=0;v<g->capacity;v++){
        if(g->vertices[v].state == UNVISITED){
            visit(g, v);
        }
    }
    
}

void visit(graph g, int v){
    int u;
    g->vertices[v].state = VISITED_SELF;
    step++;
    g->vertices[v].distance = step;
    for(u=0;u<g->capacity;u++){
        if(g->edges[v][u] == 1 && g->vertices[u].state == UNVISITED){
            g->vertices[u].predecessor = v;
            visit(g, u);
        }
    }
    step++;
    g->vertices[v].state = VISITED_DESCENDENTS;
    g->vertices[v].finish = step;
}
