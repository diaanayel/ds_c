#include "stack.h"
#include <fsqueue.h>

FSQueue*
fsq_init()
{
  FSQueue *fsqueue = malloc(sizeof(FSQueue));
  if(!is_valid_fsqueue(fsqueue)) return NULL;
  
  Stack *stack = stack_init();
  if(!is_valid_stack(stack)) return NULL;

  fsqueue->stack = stack;

  fsqueue->size = 0;

  return fsqueue;
}

void
fsq_free(FSQueue *fsqueue, int *err)
{
  if(!is_valid_fsqueue(fsqueue)) return;

  stack_free(fsqueue->stack, err);

  free(fsqueue);

  fsqueue = NULL;
}

bool
is_valid_fsqueue(const FSQueue * const fsqueue)
{
  return (fsqueue != NULL);
}

bool
is_empty_fsqueue(const FSQueue * const fsqueue, int *err)
{
  if(!is_valid_fsqueue(fsqueue))
  {
    if(err != NULL)
      *err = FSQUEUE_NULL;
    return FSQUEUE_NULL;
  }

  return (is_empty_stack(fsqueue->stack));
}

void
fsq_push(FSQueue *fsqueue, int data, int *err)
{
  if(!is_valid_fsqueue(fsqueue))
  {
    if(err != NULL)
      *err = FSQUEUE_NULL;
    return;
  }
  stack_push(fsqueue->stack, data, err);

  fsqueue->size++;
}

// needs optimization
void
fsq_peek(FSQueue * const fsqueue, int *output, int *err)
{
  if(!is_valid_fsqueue(fsqueue))
  {
    if(err != NULL)
      *err = FSQUEUE_NULL;
    return;
  }

  if(is_empty_fsqueue(fsqueue, err))
  {
    if(err != NULL)
      *err = FSQUEUE_EMPTY;
    return;
  }

  int top;
  stack_pop(fsqueue->stack, &top, err);
  
  if(is_empty_stack(fsqueue->stack))
  {
    if(output != NULL)
      *output = top;

    stack_push(fsqueue->stack, top, err);
    return;
  }

  fsq_pop(fsqueue, output, err);

  stack_push(fsqueue->stack, top, err);
}

void
fsq_pop(FSQueue * const fsqueue, int *output, int *err)
{
  if(!is_valid_fsqueue(fsqueue))
  {
    if(err != NULL)
      *err = FSQUEUE_NULL;
    return;
  }

  if(is_empty_fsqueue(fsqueue, err))
  {
    if(err != NULL)
      *err = FSQUEUE_EMPTY;
    return;
  }

  int top;
  stack_pop(fsqueue->stack, &top, err);
  
  if(is_empty_stack(fsqueue->stack))
  {
    if(output != NULL)
      *output = top;

    fsqueue->size--;
    return;
  }

  fsq_pop(fsqueue, output, err);

  stack_push(fsqueue->stack, top, err);
}

void
fsq_clear(FSQueue * const fsqueue, int *err)
{
  if(!is_valid_fsqueue(fsqueue))
  {
    if(err != NULL)
      *err = FSQUEUE_NULL;
    return;
  }

  stack_clear(fsqueue->stack, err);

  if(*err == 0)
    fsqueue->size = 0;
}


