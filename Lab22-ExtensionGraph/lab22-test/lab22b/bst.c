#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"

struct bstnode{
    bst right;
    bst left;
    char *keys;
};

bst bst_new(){
    return NULL;
}

bst bst_free(bst b){
    if(b->left!=NULL) b->left = bst_free(b->left);
    if(b->right!=NULL) b->right = bst_free(b->right);
    
    free(b->keys);
    free(b);
    return NULL;
}
void bst_inorder(bst b, void f(char *str)){
    if(b==NULL) return;
    bst_inorder(b->left, f);
    f(b->keys);
    bst_inorder(b->right, f);
}

void bst_preorder(bst b, void f(char *str)){
    if(b==NULL) return;
    f(b->keys);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

bst bst_insert(bst b, char *str){
    if(b==NULL){
        b = emalloc(sizeof *b);
        b->keys = emalloc((strlen(str)+1) * str[0]);
        strcpy(b->keys, str);
        b->left = NULL;
        b->right = NULL;
    }else if(strcmp(b->keys, str)>0) b->left = bst_insert(b->left, str);
    else if(strcmp(b->keys, str)<0) b->right = bst_insert(b->right, str);
    return b;
}

int bst_search(bst b, char *str){
    if(b==NULL) return 0;
    if(strcmp(b->keys, str) > 0) return bst_search(b->left, str);
    else if(strcmp(b->keys, str)<0) return bst_search(b->right, str);
    else if(strcmp(b->keys, str)==0) return 1;
    return 0;
}
