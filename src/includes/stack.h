#ifndef _H_STACK
#define _H_STACK

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_EMPTY -1
#define STACK_NOT_EMPTY -2
#define STACK_NULL -3
#define STACK_NODE_NULL -4
#define STACK_OUT_OF_BOUNDS -4

typedef struct node
{
  int data;
  struct node *next;
} Node;

typedef struct
{
  int size;
  Node *top;
} Stack;

Stack* stack_init();
void stack_free(Stack*, int*);
void stack_clear(Stack*, int*);

void stack_push(Stack * const, int, int*);
void stack_peek(const Stack * const, int*, int*);
void stack_pop(Stack * const, int*, int*);


bool is_valid_stack_node(const Node * const);
bool is_valid_stack(const Stack * const);
bool is_empty_stack(const Stack * const);

#endif
