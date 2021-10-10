#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "graph.h"

int main(int argc, char **argv){
    int size, v1, v2;
    int bidirectional = 0, bfs = 0, dfs = 0;
    graph g;
    const char *optstring = "bd2";
    char option;

    while((option = getopt(argc, argv, optstring)) != EOF){
        switch(option){
            case 'b':
                bfs = 1;
                break;
            case 'd':
                dfs = 1;
                break;
            case '2':
                bidirectional = 1;
                break;
        }
    }

    if(1 == scanf("%d", &size)){
        g = graph_new(size);
        while(2 == scanf("%d %d", &v1, &v2)){
            if(bidirectional){
                graph_add_2edges(g, v1, v2);
            }else{
                graph_add_edge(g, v1, v2);
            }
        }
        graph_print_list(g);
        printf("\n");
        if(bfs){
             graph_bfs(g, 1);
             graph_print_state(g);
         }
        if(dfs){ }

        g = graph_free(g);
    }
    return EXIT_SUCCESS;
}
