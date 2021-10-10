#ifndef RBT_H_
#define RBT_H_

typedef struct rbt_node *rbt;
typedef enum { RED, BLACK } rbt_colour;

extern rbt rbt_delete(rbt r, char *str);
extern rbt rbt_free(rbt r);
extern rbt rbt_insert(rbt r, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt r);
extern int rbt_search(rbt r, char *str);
extern rbt right_rotate(rbt r);
extern rbt left_rotate(rbt r);

#endif
