#include <sl_list.h>
#include <stdbool.h>

SL_List*
sll_init(int *err)
{
  SL_List *list = malloc(sizeof(SL_List));

  if(list == NULL) { *err = SLL_NULL; return NULL; }

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

bool
sll_is_valid_node(const Node * const node, int *err)
{
  if(node == NULL) { *err = SLL_NODE_NULL; return false; }

  return true;
}

bool
sll_is_valid_list(const SL_List * const list, int *err)
{
  if(list == NULL) { *err = SLL_NULL; return false; }

  return true;
}

bool
sll_is_empty(const SL_List * const list, int *err)
{
  if(!sll_is_valid_list(list, err)) return SLL_NULL;

  return (list->size == 0 && list->head == NULL && list->tail == NULL) ;
}

bool
sll_is_valid_index(const SL_List * const list, int index, int *err)
{
  if(!sll_is_valid_list(list, err)) return SLL_NULL;

  if(index >= 0 && index <= list->size)
    return true;

  *err = SLL_OUT_OF_BOUNDS;
  return false;
}

Node*
sll_get_node_at(const SL_List* const list, int index, int *err)
{
  if(!sll_is_valid_list(list, err)) return NULL;
  
  if(sll_is_empty(list, err)) return NULL;

  Node *holder = list->head;
  if(!sll_is_valid_node(holder, err)) return NULL;

  int cur_index = 0;

  while(cur_index != index)
  {
    holder = holder->next;
    cur_index++;
  }
  return holder;
}

void
sll_print(const SL_List * const list, int *err)
{ // make it prettier !
  if(!sll_is_valid_list(list, err)) return;

  Node *holder = list->head;
  if(!sll_is_valid_node(holder, err)) return;

  while(holder != NULL)
  {
    printf("%d ", holder->data);
    holder = holder->next;
  }
  printf("\n");
}

void
sll_free(SL_List *list, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  while(list->head != NULL)
  {
    Node *holder = list->head;
    if(!sll_is_valid_node(holder, err)) return;

    list->head = list->head->next;

    free(holder);
    holder = NULL;
  }
  free(list);
  list = NULL;
}

int
sll_size(const SL_List * const list, int *err)
{
  if(!sll_is_valid_list(list, err)) return SLL_NULL;
  return list->size;
}


void
sll_push_to_empty(SL_List *list, int data, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(!sll_is_empty(list, err)) return;

  Node *node = malloc(sizeof(Node));
  if(!sll_is_valid_node(node, err)) return;

  node->data = data;

  node->next = NULL;
  list->head = node;
  list->tail = node;
  list->size++;  
}


void
sll_push_head(SL_List *list, int data, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(sll_is_empty(list, err))
  {
    sll_push_to_empty(list, data, err);
    return;
  }
  
  Node *node = malloc(sizeof(Node));
  if(!sll_is_valid_node(node, err)) return;

  node->data = data;

  node->next = list->head;
  list->head = node;
  list->size++;
}

void
sll_push_tail(SL_List *list, int data, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(sll_is_empty(list, err))
  {
    sll_push_to_empty(list, data, err);
    return;
  }
 
  Node *node = malloc(sizeof(Node));
  if(!sll_is_valid_node(node, err)) return;

  node->data = data;

  node->next = NULL;
  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void
sll_push_at(SL_List *list, int index, int data, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(!sll_is_valid_index(list, index, err)) return;

  Node *node = malloc(sizeof(Node));
  if(!sll_is_valid_node(node, err)) return;

  node->data = data;

  if(index == 0)
  {
    sll_push_head(list, data, err);
    return;
  }

  Node *prev_node = sll_get_node_at(list, index-1, err);
  if(!sll_is_valid_node(prev_node, err)) return;

  node->next = prev_node->next;
  prev_node->next = node;
  list->size++;
}

int
sll_peek(const SL_List* const list, int index, int *err)
{
  if(!sll_is_valid_list(list, err)) return SLL_NULL;
  
  if(sll_is_empty(list, err)) return SLL_EMPTY;

  Node *holder = sll_get_node_at(list, index, err);
  if(!sll_is_valid_node(holder, err)) return SLL_NODE_NULL;
  
  return holder->data;
}

void
sll_remove_head(SL_List *list, int *err)
{
  if(!sll_is_valid_list(list, err)) return;
  
  if(sll_is_empty(list, err))
  {
    *err = SLL_EMPTY;
    return;
  }

  Node *node = list->head;
  if(!sll_is_valid_node(node, err)) return;

  list->head = list->head->next;
  free(node);
  list->size--;
}


void
sll_remove_tail(SL_List *list, int *err)
{
  if(!sll_is_valid_list(list, err)) return;
  
  if(sll_is_empty(list, err))
  {
    *err = SLL_EMPTY;
    return;
  }
  
  Node *pre_tail = sll_get_node_at(list, list->size - 2, err);
  if(!sll_is_valid_node(pre_tail, err)) return;

  free(pre_tail->next);
  pre_tail->next = NULL;
  list->tail = pre_tail;
  list->size--;
}


void
sll_remove_at(SL_List* const list, int index, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(sll_is_empty(list, err))
  {
    *err = SLL_EMPTY;
    return;
  }

  if(!sll_is_valid_index(list, index, err)) return;

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

  Node *prev_node = sll_get_node_at(list, index-1, err);
  if(!sll_is_valid_node(prev_node, err)) return;

  Node *next_node = prev_node->next->next;
  if(!sll_is_valid_node(next_node, err)) return;
  
  free(prev_node->next);
  prev_node->next = next_node;
  list->size--;
}


void
sll_reverse(SL_List *list, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(sll_is_empty(list, err))
  {
    *err = SLL_EMPTY;
    return;
  }

  if(list->size == 1) return;

  list->tail = list->head;

  Node *prev = list->head;
  Node *node = prev->next;

  while(node != NULL)
  {
    Node *next = node->next;
    node->next = prev;
    prev = node;
    node = next;
  }

  list->head = prev;
  list->tail->next = NULL;
}

void
sll_convert_to_array(SL_List *list, int *array, int *err)
{
  if(!sll_is_valid_list(list, err)) return;

  if(sll_is_empty(list, err))
  {
    *err = SLL_EMPTY;
    return;
  }

  Node *holder = list->head;
  if(!sll_is_valid_node(holder, err)) return;

  int index = 0;

  while(holder != NULL)
  {
    array[index++] = holder->data;
    holder = holder->next;
  }
}

