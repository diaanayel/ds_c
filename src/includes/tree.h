#ifndef _H_TREE
#define _H_TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TREE_EMPTY -1
#define TREE_NOT_EMPTY -2
#define TREE_NULL -3
#define TREE_NODE_NULL -4
#define TREE_OUT_OF_BOUNDS -4

typedef struct tnode
{
  int data;
  struct tnode *rt;
  struct tnode *lt;
} TNode;

typedef struct
{
  int size;
  TNode *root;
} Tree;

Tree* tree_init();
void tree_free(Tree*, int*);
void tree_free_node(TNode*);
void tree_clear(Tree*, int*);
void tree_visualize(const Tree * const, int*);
void tree_visualize_node(const TNode * const);

void tree_push(Tree * const, int, int*);
bool tree_search(const Tree * const, int, int*);
void tree_pop(Tree * const, int*, int*);
void tree_get_min(const Tree * const, int*, int*);

void tree_insert_node(TNode*, int, int *);

bool tree_is_valid(const Tree * const);
bool tree_is_valid_tnode(const TNode * const);
bool tree_is_empty(const Tree * const, int*);

#endif
