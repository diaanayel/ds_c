#include <sl_list.h>
#include <stdbool.h>

struct slnode
{
  int data;
  struct slnode *next;
};

struct sl_list
{
  int size;
  SLNode head, tail;
};

SL_List
sll_init()
{
  SL_List list = malloc(sizeof(struct sl_list));

  if(list == NULL)
    return NULL;

  list->size = 0;
  list->head = list->tail = NULL;

  return list;
}

bool
sll_is_valid_node(const SLNode node)
{
  return (node != NULL);
}

bool
sll_is_valid_list(const SL_List list)
{
  return (list != NULL);
}

bool
sll_is_empty(const SL_List list, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return true;
  }
  return (list->size == 0);
}

bool
sll_is_valid_not_empty(const SL_List list, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return false;
  }
  if(sll_is_empty(list, err))
  {
    if(err)
      *err = SLL_EMPTY;
    return false;
  }
  return true;
}

bool
sll_is_valid_index(const SL_List list, int index, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return SLL_NULL;
  }
  return (index >= 0 && index <= list->size);
}

SLNode
sll_get_node_at(const SL_List list, int index, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return NULL;

  SLNode holder = list->head;
  if(!sll_is_valid_node(holder))
  {
    if(err)
      *err = SLL_NODE_NULL;
    return NULL;
  }

  int cur_index = 0;

  while(cur_index != index)
  {
    holder = holder->next;
    cur_index++;
  }
  return holder;
}

void
sll_print(const SL_List list, int *err)
{ // make it prettier !
  if(!sll_is_valid_not_empty(list, err)) return;

  SLNode holder = list->head;
  if(!sll_is_valid_node(holder))
  {
    if(err)
      *err = SLL_NODE_NULL;
    return;
  }

  while(holder != NULL)
  {
    printf("%d ", holder->data);
    holder = holder->next;
  }
  printf("\n");
}

void
sll_free(SL_List list, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return;
  }

  while(list->head != NULL)
  {
    SLNode holder = list->head;
    if(!sll_is_valid_node(holder))
    {
      if(err)
        *err = SLL_NODE_NULL;
     return;
    }

    list->head = list->head->next;

    free(holder);
    holder = NULL;
  }
  free(list);
  list = NULL;
}

int
sll_size(const SL_List list, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return -1;
  }
  return (list->size);
}

void
sll_push_to_empty(SL_List list, int data, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return;
  }

  SLNode node = malloc(sizeof(struct slnode));
  if(!sll_is_valid_node(node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  node->data = data;

  node->next = NULL;
  list->head = node;
  list->tail = node;
  list->size++;  
}


void
sll_push_head(SL_List list, int data, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return;
  }

  if(sll_is_empty(list, err))
  {
    sll_push_to_empty(list, data, err);
    return;
  }
  
  SLNode node = malloc(sizeof(struct slnode));
  if(!sll_is_valid_node(node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  node->data = data;

  node->next = list->head;
  list->head = node;
  list->size++;
}

void
sll_push_tail(SL_List list, int data, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return;
  }

  if(sll_is_empty(list, err))
  {
    sll_push_to_empty(list, data, err);
    return;
  }
 
  SLNode node = malloc(sizeof(struct slnode));
  if(!sll_is_valid_node(node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  node->data = data;

  node->next = NULL;
  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void
sll_push_at(SL_List list, int index, int data, int *err)
{
  if(!sll_is_valid_list(list))
  {
    if(err)
      *err = SLL_NULL;
    return;
  }

  if(!sll_is_valid_index(list, index, err))
  {
    if(err)
      *err = SLL_OUT_OF_BOUNDS;
    return;
  }

  SLNode node = malloc(sizeof(struct slnode));
  if(!sll_is_valid_node(node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  node->data = data;

  if(index == 0)
  {
    sll_push_head(list, data, err);
    return;
  }

  SLNode prev_node = sll_get_node_at(list, index-1, err);
  if(!sll_is_valid_node(prev_node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  node->next = prev_node->next;
  prev_node->next = node;
  list->size++;
}

void
sll_peek(const SL_List list, int index, int *output, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;

  SLNode holder = sll_get_node_at(list, index, err);

  if(output)
    *output = holder->data;
}

void
sll_remove_head(SL_List list, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;

  SLNode node = list->head;
  if(!sll_is_valid_node(node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  list->head = list->head->next;
  free(node);
  list->size--;
}


void
sll_remove_tail(SL_List list, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;
  
  SLNode pre_tail = sll_get_node_at(list, list->size - 2, err);
  if(!sll_is_valid_node(pre_tail))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  free(pre_tail->next);
  pre_tail->next = NULL;
  list->tail = pre_tail;
  list->size--;
}


void
sll_remove_at(SL_List list, int index, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;

  if(!sll_is_valid_index(list, index, err))
  {
    if(err)
      *err = SLL_OUT_OF_BOUNDS;
    return;
  }

  if(index == 0)
  {
    sll_remove_head(list, err);
    return;
  }

  if(index == list->size - 1)
  {
    sll_remove_tail(list, err);
    return;
  }

  SLNode prev_node = sll_get_node_at(list, index-1, err);
  if(!sll_is_valid_node(prev_node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }

  SLNode next_node = prev_node->next->next;
  if(!sll_is_valid_node(next_node))
  {
    if(err)
      *err = SLL_NODE_NULL;
   return;
  }
  
  free(prev_node->next);
  prev_node->next = next_node;
  list->size--;
}

void
sll_reverse(SL_List list, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;

  if(list->size == 1) return;

  list->tail = list->head;

  SLNode prev = list->head;
  SLNode node = prev->next;

  while(node != NULL)
  {
    SLNode next = node->next;
    node->next = prev;
    prev = node;
    node = next;
  }

  list->head = prev;
  list->tail->next = NULL;
}

void
sll_convert_to_array(SL_List list, int *array, int *err)
{
  if(!sll_is_valid_not_empty(list, err)) return;

  SLNode holder = list->head;
  if(!sll_is_valid_node(holder))
  {
    if(err)
      *err = SLL_NODE_NULL;
    return;
  }

  int index = 0;
  while(holder != NULL)
  {
    array[index++] = holder->data;
    holder = holder->next;
  }
}

