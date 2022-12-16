#include <bst.h>
#include <stdbool.h>

struct tnode
{
  int data;
  struct tnode *rt, *lt;
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
  Bst tree = (Bst) malloc(sizeof(struct bst));
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
  tree = NULL;
}

void
bst_free_node(TNode node)
{
  if(!node)
    return;

  bst_free_node(node->rt);
  bst_free_node(node->lt);
  free(node);
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

bool
bst_is_valid_not_empty(const Bst tree, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return false;
  }

  if(bst_is_empty(tree, err))
  {
    if(err) *err = BST_EMPTY;
    return false;
  }
  return true;
}

/////////////////////
void
bst_clear(Bst tree, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return;

  bst_free_node(tree->root);
  tree->root = NULL;
  tree->size = 0;
}

int
bst_size(Bst tree)
{
  return (bst_is_valid(tree) ? tree->size : -1);
}

TNode
bst_get_root(Bst tree, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return NULL;

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

void
bst_visualize(const Bst tree, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return;

  bst_visualize_node(tree->root);
}

void
bst_visualize_node(const TNode node)
{
  if(node)
  {
    if(node->lt || node->rt)
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
}

void
bst_inorder(const Bst tree, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return;

  bst_inorder_node(tree->root);
  printf("\n");
}

void
bst_inorder_node(const TNode node)
{
  if(!node)
    return;

  bst_inorder_node(node->lt);
  printf("%d ", node->data);
  bst_inorder_node(node->rt);

}

TNode
bst_create_node(int data, int *err)
{
  TNode node = (TNode) malloc(sizeof(struct tnode));
  if(!bst_is_valid_node(node))
  {
    if(err) *err = BST_NODE_NULL;
    return NULL;
  }

  node->data = data;
  node->rt = NULL;
  node->lt = NULL;

  return node;
}

/////////////////////
void
bst_insert(Bst tree, int data, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return;
  }

  TNode node = bst_create_node(data, err);

  if(bst_is_empty(tree, err))
  {
    tree->root = node;
    tree->size++;
    return;
  }

  TNode cur_node = tree->root;
  while(true)
  {
    if(data < cur_node->data && !(cur_node->lt))
    {
      cur_node->lt = node;
      break;
    }
    if(data > cur_node->data && !(cur_node->rt))
    {
      cur_node->rt = node;
      break;
    }
    cur_node = (data > cur_node->data ? cur_node->rt : cur_node->lt);
  }
  tree->size++;
}

bool
bst_search(const Bst tree, int target, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return false;

  TNode cur_node = tree->root;
  while(cur_node)
  {
    if(target == cur_node->data)
      return true;

    cur_node = (target > cur_node->data ? cur_node->rt : cur_node->lt);
  }
  return false;
}

bool
bst_remove(Bst tree, int target, int *err)
{ // needs refactoeing !
  if(!bst_is_valid_not_empty(tree, err)) return false;

  TNode cur_node = tree->root;
  TNode prev_node = tree->root;
  while(cur_node)
  {
    if(target == cur_node->data)
    {
      if(cur_node->rt && cur_node->lt)
      {
        int min = bst_remove_min_node(cur_node->rt, err);
        if(*err == 0)
          prev_node->data = min;
      }
      else
      {
        TNode valid_node = (cur_node->lt ? cur_node->lt : cur_node->rt);

        if(target > prev_node->data)
          prev_node->rt = valid_node;
        else
          prev_node->lt = valid_node;

        free(cur_node);
      }
      tree->size--;

      if(tree->size == 0) // if root was removed
        tree->root = NULL;

      return true;
    }
    prev_node = cur_node;
    cur_node = (target < cur_node->data ? cur_node->lt : cur_node->rt);
  }
  return false;
}

int
bst_remove_min_node(TNode node, int *err)
{
  if(!bst_is_valid_node(node))
  {
    if(err) *err = BST_NODE_NULL;
    return 0;
  }
  TNode parent = node;
  TNode min = (parent->lt ? parent->lt : parent->rt);

  while(true)
  {
    if(!(min->lt) && !(min->rt))
    {
      int min_data = min->data;

      if(min_data > parent->data)
        parent->rt = NULL;
      else
        parent->lt = NULL;

      free(min);
      return min->data;
    }
    parent = min;
    min = (min->lt ? min->lt : min->rt);
  }
}
