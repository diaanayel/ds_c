#include <tree.h>

Tree*
tree_init()
{
  Tree *tree = malloc(sizeof(Tree));
  if(!tree_is_valid(tree)) return NULL;

  tree->size = 0;

  return tree;
}

void
tree_free(Tree *tree, int *err)
{
  if(!tree_is_valid(tree)) return;

  tree_free_node(tree->root);

  //free(tree->root);
  free(tree);
  tree = NULL;
}

void
tree_free_node(TNode *node)
{
  if(node)
  {
    tree_free_node(node->rt);
    tree_free_node(node->lt);
    free(node);
  }
}

bool
tree_is_valid(const Tree * const tree)
{
  return (tree != NULL);
}

bool
tree_is_valid_node(const TNode * const node)
{
  return (node != NULL);
}

bool
tree_is_empty(const Tree * const tree, int *err)
{
  if(!tree_is_valid(tree))
  {
    if(err) *err = TREE_NULL;
    return TREE_NULL;
  }
  return (tree->size == 0);
}



void
tree_push(Tree *tree, int data, int *err)
{
  if(!tree_is_valid(tree))
  {
    if(err) *err = TREE_NULL;
    return;
  }

  TNode *node = malloc(sizeof(TNode));
  if(!tree_is_valid_node(node))
  {
    if(err) *err = TREE_NODE_NULL;
    return;
  }
  node->data = data;
  node->rt = NULL;
  node->lt = NULL;

  if(tree_is_empty(tree, err))
  {
    tree->root = node;
    tree->size++;
    return;
  }

  TNode *cur_node = tree->root;
  while(true)
  {
    if(data < cur_node->data)
    {
      if(!cur_node->lt)
      {
        cur_node->lt = node;
        break;
      }
      cur_node = cur_node->lt;
      continue;   
    }

    if(data > cur_node->data)
    {
      if(!cur_node->rt)
      {
        cur_node->rt = node;
        break;
      }
      cur_node = cur_node->rt;
      continue;   
    }
  }
  tree->size++;
}

void
tree_visualize(const Tree * const tree, int *err)
{
  if(!tree_is_valid(tree))
  {
    if(err) *err = TREE_NULL;
    return;
  }

  if(tree_is_empty(tree, err))
  {
    if(err) *err = TREE_EMPTY;
    return;
  }
  tree_visualize_node(tree->root);
}

void
tree_visualize_node(const TNode * const node)
{
  if(node)
  {
    printf(" >>> %d", node->data);

    tree_visualize_node(node->rt);
    tree_visualize_node(node->lt);
  }
}

void
tree_peek(const Tree * const tree, int *output,int *err)
{
  if(!tree_is_valid(tree)) return;

  if(tree_is_empty(tree, err))
  {
    if(err != NULL)
      *err = TREE_EMPTY;
    return;
  }
}

void
tree_get_min(const Tree * const tree, int *output,int *err)
{
  if(!tree_is_valid(tree)) return;

  if(tree_is_empty(tree, err))
  {
    if(err != NULL)
      *err = TREE_EMPTY;
    return;
  }
}

void
tree_pop(Tree * const tree, int *output,int *err)
{
  if(!tree_is_valid(tree)) return;

  if(tree_is_empty(tree, err))
  {
    if(err != NULL)
      *err = TREE_EMPTY;
    return;
  }
}

void
tree_clear(Tree *tree, int *err)
{
  if(!tree_is_valid(tree)) return;

  if(tree_is_empty(tree, err))
  {
    if(err != NULL)
      *err = TREE_EMPTY;
    return;
  }

}

