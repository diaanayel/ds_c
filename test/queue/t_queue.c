#include "unity_internals.h"
#include <unity.h>
#include <queue.h>

int err;
Queue *queue;

void setUp (void) {
  err = 0;
  queue = queue_init(&err);
}

void tearDown (void) {
  queue_free(queue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

// can not be left for test because it'll cause problems with the cleanUp()
/*
void
t_queue_init()
{
  err = 0;
  Queue *queue_temp = queue_init(&err);

  TEST_ASSERT_NOT_EQUAL(NULL, queue_temp);
  TEST_ASSERT_EQUAL(0, queue_temp->size);
  TEST_ASSERT_EQUAL(0, queue_temp->head);
  TEST_ASSERT_EQUAL(0, queue_temp->tail);
  TEST_ASSERT_EQUAL(0, err);

  queue_free(queue_temp, &err);
}
*/

// can not be left for test because it'll cause problems with the cleanUp()
// freeing should be confirmed with a tool like valfrind
/*
void
t_queue_free()
{
  err = 0;
  Queue *queue_temp = queue_init(&err);

  TEST_ASSERT_NOT_EQUAL(NULL, queue_temp);
  TEST_ASSERT_EQUAL(0, queue_temp->size);
  TEST_ASSERT_EQUAL(0, err);

  queue_free(queue_temp, &err);

  TEST_ASSERT_EQUAL(NULL, queue);
  TEST_ASSERT_EQUAL(0, err);
}
*/

void
t_push_to_empty_queue()
{
  queue_push(queue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, queue->size);
  TEST_ASSERT_EQUAL(10, queue->head->data);
  TEST_ASSERT_EQUAL(10, queue->tail->data);
}

void
t_push_one_item_to_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue->size);
  TEST_ASSERT_EQUAL(20, queue->tail->data);
  TEST_ASSERT_EQUAL(10, queue->head->data);
}

void
t_push_multiple_items_to_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, queue->size);
  TEST_ASSERT_EQUAL(40, queue->tail->data);
  TEST_ASSERT_EQUAL(10, queue->head->data);
}

void
t_peek_empty_queue()
{
  int x = 0;

  queue_peek(queue, &x, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;

  queue_peek(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_pop_empty_queue()
{
  int x = 0;

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element_queue()
{
  queue_push(queue, 10, &err);

  int x = 0;

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue->size);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(NULL, queue->head);
}

void
t_pop_one_element_from_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(3, queue->size);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(40, queue->tail->data);
  TEST_ASSERT_EQUAL(20, queue->head->data);
}


void
t_pop_multiple_elements_from_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(3, queue->size);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(40, queue->tail->data);
  TEST_ASSERT_EQUAL(20, queue->head->data);


  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue->size);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(40, queue->tail->data);
  TEST_ASSERT_EQUAL(30, queue->head->data);
}


void
t_push_after_pop_all_elememts()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);

  int x = 0;

  queue_pop(queue, &x, &err);
  queue_pop(queue, &x, &err);
  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue->size);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(NULL, queue->head);

  queue_push(queue, 40, &err);
  queue_push(queue, 50, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue->size);

  queue_peek(queue, &x, &err);
  TEST_ASSERT_EQUAL(40, x);
}

void
t_clear_empty_queue()
{
  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
}

void
t_clear_one_element_queue()
{
  queue_push(queue, 10, &err);

  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue->size);
}

void
t_clear_non_empty_queue()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);

  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue->size);
}

void
t_push_after_clearing()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  queue_clear(queue, &err);

  queue_push(queue, 50, &err);
  queue_push(queue, 60, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue->size);

  TEST_ASSERT_EQUAL(50, queue->head->data);
  TEST_ASSERT_EQUAL(60, queue->tail->data);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
//   RUN_TEST(t_queue_init);
//   RUN_TEST(t_queue_free);
  RUN_TEST(t_push_to_empty_queue);
  RUN_TEST(t_push_one_item_to_non_empty_queue);
  RUN_TEST(t_push_multiple_items_to_non_empty_queue);
  RUN_TEST(t_peek_empty_queue);
  RUN_TEST(t_peek_non_empty_queue);
  RUN_TEST(t_pop_empty_queue);
  RUN_TEST(t_pop_one_element_queue);
  RUN_TEST(t_pop_one_element_from_non_empty_queue);
  RUN_TEST(t_pop_multiple_elements_from_non_empty_queue);
  RUN_TEST(t_push_after_pop_all_elememts);
  RUN_TEST(t_clear_empty_queue);
  RUN_TEST(t_clear_one_element_queue);
  RUN_TEST(t_clear_non_empty_queue);
  RUN_TEST(t_push_after_clearing);

  return UNITY_END();
}

