// queue using one stack + fubction call stack (recursion)

#ifndef _H_FSQUEUE
#define _H_FSQUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stack.h>

#define FSQUEUE_EMPTY -1
#define FSQUEUE_NOT_EMPTY -2
#define FSQUEUE_NULL -3
#define FSQUEUE_NODE_NULL -4
#define FSQUEUE_OUT_OF_BOUNDS -4

typedef struct{
  int size;
  Stack *stack;

} FSQueue;


FSQueue* fsq_init();
void fsq_free(FSQueue*, int*);
void fsq_clear(FSQueue * const, int*);

bool is_valid_fsqueue(const FSQueue * const);
bool is_empty_fsqueue(const FSQueue * const, int*);
void fsq_free(FSQueue*, int*);

void fsq_push(FSQueue * const, int, int*);
void fsq_peek(FSQueue * const, int*, int*);
void fsq_pop(FSQueue * const, int*, int*);

#endif
