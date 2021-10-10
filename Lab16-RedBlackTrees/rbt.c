#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

static rbt rbt_fix(rbt r);

struct rbt_node{
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

rbt rbt_new(){
    return NULL;
}

rbt right_rotate(rbt r){
    rbt temp = r;
    r = temp->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

rbt left_rotate(rbt r){
    rbt temp = r;
    r = temp->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

static rbt rbt_fix(rbt r){
    
    if(IS_RED(r->left)){

        if(IS_RED(r->left->left)){
            if(IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                return r;
            }else if(IS_BLACK(r->right)){
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
                return r;
            }
        }
        if(IS_RED(r->left->right)){
            if(IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                return r;
            }else if(IS_BLACK(r->right)){
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
                return r;
            }
        }
    }

    if(IS_RED(r->right)){
        if(IS_RED(r->right->left)){
            if(IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                return r;
            }else if(IS_BLACK(r->left)){
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
                return r;
            }
        }
        if(IS_RED(r->right->right)){
            if(IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
                return r;
            }else if(IS_BLACK(r->left)){
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
                return r;
            }
        }
    }
    return r;
}

rbt rbt_insert(rbt r, char *str){
    if(NULL == r){
        r = emalloc(sizeof *r);
        r->key = emalloc((strlen(str)+1) * sizeof str[0]);
        strcpy(r->key, str);
        r->colour = RED;
        r->left = rbt_new();
        r->right = rbt_new();
        /*r = rbt_fix(r);
          return r;*/
    }
    else{
        /*if(strcmp(str, r->key)==0) return r;
        else{*/
        if(strcmp(str, r->key)<0){
            r->left = rbt_insert(r->left, str);
        }else{
            r->right = rbt_insert(r->right, str);
        }
        
    }
    r = rbt_fix(r);
    return r;
}

void rbt_preorder(rbt r){
    if(r != NULL){
        if(IS_BLACK(r)) printf("black: %.5s\n", r->key);
        else if(IS_RED(r)) printf("red: %.5s\n", r->key);
    }else{
        return;
    }
    rbt_preorder(r->left);
    rbt_preorder(r->right);
}

rbt minValue(rbt r){
    rbt current = r;
    while(current && current->left != NULL){
        current = current->left;
    }
    return current;
}

rbt rbt_delete(rbt r, char *str){
    rbt temp;
    if(r == NULL) return NULL;

    if(strcmp(str, r->key)<0) r->left = rbt_delete(r->left, str);
    else if(strcmp(str, r->key)>0) r->right = rbt_delete(r->right, str);
    else{
        /* only one child or no child*/
        if(r->left == NULL){
            rbt temp = r->left;
            free(r);
            return temp;
        }
        else if(r->right == NULL){
            rbt temp = r->right;
            free(r);
            return temp;
        }

        /* two children*/
        temp = minValue(r);
        r->key = temp->key;
        r->right = rbt_delete(r->right, temp->key);
    }
    return r;
}
int rbt_search(rbt r, char *key){
    if(r == NULL) return 0;

    if(strcmp(key, r->key)<0) return rbt_search(r->left,key);
    else if(strcmp(key,r->key)>0) return rbt_search(r->right,key);
    else if(strcmp(key,r->key)==0) return 1;
    else{
        return 0;
    }
}

rbt rbt_free(rbt r){
    if(r->left != NULL) r->left =rbt_free(r->left);
    if(r->right != NULL) r->right = rbt_free(r->right);
    free(r->key);
    free(r);

    return NULL;
}
