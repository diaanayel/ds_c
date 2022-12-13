#include <gmqueue.h>


GMQueue*
gmq_init()
{
  GMQueue *gmqueue = malloc(sizeof(GMQueue));
  if(!is_valid_gmqueue(gmqueue)) return NULL;

  Queue *queue = queue_init(NULL);
  if(!is_valid_queue(queue, NULL)) return NULL;
  

  Queue *minq = queue_init(NULL);
  if(!is_valid_queue(minq, NULL)) return NULL;

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
is_valid_gmq_node(const Node * const node)
{
  return (node != NULL);
}

bool
is_valid_gmqueue(const GMQueue * const gmqueue)
{
  return (gmqueue != NULL);
}

bool
is_empty_gmqueue(const GMQueue * const gmqueue, int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return GMQUEUE_NULL;

  return (gmqueue->size == 0);
}

void
gmq_push(GMQueue *gmqueue, int data, int *err)
{
  if(!is_valid_gmqueue(gmqueue)) return;

  if(is_empty_gmqueue(gmqueue, err))
  {
    queue_push(gmqueue->queue, data,err);
    queue_push(gmqueue->minq, data,err);

    gmqueue->size++;
    
    return;
  }



  /*
  12  q, minq
  5   
  
  */

  

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

}

