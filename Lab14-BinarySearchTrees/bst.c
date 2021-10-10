#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bstnode{
    char *key;
    bst left;
    bst right;
};

bst bst_new(){
    return NULL;
}

int bst_search(bst b, char *key){
    if(b == NULL) return 0;

    if(strcmp(key, b->key)<0) return bst_search(b->left,key);
    else if(strcmp(key,b->key)>0) return bst_search(b->right,key);
    else if(strcmp(key,b->key)==0) return 1;
    else{
        return 0;
    }
}

bst bst_insert(bst b, char *str){
    if(NULL == b){
        b = emalloc(sizeof *b);
        b->key = emalloc((strlen(str)+1) * sizeof str[0]);
        strcpy(b->key, str);
        b->left = bst_new();
        b->right = bst_new();
    }
    else{
        if(strcmp(str, b->key)<0){
            b->left = bst_insert(b->left, str);
       
        }
        else if(strcmp(str, b->key)>0){
            b->right = bst_insert(b->right, str);
        }
    }
    return b;
}

void bst_inorder(bst b, void f(char *s)){
    if(b == NULL) return;

    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right,f);
}

void bst_preorder(bst b, void f(char *s)){
    if(b == NULL) return;

    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

bst minValue(bst b){
    bst current = b;
    while(current && current->left != NULL){
        current = current->left;
    }
    return current;
}

bst bst_delete(bst b, char *str){
    bst temp;
    if(b == NULL) return NULL;

    if(strcmp(str, b->key)<0) b->left = bst_delete(b->left, str);
    else if(strcmp(str, b->key)>0) b->right = bst_delete(b->right, str);
    else{
        /* only one child or no child*/
        if(b->left == NULL){
            bst temp = b->right;
            free(b);
            return temp;
        }
        else if(b->right == NULL){
            bst temp = b->left;
            free(b);
            return temp;
        }

        /* two children*/
        temp = minValue(b);
        b->key = temp->key;
        b->right = bst_delete(b->right, temp->key);
    }
    return b;
}

bst bst_free(bst b){
    if(b->left != NULL) b->left =bst_free(b->left);
    if(b->right != NULL) b->right = bst_free(b->right);
    free(b->key);
    free(b);

    return NULL;
}
