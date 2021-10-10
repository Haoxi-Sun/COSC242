#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"

int main(void){
    int i;
    rbt r = rbt_new();
    char *words[12] = {"h","l","i","f","j","g","k","d","a","e","b","c"};

    for(i=0;i<12;i++){
        r = rbt_insert(r, words[i]);
        printf("%d %s\n",rbt_search(r, words[i]),words[i]);
    }

    printf("Pre-order\n");
    rbt_preorder(r);
    rbt_free(r);
    return EXIT_SUCCESS;
}

