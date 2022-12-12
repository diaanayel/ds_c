#include "unity_internals.h"
#include <unity.h>
#include <queue_with_stack.h>

void setUp (void) {
}

void tearDown (void) {
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_test_test()
{
  TEST_ASSERT_EQUAL(1, test());
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  RUN_TEST(t_test_test);

  return UNITY_END();
}

