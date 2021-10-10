#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"

void print_key(char *s){
    printf("%s\n", s);
}

int main(void){
    bst b = bst_new();
    char word[256];
 
    while (1==scanf("%255s", word)){
        b = bst_insert(b, word);
        printf("%d %s\n", bst_search(b, word),word);
    }
    printf("Preorder\n");
    bst_preorder(b, print_key);

    printf("Delete\n");
    b = bst_delete(b, "This");

    printf("Inorder\n");
    bst_inorder(b, print_key);
    bst_free(b);
    return EXIT_SUCCESS;
}

