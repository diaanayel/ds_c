#include "queue.h"
#include <gmqueue.h>
#include <stdbool.h>


GMQueue*
gmq_init()
{
  GMQueue *gmqueue = malloc(sizeof(GMQueue));
  if(!is_valid_gmqueue(gmqueue)) return NULL;

  Queue *queue = queue_init();
  if(!is_valid_queue(queue)) return NULL;
  

  Queue *minq = queue_init();
  if(!is_valid_queue(minq)) return NULL;

  gmqueue->queue = queue;
  gmqueue->minq = minq;

  gmqueue->size = 0;

  return gmqueue;
}

void
gmq_free(GMQueue *gmqueue, int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  queue_free(gmqueue->queue, err);
  queue_free(gmqueue->minq, err);

  free(gmqueue);
  gmqueue = NULL;
}

bool
is_valid_gmqueue(const GMQueue * const gmqueue)
{
  return (gmqueue != NULL);
}

bool
is_empty_gmqueue(const GMQueue * const gmqueue, int *err)
{
  if(!is_valid_gmqueue(gmqueue))
  {
    if(err) *err = GMQUEUE_NULL;
    return GMQUEUE_NULL;
  }

  return (gmqueue->size == 0);
}

void
gmq_push(GMQueue *gmqueue, int data, int *err)
{
  if(!is_valid_gmqueue(gmqueue))
  {
    if(err) *err = GMQUEUE_NULL;
    return;
  }

  if(is_empty_gmqueue(gmqueue, err))
  {
    queue_push(gmqueue->queue, data,err);
    queue_push(gmqueue->minq, data,err);

    gmqueue->size++;
    
    return;
  }

  int min;
  queue_peek(gmqueue->minq, &min, err);
  
  while(!(is_empty_queue(gmqueue->minq, err)))
  {
    queue_peek(gmqueue->minq, &min, err);

    if(data > min)
      break;

    queue_pop(gmqueue->minq, &min, err);
  }

  queue_push(gmqueue->queue, data, err);
  queue_push(gmqueue->minq, data, err);

  gmqueue->size++;
}

void
gmq_peek(const GMQueue * const gmqueue, int *output,int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  if(is_empty_gmqueue(gmqueue, err))
  {
    if(err != NULL)
      *err = GMQUEUE_EMPTY;
    return;
  }
  queue_peek(gmqueue->queue, output, err);
}

void
gmq_get_min(const GMQueue * const gmqueue, int *output,int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  if(is_empty_gmqueue(gmqueue, err))
  {
    if(err != NULL)
      *err = GMQUEUE_EMPTY;
    return;
  }
  queue_peek(gmqueue->minq, output, err);
}

void
gmq_pop(GMQueue * const gmqueue, int *output,int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  if(is_empty_gmqueue(gmqueue, err))
  {
    if(err != NULL)
      *err = GMQUEUE_EMPTY;
    return;
  }

  int min, first;
  queue_pop(gmqueue->queue, &first, err);
  queue_peek(gmqueue->minq, &min, err);

  if(min == first)
    queue_pop(gmqueue->minq, NULL, err);

  if(output)
    *output = first;

  gmqueue->size--;
}

void
gmq_clear(GMQueue *gmqueue, int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  if(is_empty_gmqueue(gmqueue, err))
  {
    if(err != NULL)
      *err = GMQUEUE_EMPTY;
    return;
  }

  while(!is_empty_gmqueue(gmqueue, err))
    gmq_pop(gmqueue, NULL, err);
}

