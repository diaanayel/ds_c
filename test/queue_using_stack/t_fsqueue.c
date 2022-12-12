#include <unity.h>
#include <fsqueue.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !

int err;
FSQueue *fsqueue;

void setUp (void) {
  err = 0;
  fsqueue = fsq_init();
}

void tearDown (void) {
  fsq_free(fsqueue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  fsq_push(fsqueue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, fsqueue->size);
  TEST_ASSERT_EQUAL(1, fsqueue->stack->size);
  TEST_ASSERT_EQUAL(10, fsqueue->stack->top->data);
}

void
t_push_one_element_to_non_empty()
{
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, fsqueue->size);
  TEST_ASSERT_EQUAL(2, fsqueue->stack->size);
  TEST_ASSERT_EQUAL(20, fsqueue->stack->top->data);
}

void
t_push_multiple_elements_to_non_empty()
{
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);
  fsq_push(fsqueue, 30, &err);
  fsq_push(fsqueue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, fsqueue->size);
  TEST_ASSERT_EQUAL(40, fsqueue->stack->top->data);
}

void
t_pop_empty_fsqueue()
{
  int x = 0;
  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(FSQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element_fsqueue()
{
  int x = 0;
  
  fsq_push(fsqueue, 10, &err);

  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_pop_two_elemnt_fsqueue()
{
  int x = 0;
  
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);

  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, fsqueue->size);

  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(0, fsqueue->size);
}

void
t_pop_till_clear()
{
  int x = 0;
  
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);
  fsq_push(fsqueue, 30, &err);

  fsq_pop(fsqueue, &x, &err);
  fsq_pop(fsqueue, &x, &err);
  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(0, fsqueue->size);
}

void
t_clear()
{
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);
  fsq_push(fsqueue, 30, &err);

  fsq_clear(fsqueue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, fsqueue->size);
}

void
t_push_after_clearing()
{
  int x = 0;
  
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);
  fsq_push(fsqueue, 30, &err);

  fsq_pop(fsqueue, &x, &err);
  fsq_pop(fsqueue, &x, &err);
  fsq_pop(fsqueue, &x, &err);

  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 30, &err);

  TEST_ASSERT_EQUAL(0, err);

  fsq_pop(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_peek_empty_fsqueue()
{
  int x = 0;
  fsq_peek(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(FSQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_fsqueue()
{
  int x = 0;
  
  fsq_push(fsqueue, 10, &err);
  fsq_push(fsqueue, 20, &err);
  fsq_push(fsqueue, 30, &err);
  fsq_push(fsqueue, 40, &err);

  fsq_peek(fsqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}


int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  // RUN_TEST(t_init_and_free);
  RUN_TEST(t_push_to_empty);
  RUN_TEST(t_push_one_element_to_non_empty);
  RUN_TEST(t_push_multiple_elements_to_non_empty);
  RUN_TEST(t_pop_empty_fsqueue);
  RUN_TEST(t_pop_one_element_fsqueue);
  RUN_TEST(t_pop_two_elemnt_fsqueue);
  RUN_TEST(t_pop_till_clear);
  RUN_TEST(t_clear);
  RUN_TEST(t_push_after_clearing);
  RUN_TEST(t_peek_empty_fsqueue);
  RUN_TEST(t_peek_non_empty_fsqueue);

  return UNITY_END();
}

