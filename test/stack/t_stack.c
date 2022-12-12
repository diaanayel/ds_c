#include "unity_internals.h"
#include <unity.h>
#include <stack.h>

int err;
Stack *stack;

void setUp (void) {
  err = 0;
  stack = stack_init();
}

void tearDown (void) {
  stack_free(stack, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_stack_init()
{
  TEST_ASSERT_NOT_EQUAL(NULL, stack);
  TEST_ASSERT_EQUAL(0, stack->size);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_push_to_empty_stack()
{
  stack_push(stack, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, stack->size);
  TEST_ASSERT_EQUAL(10, stack->top->data);
}

void
t_push_to_non_empty_stack()
{
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, stack->size);
  TEST_ASSERT_EQUAL(20, stack->top->data);
}

void
t_peek_empty_stack()
{
  int x = 0;

  stack_peek(stack, &x, &err);

  TEST_ASSERT_EQUAL(STACK_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_stack()
{
  stack_push(stack, 10, &err);
  stack_push(stack, 20, &err);
  stack_push(stack, 30, &err);
  stack_push(stack, 40, &err);

  int x = 0;

  stack_peek(stack, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(40, x);
}

void
t_pop_empty_stack()
{
  int x = 0;

  stack_pop(stack, &x, &err);

  TEST_ASSERT_EQUAL(STACK_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_non_empty_stack()
{
  stack_push(stack, 10, &err);
  stack_push(stack, 20, &err);
  stack_push(stack, 30, &err);
  stack_push(stack, 40, &err);

  int x = 0;

  stack_pop(stack, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(3, stack->size);
  TEST_ASSERT_EQUAL(40, x);
  TEST_ASSERT_EQUAL(30, stack->top->data);

  stack_pop(stack, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, stack->size);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(20, stack->top->data);
}

void
t_pop_one_element_stack()
{
  stack_push(stack, 10, &err);

  int x = 0;

  stack_pop(stack, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, stack->size);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(NULL, stack->top);
}

void
t_push_to_stack_after_pop_last_elememt()
{
  stack_push(stack, 10, &err);

  int x = 0;

  stack_pop(stack, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, stack->size);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(NULL, stack->top);

  stack_push(stack, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, stack->size);

  stack_peek(stack, &x, &err);
  TEST_ASSERT_EQUAL(20, x);
}

void
t_clear_empty_stack()
{
  stack_clear(stack, &err);

  TEST_ASSERT_EQUAL(STACK_EMPTY, err);
}

void
t_clear_one_element_stack()
{
  stack_push(stack, 10, &err);

  stack_clear(stack, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, stack->size);
}

void
t_clear_stack_with_multiple_elements()
{
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);

  stack_clear(stack, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, stack->size);
}

void
t_push_after_clearing()
{
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);
  stack_push(stack, 10, &err);

  stack_clear(stack, &err);

  stack_push(stack, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, stack->size);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  RUN_TEST(t_stack_init);
  RUN_TEST(t_push_to_empty_stack);
  RUN_TEST(t_push_to_non_empty_stack);
  RUN_TEST(t_peek_empty_stack);
  RUN_TEST(t_peek_non_empty_stack);
  RUN_TEST(t_pop_empty_stack);
  RUN_TEST(t_pop_non_empty_stack);
  RUN_TEST(t_pop_one_element_stack);
  RUN_TEST(t_push_to_stack_after_pop_last_elememt);
  RUN_TEST(t_clear_empty_stack);
  RUN_TEST(t_clear_one_element_stack);
  RUN_TEST(t_clear_stack_with_multiple_elements);
  RUN_TEST(t_push_after_clearing);

  return UNITY_END();
}

