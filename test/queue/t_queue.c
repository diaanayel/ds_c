#include <unity.h>
#include <queue.h>

// memory leaks should be confirmed negative in addition to these tests !
//


int err;
Queue queue;

void setUp (void) {
  err = 0;
  queue = queue_init();
}

void tearDown (void) {
  queue_free(queue, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  queue_push(queue, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, queue_get_size(queue, &err));
}

void
t_push_one_item_to_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue_get_size(queue, &err));
}

void
t_push_multiple_items_to_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, queue_get_size(queue, &err));
}

void
t_peek_empty()
{
  int x = 0;
  queue_peek(queue, &x, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;
  queue_peek(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(4, queue_get_size(queue, &err));
}

void
t_pop_empty()
{
  int x = 0;
  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element()
{
  queue_push(queue, 10, &err);

  int x = 0;
  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue_get_size(queue, &err));
  TEST_ASSERT_EQUAL(10, x);
}

void
t_pop_one_element_from_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(3, queue_get_size(queue, &err));
}


void
t_pop_multiple_elements_from_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 20, &err);
  queue_push(queue, 30, &err);
  queue_push(queue, 40, &err);

  int x = 0;
  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(3, queue_get_size(queue, &err));

  queue_pop(queue, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(2, queue_get_size(queue, &err));
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
  TEST_ASSERT_EQUAL(0, queue_get_size(queue, &err));
  TEST_ASSERT_EQUAL(30, x);

  queue_push(queue, 40, &err);
  queue_push(queue, 50, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, queue_get_size(queue, &err));

  queue_peek(queue, &x, &err);
  TEST_ASSERT_EQUAL(40, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_clear_empty()
{
  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(QUEUE_EMPTY, err);
}

void
t_clear_one_element()
{
  queue_push(queue, 10, &err);

  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue_get_size(queue, &err));
}

void
t_clear_non_empty()
{
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);
  queue_push(queue, 10, &err);

  queue_clear(queue, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, queue_get_size(queue, &err));
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
  TEST_ASSERT_EQUAL(2, queue_get_size(queue, &err));
}

void
t_passing_err_handler_as_null()
{
  int x;
  queue_push(queue, 10, NULL);
  queue_clear(queue, NULL);
  queue_pop(queue, &x, NULL);
  queue_peek(queue, &x, NULL);
}

void
t_passing_outputVar_as_null()
{
  queue_push(queue, 10, NULL);
  queue_clear(queue, NULL);
  queue_pop(queue, NULL, NULL);
  queue_peek(queue, NULL, NULL);
}

void
t_passing_as_null()
{
  queue_push(NULL, 10, NULL);
  queue_clear(NULL, NULL);
  queue_pop(NULL, NULL, NULL);
  queue_peek(NULL, NULL, NULL);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
//   RUN_TEST(t_init);
//   RUN_TEST(t_free);
  RUN_TEST(t_push_to_empty);
  RUN_TEST(t_push_one_item_to_non_empty);
  RUN_TEST(t_push_multiple_items_to_non_empty);
  RUN_TEST(t_peek_empty);
  RUN_TEST(t_peek_non_empty);
  RUN_TEST(t_pop_empty);
  RUN_TEST(t_pop_one_element);
  RUN_TEST(t_pop_one_element_from_non_empty);
  RUN_TEST(t_pop_multiple_elements_from_non_empty);
  RUN_TEST(t_push_after_pop_all_elememts);
  RUN_TEST(t_clear_empty);
  RUN_TEST(t_clear_one_element);
  RUN_TEST(t_clear_non_empty);
  RUN_TEST(t_push_after_clearing);
  RUN_TEST(t_passing_err_handler_as_null);
  RUN_TEST(t_passing_outputVar_as_null);
  RUN_TEST(t_passing_as_null);

  return UNITY_END();
}

