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
bst_insert(Bst tree, int data, int *err)
{
  if(!bst_is_valid(tree))
  {
    if(err) *err = BST_NULL;
    return;
  }

  TNode node = (TNode) malloc(sizeof(struct tnode));
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
        break;
      }
      cur_node = cur_node->lt;
    }

    if(data > cur_node->data)
    {
      if(!(cur_node->rt))
      {
        cur_node->rt = node;
        break;
      }
      cur_node = cur_node->rt;
    }
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

    if(target < cur_node->data)
      cur_node = cur_node->lt;
    else
      cur_node = cur_node->rt;
  }
  return false;
}

bool
bst_remove(Bst tree, int target, int *err)
{
  if(!bst_is_valid_not_empty(tree, err)) return false;

  if(tree->size == 1)
  {
    if(target == tree->root->data)
    {
      free(tree->root);
      tree->root = NULL;
      tree->size--;
      return true;
    }
    return false;
  }

  TNode cur_node = tree->root, prev_node = tree->root;

  while(cur_node)
  {
    printf("cur: %d, prev: %d\n", cur_node->data, prev_node->data);
    if(target == cur_node->data)
    {
      printf("found %d at ", cur_node->data);
      if(!(cur_node->rt) && !(cur_node->lt))
      {
        free(cur_node);
        if(target > prev_node->data)
        {
          printf("rt ");
          prev_node->rt = NULL;
        }
        else
        {
          printf("lt ");
          prev_node->lt = NULL;
        }
      }
      printf("of %d\n", prev_node->data);
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
