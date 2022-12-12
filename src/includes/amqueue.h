// amorized queue using one stacks

#ifndef _H_AMQUEUE
#define _H_AMQUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stack.h>

#define AMQUEUE_EMPTY -1
#define AMQUEUE_NOT_EMPTY -2
#define AMQUEUE_NULL -3
#define AMQUEUE_NODE_NULL -4
#define AMQUEUE_OUT_OF_BOUNDS -4

typedef struct{
  int size;
  Stack *s1;
  Stack *s2;

} FSQueue;


FSQueue* amq_init();
void amq_free(FSQueue*, int*);
void amq_clear(FSQueue * const, int*);

bool is_valid_amqueue(const FSQueue * const);
bool is_empty_amqueue(const FSQueue * const, int*);
void amq_free(FSQueue*, int*);

void amq_push(FSQueue * const, int, int*);
void amq_peek(FSQueue * const, int*, int*);
void amq_pop(FSQueue * const, int*, int*);

#endif
