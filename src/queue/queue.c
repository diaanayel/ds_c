#include <queue.h>
#include <stdbool.h>

struct node
{
  int data;
  struct node *next;
};

struct queue
{
  int size;
  QNode head, tail;
};

Queue
queue_init()
{
  Queue queue = malloc(sizeof(struct queue));
  if(!queue_is_valid(queue)) return NULL;

  queue->size = 0;
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}

void
queue_free(Queue queue, int *err)
{
  if(!queue_is_valid(queue)) return;

  QNode holder;
  
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
queue_is_valid_node(const QNode node)
{
  return (node != NULL);
}

bool
queue_is_valid(const Queue queue)
{
  return (queue != NULL);
}

bool
queue_is_empty(const Queue queue, int *err)
{
  if(!queue_is_valid(queue))
  {
    if(err)
      *err = QUEUE_NULL;
    return QUEUE_NULL;
  }
  return (queue->size == 0);
}

bool
queue_is_valid_not_empty(const Queue queue, int *err)
{
  if(!queue_is_valid(queue))
  {
    if(err != NULL)
      *err = QUEUE_NULL;
    return false;
  }

  if(queue_is_empty(queue, err))
  {
    if(err != NULL)
      *err = QUEUE_EMPTY;
    return false;
  }
  return true;
}

int
queue_get_size(const Queue queue, int *err)
{
  if(!queue_is_valid(queue))
  {
    if(err != NULL)
      *err = QUEUE_NULL;
    return -1;
  }
  return (queue->size);
}

void
queue_push(Queue queue, int data, int *err)
{
  if(!queue_is_valid(queue)) return;

  QNode node = malloc(sizeof(struct node));
  if(!queue_is_valid_node(node))
  {
    if(err != NULL)
      *err = QUEUE_NODE_NULL;
    return;
  }
  node->data = data;
  node->next = NULL;

  if(queue_is_empty(queue, err))
    queue->head = queue->tail = node;
  else
  {
    queue->tail->next = node;
    queue->tail = node;
  }

  queue->size++;
}

void
queue_peek(const Queue queue, int *output,int *err)
{
  if(!queue_is_valid_not_empty(queue, err)) return;

  if(output != NULL)
    *output = queue->head->data;
}

void
queue_pop(Queue queue, int *output,int *err)
{
  if(!queue_is_valid_not_empty(queue, err)) return;

  QNode node = queue->head;
  if(!queue_is_valid_node(node)) return;

  if(output != NULL)
   *output = node->data;

  queue->head = queue->head->next;

  free(node);

  queue->size--;
}

void
queue_clear(Queue queue, int *err)
{
  if(!queue_is_valid_not_empty(queue, err)) return;

  while(queue->size != 0)
    queue_pop(queue, NULL, err);
}

