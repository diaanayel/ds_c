#include <stack.h>


Stack*
stack_init(int *err)
{
  Stack *stack = malloc(sizeof(Stack));
  if(!is_valid_stack(stack, err)) return NULL;

  stack->size = 0;
  stack->top = NULL;

  return stack;
}

void
stack_free(Stack *stack, int *err)
{
  if(!is_valid_stack(stack, err)) return;

  while(stack->top != NULL)
  {
    Node *holder = stack->top;
    if(!is_valid_stack_node(holder, err)) return;

    stack->top = stack->top->next;

    free(holder);
    holder = NULL;
  }
  free(stack);
  stack = NULL;
}

bool
is_valid_stack_node(const Node * const node, int *err)
{
  if(node == NULL) { *err = STACK_NODE_NULL; return false; }

  return true;
}

bool
is_valid_stack(const Stack * const stack, int *err)
{
  if(stack == NULL) { *err = STACK_NULL; return false; }

  return true;
}

bool
is_empty_stack(const Stack * const stack, int *err)
{
  if(!is_valid_stack(stack, err)) return STACK_NULL;

  return (stack->size == 0 && stack->top == NULL) ;
}

void
stack_push(Stack *stack, int data, int *err)
{
  if(!is_valid_stack(stack, err)) return;

  Node *new_top = malloc(sizeof(Node));
  if(!is_valid_stack_node(new_top, err)) return;

  new_top->data = data;
  new_top->next = stack->top;
  stack->top = new_top;
  stack->size++;
}

void
stack_peek(const Stack * const stack, int *output,int *err)
{
  if(!is_valid_stack(stack, err)) return;

  if(is_empty_stack(stack, err)) { *err = STACK_EMPTY; return;}

  *output = stack->top->data;
}

void
stack_pop(Stack * const stack, int *output,int *err)
{
  if(!is_valid_stack(stack, err)) return;

  if(is_empty_stack(stack, err)) { *err = STACK_EMPTY; return;}

  *output = stack->top->data;

  Node *node_to_remove = stack->top;
  if(!is_valid_stack_node(node_to_remove, err)) return;

  stack->top = stack->top->next;

  free(node_to_remove);

  stack->size--;
}

void
stack_clear(Stack *stack, int *err)
{
  if(!is_valid_stack(stack, err)) return;

  if(is_empty_stack(stack, err)) { *err = STACK_EMPTY; return;}

  Node *holder = stack->top;
  if(!is_valid_stack_node(holder, err)) return;

  while(holder != NULL)
  {
    Node *temp = holder;
    holder = holder->next;

    free(temp);
    stack->size--;
  }
  stack->top = NULL;
}

