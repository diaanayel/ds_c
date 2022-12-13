#include <unity.h>
#include <gmqueue.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !

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
t_push_one_element_to_non_empty()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, gmqueue->size);
}

void
t_push_multiple_elements_to_non_empty()
{
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 30, &err);
  gmq_push(gmqueue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, gmqueue->size);
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

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_pop_two_elemnt_gmqueue()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);

  gmq_pop(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, gmqueue->size);

  gmq_pop(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(0, gmqueue->size);
}

void
t_pop_till_clear()
{
  int x = 0;
  
  gmq_push(gmqueue, 10, &err);
  gmq_push(gmqueue, 20, &err);
  gmq_push(gmqueue, 30, &err);

  gmq_pop(gmqueue, &x, &err);
  gmq_pop(gmqueue, &x, &err);
  gmq_pop(gmqueue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(30, x);
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


int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  // RUN_TEST(t_init_and_free);
  RUN_TEST(t_push_to_empty);
  // RUN_TEST(t_push_one_element_to_non_empty);
  // RUN_TEST(t_push_multiple_elements_to_non_empty);
  // RUN_TEST(t_pop_empty_gmqueue);
  // RUN_TEST(t_pop_one_element_gmqueue);
  // RUN_TEST(t_pop_two_elemnt_gmqueue);
  // RUN_TEST(t_pop_till_clear);
  // RUN_TEST(t_clear);
  // RUN_TEST(t_push_after_clearing);
  // RUN_TEST(t_peek_empty_gmqueue);
  // RUN_TEST(t_peek_non_empty_gmqueue);

  return UNITY_END();
}

