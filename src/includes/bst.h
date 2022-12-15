#ifndef _H_BST
#define _H_BST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BST_EMPTY -1
#define BST_NOT_EMPTY -2
#define BST_NULL -3
#define BST_NODE_NULL -4
#define BST_OUT_OF_BOUNDS -4

typedef struct tnode *TNode;
typedef struct bst *Bst;

Bst bst_init();
void bst_free(Bst, int*);
void bst_free_node(TNode);
void bst_clear(Bst, int*);
void bst_visualize(const Bst, int*);
void bst_visualize_node(const TNode);
int bst_size(Bst);
TNode bst_get_root(Bst, int*);
void bst_get_node_data(TNode, int*, int*);

void bst_insert(Bst const, int, int*);
bool bst_search(const Bst, int, int*);
bool bst_remove(Bst const, int, int*);

void bst_insert_node(TNode, int, int *);

bool bst_is_valid(const Bst);
bool bst_is_valid_tnode(const TNode);
bool bst_is_empty(const Bst, int*);
bool bst_is_valid_not_empty(const Bst, int*);

#endif
