#include "stack.h"
#include <squeue.h>

SQueue*
sq_init()
{
  SQueue *squeue = malloc(sizeof(SQueue));
  if(!is_valid_squeue(squeue)) return NULL;
  
  Stack *s1 = stack_init();
  if(!is_valid_stack(s1)) return NULL;

  Stack *s2 = stack_init();
  if(!is_valid_stack(s2)) return NULL;

  squeue->s1 = s1;
  squeue->s2 = s2;

  squeue->size = 0;

  return squeue;
}

void
sq_free(SQueue *squeue, int *err)
{
  if(!is_valid_squeue(squeue)) return;

  stack_free(squeue->s1, err);
  stack_free(squeue->s2, err);

  free(squeue);

  squeue = NULL;
}

bool
is_valid_squeue(const SQueue * const squeue)
{
  return (squeue != NULL);
}

bool
is_empty_squeue(const SQueue * const squeue, int *err)
{
  if(!is_valid_squeue(squeue))
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return SQUEUE_NULL;
  }

  return (is_empty_stack(squeue->s1) &&
          is_empty_stack(squeue->s2));
}

void
sq_push(SQueue *squeue, int data, int *err)
{
  if(!is_valid_squeue(squeue))
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return;
  }

  if(is_empty_squeue(squeue, err))
  {
    stack_push(squeue->s1, data, err);
    squeue->size++;
    return;
  }

  while(!is_empty_stack(squeue->s1))
  {
    int popped_data;
    stack_pop(squeue->s1, &popped_data, err);

    stack_push(squeue->s2, popped_data, err);
  }

  stack_push(squeue->s1, data, err);

  while(!is_empty_stack(squeue->s2))
  {
    int popped_data;
    stack_pop(squeue->s2, &popped_data, err);

    stack_push(squeue->s1, popped_data, err);
  }

  squeue->size++;
}

void
sq_peek(const SQueue * const squeue, int *output, int *err)
{
  if(!is_valid_squeue(squeue))
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return;
  }

  if(is_empty_squeue(squeue, err)) return;

  if(output != NULL)
    stack_peek(squeue->s1, output, err);
}

void
sq_pop(SQueue * const squeue, int *output, int *err)
{
  if(!is_valid_squeue(squeue))
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return;
  }

  if(is_empty_squeue(squeue, err))
  {
    if(err != NULL)
      *err = SQUEUE_EMPTY;
    return;
  }
  
  stack_pop(squeue->s1, output, err);
  squeue->size--;
}

void
sq_clear(SQueue * const squeue, int *err)
{
  if(!is_valid_squeue(squeue))
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return;
  }
  if(is_empty_squeue(squeue, err))
  {
    if(err != NULL)
      *err = SQUEUE_EMPTY;
    return;
  }

  while(!is_empty_squeue(squeue, err))
    sq_pop(squeue, NULL, err);
}


