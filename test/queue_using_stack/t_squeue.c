#include <unity.h>
#include <squeue.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !

int err;
SQueue *squeue;

void setUp (void) {
  err = 0;
  squeue = squeue_init();
}

void tearDown (void) {
  squeue_free(squeue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  squeue_push(squeue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, squeue->size);
  TEST_ASSERT_EQUAL(1, squeue->s1->size);
  TEST_ASSERT_EQUAL(10, squeue->s1->top->data);
}

void
t_push_one_element_to_non_empty()
{
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, squeue->size);
  TEST_ASSERT_EQUAL(2, squeue->s1->size);
  TEST_ASSERT_EQUAL(10, squeue->s1->top->data);
}


void
t_push_multiple_elements_to_non_empty()
{
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);
  squeue_push(squeue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, squeue->size);
  TEST_ASSERT_EQUAL(10, squeue->s1->top->data);
}

void
t_peek_empty_squeue()
{
  int x = 0;
  squeue_peek(squeue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_squeue()
{
  int x = 0;
  
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);
  squeue_push(squeue, 40, &err);

  squeue_peek(squeue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(squeue->s1->top->data, x);
}

void
t_pop_empty_squeue()
{
  int x = 0;
  squeue_pop(squeue, &x, &err);

  TEST_ASSERT_EQUAL(SQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_non_empty_squeue()
{
  int x = 0;
  
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);
  squeue_push(squeue, 40, &err);

  squeue_pop(squeue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(20, squeue->s1->top->data);
}

void
t_pop_till_clear()
{
  int x = 0;
  
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);

  squeue_pop(squeue, &x, &err);
  squeue_pop(squeue, &x, &err);
  squeue_pop(squeue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(0, squeue->size);
}

void
t_clear()
{
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);

  squeue_clear(squeue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, squeue->size);
}

void
t_push_after_clearing()
{
  int x = 0;
  
  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 20, &err);
  squeue_push(squeue, 30, &err);

  squeue_pop(squeue, &x, &err);
  squeue_pop(squeue, &x, &err);
  squeue_pop(squeue, &x, &err);

  squeue_push(squeue, 10, &err);
  squeue_push(squeue, 30, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, squeue->s1->top->data);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  // RUN_TEST(t_init_and_free);
  RUN_TEST(t_push_to_empty);
  RUN_TEST(t_push_one_element_to_non_empty);
  RUN_TEST(t_push_multiple_elements_to_non_empty);
  RUN_TEST(t_peek_empty_squeue);
  RUN_TEST(t_peek_non_empty_squeue);
  RUN_TEST(t_pop_empty_squeue);
  RUN_TEST(t_pop_non_empty_squeue);
  RUN_TEST(t_pop_till_clear);
  RUN_TEST(t_push_after_clearing);
  RUN_TEST(t_clear);

  return UNITY_END();
}

