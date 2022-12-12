#include <stack.h>

Stack*
stack_init()
{
  Stack *stack = malloc(sizeof(Stack));
  if(!is_valid_stack(stack)) return NULL;

  stack->size = 0;
  stack->top = NULL;

  return stack;
}

void
stack_free(Stack *stack, int *err)
{
  if(!is_valid_stack(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  Node *holder;
  
  while(stack->top != NULL)
  {
    holder = stack->top;
    stack->top = stack->top->next;

    free(holder);
    holder = NULL;
  }
  free(stack);
  stack = NULL;
}

bool
is_valid_stack_node(const Node * const node)
{
  return node != NULL;
}

bool
is_valid_stack(const Stack * const stack)
{
  return stack != NULL;
}

bool
is_empty_stack(const Stack * const stack)
{
  if(!is_valid_stack(stack)) return STACK_NULL;

  return (stack->size == 0) ;
}

void
stack_push(Stack * const stack, int data, int *err)
{
  if(!is_valid_stack(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  Node *new_top = malloc(sizeof(Node));
  if(!is_valid_stack_node(new_top))
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
stack_peek(const Stack * const stack, int *output,int *err)
{
  if(!is_valid_stack(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  if(is_empty_stack(stack))
  {
    if(err != NULL)
      *err = STACK_EMPTY;
    return;
  }

  if(output != NULL)
    *output = stack->top->data;
}

void
stack_pop(Stack * const stack, int *output,int *err)
{
  if(!is_valid_stack(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  if(is_empty_stack(stack))
  {
    if(err != NULL)
      *err = STACK_EMPTY;
    return;
  }

  if(output != NULL)
    *output = stack->top->data;

  Node *node_to_remove = stack->top;

  stack->top = stack->top->next;

  free(node_to_remove);

  stack->size--;
}

void
stack_clear(Stack *stack, int *err)
{
  if(!is_valid_stack(stack))
  {
    if(err != NULL)
      *err = STACK_NULL;
    return;
  }

  if(is_empty_stack(stack))
  {
    if(err != NULL)
      *err = STACK_EMPTY;
    return;
  }

  while(stack->size != 0)
    stack_pop(stack, NULL, err);
}

