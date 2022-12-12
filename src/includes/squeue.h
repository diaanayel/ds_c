#ifndef _H_SQUEUE
#define _H_SQUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stack.h>

#define SQUEUE_EMPTY -1
#define SQUEUE_NOT_EMPTY -2
#define SQUEUE_NULL -3
#define SQUEUE_NODE_NULL -4
#define SQUEUE_OUT_OF_BOUNDS -4

typedef struct{
  int size;
  Stack *s1;
  Stack *s2;

} SQueue;


SQueue* squeue_init(int*);
bool is_valid_squeue(const SQueue * const, int*);
bool is_empty_squeue(const SQueue * const, int*);
void squeue_free(SQueue*, int*);

void squeue_push(SQueue*, int, int*);
void squeue_peek(const SQueue * const, int*, int*);
void squeue_pop(SQueue * const, int*, int*);


#endif
