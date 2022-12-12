#include <unity.h>
#include <amqueue.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !

int err;
FSQueue *amqueue;

void setUp (void) {
  err = 0;
  amqueue = amq_init();
}

void tearDown (void) {
  amq_free(amqueue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  amq_push(amqueue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, amqueue->size);
  TEST_ASSERT_EQUAL(1, amqueue->s1->size + amqueue->s2->size);
}

void
t_push_one_element_to_non_empty()
{
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, amqueue->size);
  TEST_ASSERT_EQUAL(2, amqueue->s1->size + amqueue->s2->size);
}

void
t_push_multiple_elements_to_non_empty()
{
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);
  amq_push(amqueue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, amqueue->size);
  TEST_ASSERT_EQUAL(4, amqueue->s1->size + amqueue->s2->size);
}

void
t_pop_empty_amqueue()
{
  int x = 0;
  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(AMQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element_amqueue()
{
  int x = 0;
  
  amq_push(amqueue, 10, &err);

  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_pop_multiple_elemnt_amqueue()
{
  int x = 0;
  
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);
  amq_push(amqueue, 40, &err);
  amq_push(amqueue, 50, &err);

  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(4, amqueue->size);
  TEST_ASSERT_EQUAL(4, amqueue->s1->size + amqueue->s2->size);

  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(3, amqueue->size);
  TEST_ASSERT_EQUAL(3, amqueue->s1->size + amqueue->s2->size);
}

void
t_pop_till_clear()
{
  int x = 0;
  
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);

  amq_pop(amqueue, &x, &err);
  amq_pop(amqueue, &x, &err);
  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(0, amqueue->size);
}

void
t_clear()
{
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);

  amq_clear(amqueue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, amqueue->size);
}

void
t_push_after_clearing()
{
  int x = 0;
  
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);

  amq_pop(amqueue, &x, &err);
  amq_pop(amqueue, &x, &err);
  amq_pop(amqueue, &x, &err);

  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 30, &err);

  TEST_ASSERT_EQUAL(0, err);

  amq_pop(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_peek_empty_amqueue()
{
  int x = 0;
  amq_peek(amqueue, &x, &err);

  TEST_ASSERT_EQUAL(AMQUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_amqueue()
{
  int x = 0;
  
  amq_push(amqueue, 10, &err);
  amq_push(amqueue, 20, &err);
  amq_push(amqueue, 30, &err);
  amq_push(amqueue, 40, &err);

  amq_peek(amqueue, &x, &err);

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
  RUN_TEST(t_pop_empty_amqueue);
  RUN_TEST(t_pop_one_element_amqueue);
  RUN_TEST(t_pop_multiple_elemnt_amqueue);
  RUN_TEST(t_pop_till_clear);
  RUN_TEST(t_clear);
  RUN_TEST(t_push_after_clearing);
  RUN_TEST(t_peek_empty_amqueue);
  RUN_TEST(t_peek_non_empty_amqueue);

  return UNITY_END();
}

