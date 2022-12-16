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

typedef struct node *QNode;

typedef struct queue *Queue;

Queue queue_init();
void queue_free(Queue, int*);
void queue_clear(Queue, int*);

void queue_push(Queue, int, int*);
void queue_peek(const Queue, int*, int*);
void queue_pop(Queue, int*, int*);

bool queue_is_valid_node(const QNode);
bool queue_is_valid(const Queue);
bool queue_is_empty(const Queue, int*);
bool queue_is_valid_not_empty(const Queue, int*);
int queue_get_size(const Queue, int*);

#endif
