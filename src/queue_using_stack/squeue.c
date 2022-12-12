#include "stack.h"
#include <squeue.h>

SQueue*
squeue_init(int *err)
{
  SQueue *squeue = malloc(sizeof(SQueue));
  if(!is_valid_squeue(squeue, err)) return NULL;
  
  Stack *s1 = stack_init(err);
  if(!is_valid_stack(s1, err)) return NULL;

  Stack *s2 = stack_init(err);
  if(!is_valid_stack(s2, err)) return NULL;

  squeue->s1 = s1;
  squeue->s2 = s2;

  squeue->size = 0;

  return squeue;
}

void
squeue_free(SQueue *squeue, int *err)
{
  if(!is_valid_squeue(squeue, err)) return;

  stack_free(squeue->s1, err);
  stack_free(squeue->s2, err);

  free(squeue);

  squeue = NULL;
}

bool
is_valid_squeue(const SQueue * const squeue, int *err)
{
  if(squeue == NULL)
  {
    if(err != NULL)
      *err = SQUEUE_NULL;
    return false;
  }

  return true;
}

bool
is_empty_squeue(const SQueue * const squeue, int *err)
{
  if(!is_valid_squeue(squeue, err)) return SQUEUE_NULL;

  return (is_empty_stack(squeue->s1, err) &&
          is_empty_stack(squeue->s2, err));
}

void
squeue_push(SQueue *squeue, int data, int *err)
{
  if(!is_valid_squeue(squeue, err)) return;

  if(is_empty_squeue(squeue, err))
  {
    stack_push(squeue->s1, data, err);
    squeue->size++;
    return;
  }

  while(!is_empty_stack(squeue->s1, err))
  {
    int popped_data;
    stack_pop(squeue->s1, &popped_data, err);

    stack_push(squeue->s2, popped_data, err);
  }

  while(!is_empty_stack(squeue->s2, err))
  {
    int popped_data;
    stack_pop(squeue->s2, &popped_data, err);

    stack_push(squeue->s1, popped_data, err);
  }

  squeue->size++;
}

void
squeue_peek(const SQueue * const squeue, int *output, int *err)
{
  if(!is_valid_squeue(squeue, err)) return;

  if(is_empty_squeue(squeue, err)) return;

  stack_peek(squeue->s1, output, err);
}

void
squeue_pop(SQueue * const squeue, int *output, int *err)
{
  if(!is_valid_squeue(squeue, err))
  {
    *err = SQUEUE_NULL;
    return;
  }

  if(is_empty_squeue(squeue, err))
  {
    *err = SQUEUE_EMPTY;
    return;
  }
  
  stack_pop(squeue->s1, output, err);
  squeue->size--;
}





