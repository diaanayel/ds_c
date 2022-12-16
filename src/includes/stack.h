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

typedef struct snode *SNode;
typedef struct stack *Stack;


Stack stack_init();
void stack_free(Stack, int*);
void stack_clear(Stack, int*);

void stack_push(Stack, int, int*);
void stack_peek(const Stack, int*, int*);
void stack_pop(Stack, int*, int*);
int stack_get_size(const Stack, int*);


bool stack_is_valid_node(const SNode);
bool stack_is_valid(const Stack);
bool stack_is_empty(const Stack);
bool stack_is_valid_not_empty(const Stack, int*);

#endif
