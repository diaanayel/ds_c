#ifndef _H_GMQUEUE
#define _H_GMQUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue.h>

#define GMQUEUE_EMPTY -1
#define GMQUEUE_NOT_EMPTY -2
#define GMQUEUE_NULL -3
#define GMQUEUE_NODE_NULL -4
#define GMQUEUE_OUT_OF_BOUNDS -4

typedef struct
{
  int size;
  Queue *queue;
  Queue *minq;
} GMQueue;

GMQueue* gmq_init();
void gmq_free(GMQueue*, int*);
void gmq_clear(GMQueue*, int*);

void gmq_push(GMQueue*, int, int*);
void gmq_peek(const GMQueue * const, int*, int*);
void gmq_pop(GMQueue * const, int*, int*);
void gmq_get_min(GMQueue * const, int*, int*);


bool is_valid_gmq_node(const Node * const);
bool is_valid_gmqueue(const GMQueue * const);
bool is_empty_gmqueue(const GMQueue * const, int*);

#endif
