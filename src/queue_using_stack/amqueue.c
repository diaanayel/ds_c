#include "stack.h"
#include <amqueue.h>

FSQueue*
amq_init()
{
  FSQueue *amqueue = malloc(sizeof(FSQueue));
  if(!is_valid_amqueue(amqueue)) return NULL;
  
  Stack *s1 = stack_init();
  if(!is_valid_stack(s1)) return NULL;

  Stack *s2 = stack_init();
  if(!is_valid_stack(s2)) return NULL;

  amqueue->s1 = s1;
  amqueue->s2 = s2;

  amqueue->size = 0;

  return amqueue;
}

void
amq_free(FSQueue *amqueue, int *err)
{
  if(!is_valid_amqueue(amqueue)) return;

  stack_free(amqueue->s1, err);
  stack_free(amqueue->s2, err);

  free(amqueue);

  amqueue = NULL;
}

bool
is_valid_amqueue(const FSQueue * const amqueue)
{
  return (amqueue != NULL);
}

bool
is_empty_amqueue(const FSQueue * const amqueue, int *err)
{
  if(!is_valid_amqueue(amqueue))
  {
    if(err != NULL)
      *err = AMQUEUE_NULL;
    return AMQUEUE_NULL;
  }

  return (is_empty_stack(amqueue->s1) &&
          is_empty_stack(amqueue->s2));
}

void
amq_push(FSQueue *amqueue, int data, int *err)
{
  if(!is_valid_amqueue(amqueue))
  {
    if(err != NULL)
      *err = AMQUEUE_NULL;
    return;
  }
  stack_push(amqueue->s1, data, err);

  amqueue->size++;
}

// needs optimization
void
amq_peek(FSQueue * const amqueue, int *output, int *err)
{
  if(!is_valid_amqueue(amqueue))
  {
    if(err != NULL)
      *err = AMQUEUE_NULL;
    return;
  }

  if(is_empty_amqueue(amqueue, err))
  {
    if(err != NULL)
      *err = AMQUEUE_EMPTY;
    return;
  }

  int item;
  if(is_empty_stack(amqueue->s2))
  {
    while(!is_empty_stack(amqueue->s1))
    {
      stack_pop(amqueue->s1, &item, err);

      stack_push(amqueue->s2, item, err);
    }
  }

  if(output != NULL)
    *output = item;
}

void
amq_pop(FSQueue * const amqueue, int *output, int *err)
{
  if(!is_valid_amqueue(amqueue))
  {
    if(err != NULL)
      *err = AMQUEUE_NULL;
    return;
  }

  if(is_empty_amqueue(amqueue, err))
  {
    if(err != NULL)
      *err = AMQUEUE_EMPTY;
    return;
  }

  int item;
  if(is_empty_stack(amqueue->s2))
  {
    while(!is_empty_stack(amqueue->s1))
    {
      stack_pop(amqueue->s1, &item, err);

      stack_push(amqueue->s2, item, err);
    }
  }

  stack_pop(amqueue->s2, &item, err);
  amqueue->size--;

  if(output != NULL)
    *output = item;
}

void
amq_clear(FSQueue * const amqueue, int *err)
{
  if(!is_valid_amqueue(amqueue))
  {
    if(err != NULL)
      *err = AMQUEUE_NULL;
    return;
  }

  stack_clear(amqueue->s1, err);

  if(*err == 0)
    amqueue->size = 0;
}


