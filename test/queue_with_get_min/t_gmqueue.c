#include "unity_internals.h"
#include <unity.h>
#include <gmqueue.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !
// err returns code if empty in queue_is_empty, look at it, if done and foud this node, remove it !

int err;
GMQueue *gmqueue;

void setUp (void) {
  err = 0;
  gmqueue = gmq_init();
}

void tearDown (void) {
  gmq_free(gmqueue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  gmq_push(gmqueue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, gmqueue->size);
}

void
t_push_one_bigger_element_to_non_empty()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, gmqueue->size);
  TEST_ASSERT_EQUAL(2, gmqueue->minq->size);
  TEST_ASSERT_EQUAL(2, gmqueue->queue->size);
  TEST_ASSERT_EQUAL(10, gmqueue->queue->head->data);
  TEST_ASSERT_EQUAL(20, gmqueue->queue->tail->data);
  TEST_ASSERT_EQUAL(10, gmqueue->minq->head->data);
  TEST_ASSERT_EQUAL(20, gmqueue->minq->tail->data);
}

void
t_push_one_smaller_element_to_non_empty()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 5, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, gmqueue->size);
  TEST_ASSERT_EQUAL(1, gmqueue->minq->size);
  TEST_ASSERT_EQUAL(2, gmqueue->queue->size);
  TEST_ASSERT_EQUAL(10, gmqueue->queue->head->data);
  TEST_ASSERT_EQUAL(5, gmqueue->queue->tail->data);
  TEST_ASSERT_EQUAL(5, gmqueue->minq->head->data);
  TEST_ASSERT_EQUAL(5, gmqueue->minq->tail->data);
}

void
t_push_multiple_elements_to_non_empty()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 3, &err);
  gmq_push(gmqueue, 4, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, gmqueue->size);
  TEST_ASSERT_EQUAL(2, gmqueue->minq->size);
  TEST_ASSERT_EQUAL(4, gmqueue->queue->size);

  TEST_ASSERT_EQUAL(10, gmqueue->queue->head->data);
  TEST_ASSERT_EQUAL(4, gmqueue->queue->tail->data);
  TEST_ASSERT_EQUAL(3, gmqueue->minq->head->data);
  TEST_ASSERT_EQUAL(4, gmqueue->minq->tail->data);
}

void
t_peek_empty_gmqueue()
{
  int x = 0;
  gmq_peek(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(GMQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_gmqueue()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 30, &err);
  gmq_push(gmqueue, 40, &err);

  gmq_peek(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_get_min()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 3, &err);
  gmq_push(gmqueue, 4, &err);

  int x;
  gmq_get_min(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(3, x);
}

void
t_pop_empty_gmqueue()
{
  int x = 0;
  gmq_pop(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(GMQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element_gmqueue()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);

  gmq_pop(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(0, gmqueue->size);
}

void
t_get_min_after_pop_bigger_element()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);

  gmq_pop(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, gmqueue->size);

  gmq_get_min(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
}

void
t_get_min_after_pop_smaller_element()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 4, &err);

  gmq_pop(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);

  gmq_get_min(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, x);
}

void
t_pop_two_elemnt_gmqueue()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);

  gmq_pop(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, gmqueue->size);

  gmq_pop(gmqueue, &x, &err);

  // TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(0, gmqueue->size);
}

void
t_clear()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 30, &err);

  gmq_clear(gmqueue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, gmqueue->size);
}

void
t_push_after_clearing()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 30, &err);

  gmq_pop(gmqueue, &x, &err);
  gmq_pop(gmqueue, &x, &err);
  gmq_pop(gmqueue, &x, &err);

  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 30, &err);

  TEST_ASSERT_EQUAL(0, err);

  gmq_pop(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  // RUN_TEST(t_init_and_free);
  RUN_TEST(t_push_to_empty);
  RUN_TEST(t_push_one_bigger_element_to_non_empty);
  RUN_TEST(t_push_one_smaller_element_to_non_empty);
  RUN_TEST(t_push_multiple_elements_to_non_empty);
  RUN_TEST(t_peek_empty_gmqueue);
  RUN_TEST(t_peek_non_empty_gmqueue);
  RUN_TEST(t_get_min);
  RUN_TEST(t_pop_empty_gmqueue);
  RUN_TEST(t_pop_one_element_gmqueue);
  RUN_TEST(t_get_min_after_pop_bigger_element);
  RUN_TEST(t_get_min_after_pop_smaller_element);
  RUN_TEST(t_pop_two_elemnt_gmqueue);
  RUN_TEST(t_clear);
  RUN_TEST(t_push_after_clearing);

  return UNITY_END();
}

