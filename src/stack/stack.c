#include <stack.h>
#include <stdbool.h>

struct snode
{
  int data;
  struct snode *next;
};

struct stack
{
  int size;
  SNode top;
};

Stack
stack_init()
{
  Stack stack = malloc(sizeof(struct stack));
  if(!stack_is_valid(stack)) return NULL;

  stack->size = 0;
  stack->top = NULL;

  return stack;
}

void
stack_free(Stack stack, int *err)
{
  if(!stack_is_valid(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  SNode holder;
  
  while(stack->top != NULL)
  {
    holder = stack->top;
    stack->top = stack->top->next;

    free(holder);
  }
  free(stack);
  stack = NULL;
}

bool
stack_is_valid_node(const SNode node)
{
  return (node != NULL);
}

bool
stack_is_valid(const Stack stack)
{
  return (stack != NULL);
}

bool
stack_is_empty(const Stack stack)
{
  if(!stack_is_valid(stack)) return STACK_NULL;

  return (stack->size == 0);
}

bool
stack_is_valid_not_empty(const Stack stack, int *err)
{
  if(!stack_is_valid(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return false;
  }

  if(stack_is_empty(stack))
  {
    if(err != NULL)
      *err = STACK_EMPTY;
    return false;
  }
  return true;
}

void
stack_push(Stack stack, int data, int *err)
{
  if(!stack_is_valid(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  SNode new_top = malloc(sizeof(struct snode));
  if(!stack_is_valid_node(new_top))
  {
    if(err != NULL)
      *err = STACK_NODE_NULL;
    return;
  }

  new_top->data = data;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->size++;
}

void
stack_peek(const Stack stack, int *output,int *err)
{
  if(!stack_is_valid_not_empty(stack, err)) return;

  if(output != NULL)
    *output = stack->top->data;
}

void
stack_pop(Stack stack, int *output,int *err)
{
  if(!stack_is_valid_not_empty(stack, err)) return;

  SNode top = stack->top;

  if(output != NULL)
    *output = top->data;

  stack->top = stack->top->next;
  free(top);
  stack->size--;
}

void
stack_clear(Stack stack, int *err)
{
  if(!stack_is_valid_not_empty(stack, err)) return;

  while(stack->size != 0)
    stack_pop(stack, NULL, err);
}

int
stack_get_size(const Stack stack, int *err)
{
  if(!stack_is_valid(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return -1;
  }
  return (stack->size);
}
