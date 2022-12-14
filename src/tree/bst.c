#include <bst.h>

struct tnode
{
  int data;
  struct tnode *rt;
  struct tnode *lt;
};

struct bst
{
  int size;
  TNode root;
};

///////////////////
Bst
bst_init()
{
  Bst tree = malloc(sizeof(Bst));
  if(!bst_is_valid(tree)) return NULL;

  tree->size = 0;

  return tree;
}

void
bst_free(Bst tree, int *err)
{
  if(!bst_is_valid(tree)) return;

  bst_free_node(tree->root);
  free(tree);
}

void
bst_free_node(TNode node)
{
  if(node)
  {
    bst_free_node(node->rt);
    bst_free_node(node->lt);
    free(node);
  }
}

bool
bst_is_valid(const Bst tree)
{
  return (tree != NULL);
}

bool
bst_is_valid_node(const TNode node)
{
  return (node != NULL);
}

bool
bst_is_empty(const Bst tree, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return BST_NULL;
  }
  return (tree->size == 0);
}

void
bst_visualize(const Bst tree, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return;
  }

  if(bst_is_empty(tree, err))
  {
    if(err) *err = BST_EMPTY;
    return;
  }

  bst_visualize_node(tree->root);
}

void
bst_visualize_node(const TNode node)
{
  if(node)
  {
    printf(" %d -> ( ", node->data);

    if(node->rt)
      printf(" rt: %d ", node->rt->data);

    if(node->lt)
      printf(" lt: %d ", node->lt->data);

    printf(" )\n");

    bst_visualize_node(node->lt);
    bst_visualize_node(node->rt);
  }
}

void
bst_insert(Bst tree, int data, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return;
  }

  TNode node = malloc(sizeof(TNode));
  if(!bst_is_valid_node(node))
  {
    if(err) *err = BST_NODE_NULL;
    return;
  }

  node->data = data;
  node->rt = NULL;
  node->lt = NULL;

  if(bst_is_empty(tree, err))
  {
    tree->root = node;
    tree->size++;
    return;
  }

  TNode cur_node = tree->root;
  while(true)
  {
    if(data < cur_node->data)
    {
      if(!(cur_node->lt))
      {
        cur_node->lt = node;
        tree->size++;
        return;
      }
      cur_node = cur_node->lt;
    }

    if(data > cur_node->data)
    {
      if(!(cur_node->rt))
      {
        cur_node->rt = node;
        tree->size++;
        return;
      }
      cur_node = cur_node->rt;
    }
  }

}

bool
bst_search(const Bst tree, int target, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err != NULL) *err = BST_NULL;
    return false;
  }

  if(bst_is_empty(tree, err))
  {
    if(err != NULL) *err = BST_EMPTY;
    return false;
  }

  TNode cur_node = tree->root;
  while(cur_node)
  {
    int data = cur_node->data;

    printf(">>> %d, %d, %d\n", data, 
        cur_node->lt->data, cur_node->rt->data);

    if(target == data)
      return true;

    if(target < data)
    {
      printf("moving lt\n");
      cur_node = cur_node->lt;
    }

    if(target > data)
    {
      printf("moving rt\n");
      cur_node = cur_node->rt;
    }
  }

  return false;
}

bool
bst_remove(Bst tree, int target, int *err)
{
  if(!bst_is_valid(tree)) return false;

  if(bst_is_empty(tree, err))
  {
    if(err != NULL)
      *err = BST_EMPTY;
    return false;
  }

  if(tree->size == 1 && target == tree->root->data)
  {
    free(tree->root);
    tree->root = NULL;
    tree->size--;
    return true;
  }

  TNode cur_node = tree->root;
  TNode prev_node;

  while(cur_node)
  {
    if(target == cur_node->data)
    {
      if(!(cur_node->rt) && !(cur_node->lt))
      {
        free(cur_node);

        if(target > prev_node->data)
        {
          printf(">>> rt ");
          prev_node->rt = NULL;
        }
        else
        {
          printf(">>> lt ");
          prev_node->lt = NULL;
        }
      }

      tree->size--;
      return true;
    }

    prev_node = cur_node;

    if(target < cur_node->data)
      cur_node = cur_node->lt;

    if(target > cur_node->data)
      cur_node = cur_node->rt;
  }

  return false;
}

void
bst_clear(Bst tree, int *err)
{
  if(!bst_is_valid(tree)) return;

  if(bst_is_empty(tree, err))
  {
    if(err != NULL)
      *err = BST_EMPTY;
    return;
  }

}

int
bst_size(Bst tree)
{
  if(!bst_is_valid(tree))
    return -1;

  return (tree->size);
}

TNode
bst_get_root(Bst tree, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return NULL;
  }

  if(bst_is_empty(tree, err))
  {
    if(err) *err = BST_EMPTY;
    return NULL;
  }

  return tree->root;
}

void
bst_get_node_data(TNode node, int *output, int *err)
{
  if(!bst_is_valid_node(node))
  {
    if(err) *err = BST_NODE_NULL;
    return;
  }

  if(output)
    *output = node->data;
}
