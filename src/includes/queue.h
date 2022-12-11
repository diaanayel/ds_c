#ifndef _H_QUEUE
#define _H_QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_EMPTY -1
#define QUEUE_NOT_EMPTY -2
#define QUEUE_NULL -3
#define QUEUE_NODE_NULL -4
#define QUEUE_OUT_OF_BOUNDS -4

typedef struct node
{
  int data;
  struct node *next;
} Node;

typedef struct
{
  int size;
  Node *head;
  Node *tail;
} Queue;

Queue* queue_init(int*);
void queue_free(Queue*, int*);
void queue_clear(Queue*, int*);

void queue_push(Queue*, int, int*);
void queue_peek(const Queue * const, int*, int*);
void queue_pop(Queue * const, int*, int*);

void queue_push_to_empty(Queue*, int, int*);

bool is_valid_queue_node(const Node * const, int*);
bool is_valid_queue(const Queue * const, int*);
bool is_empty_queue(const Queue * const, int*);

#endif
