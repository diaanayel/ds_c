#ifndef _H_SL_LIST
#define _H_SL_LIST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SLL_EMPTY -1
#define SLL_NOT_EMPTY -2
#define SLL_NULL -3
#define SLL_NODE_NULL -4
#define SLL_OUT_OF_BOUNDS -4

typedef struct slnode *SLNode;
typedef struct sl_list *SL_List;


void sll_push_head(SL_List, int, int*);
void sll_push_tail(SL_List, int, int*);
void sll_push_at(SL_List, int, int, int*);

void sll_remove_at(SL_List const, int, int*);
void sll_remove_head(SL_List, int*);
void sll_remove_tail(SL_List, int*);

void sll_peek(const SL_List, int, int*, int*);
void sll_print(const SL_List, int*);

SL_List sll_init();
void sll_free(SL_List, int*);
bool sll_is_empty(const SL_List, int*);

bool sll_is_valid_index(const SL_List, int, int*);
bool sll_is_valid_node(const SLNode);
bool sll_is_valid_list(const SL_List);
bool sll_is_valid_not_empty(const SL_List, int*);

void sll_reverse(SL_List, int*);
void sll_push_to_empty(SL_List, int, int*);
void sll_clear_error_code(SL_List, int*);
int sll_size(const SL_List, int*);

SLNode sll_get_node_at(const SL_List, int, int*);

void sll_convert_to_array(SL_List, int*, int*);

#endif
