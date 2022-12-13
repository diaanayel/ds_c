#include <queue.h>

Queue*
queue_init()
{
  Queue *queue = malloc(sizeof(Queue));
  if(!is_valid_queue(queue)) return NULL;

  queue->size = 0;
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}

void
queue_free(Queue *queue, int *err)
{
  if(!is_valid_queue(queue)) return;

  Node *holder;
  
  while(queue->head != NULL)
  {
    holder = queue->head;

    queue->head = queue->head->next;

    free(holder);
    holder = NULL;
  }

  free(queue);
  queue = NULL;
}

bool
is_valid_queue_node(const Node * const node)
{
  return (node != NULL);
}

bool
is_valid_queue(const Queue * const queue)
{
  return (queue != NULL);
}

bool
is_empty_queue(const Queue * const queue, int *err)
{
  if(!is_valid_queue(queue))
  {
    if(err)
      *err = QUEUE_NULL;
    return QUEUE_NULL;
  }

  return (queue->size == 0);
}

void
queue_push_to_empty(Queue *queue, int data, int *err)
{
  if(!is_valid_queue(queue)) return;
  
  Node *node = malloc(sizeof(Node));
  if(!is_valid_queue_node(node)) return;

  node->data = data;
  node->next = NULL;

  queue->head = node;
  queue->tail = node;
  queue->size++;
}

void
queue_push(Queue *queue, int data, int *err)
{
  if(!is_valid_queue(queue)) return;

  if(is_empty_queue(queue, err))
  {
    queue_push_to_empty(queue, data, err);
    return;
  }

  Node *node = malloc(sizeof(Node));
  if(!is_valid_queue_node(node)) return;

  node->data = data;
  node->next = NULL;

  queue->tail->next = node;
  queue->tail = node;
  queue->size++;
}

void
queue_peek(const Queue * const queue, int *output,int *err)
{
  if(!is_valid_queue(queue)) return;

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
  if(!is_valid_queue(queue)) return;

  if(is_empty_queue(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return;
  }

  Node *node_to_remove = queue->head;
  if(!is_valid_queue_node(node_to_remove)) return;

  if(output != NULL)
   *output = node_to_remove->data;

  queue->head = queue->head->next;

  free(node_to_remove);

  queue->size--;
}

void
queue_clear(Queue *queue, int *err)
{
  if(!is_valid_queue(queue)) return;

  if(is_empty_queue(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return;
  }

  Node *holder = queue->head;
  if(!is_valid_queue_node(holder)) return;

  while(queue->size != 0)
    queue_pop(queue, NULL, err);
}

