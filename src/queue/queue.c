#include <queue.h>


Queue*
queue_init(int *err)
{
  Queue *queue = malloc(sizeof(Queue));
  if(!is_valid_queue(queue, err)) return NULL;

  queue->size = 0;
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}

void
queue_free(Queue *queue, int *err)
{
  if(!is_valid_queue(queue, err)) return;

  Node *holder;
  
  while(queue->head != NULL)
  {
    holder = queue->head;

    queue->head = queue->head->next;

    free(holder);
    holder = NULL;
  }

  queue->tail = NULL;
  free(queue);
  queue = NULL;
}

bool
is_valid_queue_node(const Node * const node, int *err)
{
  if(node == NULL)
  {
    if(err != NULL)
      *err = QUEUE_NODE_NULL;
    return false;
  }

  return true;
}

bool
is_valid_queue(const Queue * const queue, int *err)
{
  if(queue == NULL)
  {
    if(err != NULL)
      *err = QUEUE_NULL;
    return false;
  }

  return true;
}

bool
is_empty_queue(const Queue * const queue, int *err)
{
  if(!is_valid_queue(queue, err)) return QUEUE_NULL;

  return (queue->size == 0 && queue->head == NULL) ;
}

void
queue_push_to_empty(Queue *queue, int data, int *err)
{
  if(!is_valid_queue(queue, err)) return;
  
  Node *node = malloc(sizeof(Node));
  if(!is_valid_queue_node(node, err)) return;

  node->data = data;
  node->next = NULL;

  queue->head = node;
  queue->tail = node;
  queue->size++;
}

void
queue_push(Queue *queue, int data, int *err)
{
  if(!is_valid_queue(queue, err)) return;

  if(is_empty_queue(queue, err))
  {
    queue_push_to_empty(queue, data, err);
    return;
  }

  Node *new_tail = malloc(sizeof(Node));
  if(!is_valid_queue_node(new_tail, err)) return;

  new_tail->data = data;
  new_tail->next = NULL;

  queue->tail->next = new_tail;
  queue->tail = new_tail;
  queue->size++;
}

void
queue_peek(const Queue * const queue, int *output,int *err)
{
  if(!is_valid_queue(queue, err)) return;

  if(is_empty_queue(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return;
  }

  if(output != NULL)
    *output = queue->head->data;
}

void
queue_pop(Queue * const queue, int *output,int *err)
{
  if(!is_valid_queue(queue, err)) return;

  if(is_empty_queue(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return;
  }

  Node *node_to_remove = queue->head;
  if(!is_valid_queue_node(node_to_remove, err)) return;

  if(output != NULL)
   *output = node_to_remove->data;

  queue->head = queue->head->next;

  free(node_to_remove);

  queue->size--;
}

void
queue_clear(Queue *queue, int *err)
{
  if(!is_valid_queue(queue, err)) return;

  if(is_empty_queue(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return;
  }

  Node *holder = queue->head;
  if(!is_valid_queue_node(holder, err)) return;

  while(queue->size != 0)
    queue_pop(queue, NULL, err);
}

