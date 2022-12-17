#include <unity.h>
#include <sl_list.h>

int err;
SL_List list;

void setUp (void) {
  list = sll_init();
  err = 0;
}

void tearDown (void) {
  sll_free(list, &err);
}

void
t_init_not_return_NULL()
{
  TEST_ASSERT_NOT_EQUAL(NULL, list);
}

void
t_push_to_empty_size_will_be_1()
{
  sll_push_to_empty(list, 10, &err);
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
}

void
t_is_empty()
{
  TEST_ASSERT_EQUAL(1, sll_is_empty(list, &err));
  sll_push_to_empty(list, 10, &err);
  TEST_ASSERT_EQUAL(0, sll_is_empty(list, &err));
}

void
t_push_head_to_empty()
{
  sll_push_head(list, 10, &err);
  
  TEST_ASSERT_EQUAL(0, sll_is_empty(list, &err));
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
}

void
t_push_head_to_non_empty()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  
  TEST_ASSERT_EQUAL(0, sll_is_empty(list, &err));
  TEST_ASSERT_EQUAL(2, sll_size(list, &err));
}

void
t_size()
{
  TEST_ASSERT_EQUAL(0, sll_size(list, &err));

  sll_push_head(list, 10, &err);
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));

  sll_push_head(list, 20, &err);
  TEST_ASSERT_EQUAL(2, sll_size(list, &err));

  sll_push_head(list, 30, &err);
  TEST_ASSERT_EQUAL(3, sll_size(list, &err));
}

void
t_push_tail_to_empty()
{
  sll_push_tail(list, 10, &err);
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
}

void
t_push_tail_to_non_empty()
{
  sll_push_tail(list, 10, &err);
  sll_push_tail(list, 20, &err);
  
  TEST_ASSERT_EQUAL(0, sll_is_empty(list, &err));
  TEST_ASSERT_EQUAL(2, sll_size(list, &err));
}

void
t_push_at_0_to_empty_list()
{
  sll_push_at(list, 0, 10, &err);
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
}

void
t_push_at_0_to_non_empty_list()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 10, &err);
  sll_push_at(list, 0, 20, &err);

  TEST_ASSERT_EQUAL(3, sll_size(list, &err));
}

void
t_push_at_non_empty_list_with_tail_index()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 10, &err);
  sll_push_at(list, 2, 20, &err);
  sll_push_at(list, 3, 20, &err);
  
  
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, sll_size(list, &err));
}

void
t_push_at_invalid_index()
{
  sll_push_at(list, 3, 20, &err);

  TEST_ASSERT_EQUAL(SLL_OUT_OF_BOUNDS, err);
  TEST_ASSERT_EQUAL(0, sll_size(list, &err));

  sll_push_at(list, -1, 20, &err);

  TEST_ASSERT_EQUAL(SLL_OUT_OF_BOUNDS, err);
  TEST_ASSERT_EQUAL(0, sll_size(list, &err));
}

void
t_push_at_valid_index_not_0_or_tail()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);

  sll_push_at(list, 1, 30, &err);
  TEST_ASSERT_EQUAL(3, sll_size(list, &err));

  sll_push_at(list, 2, 30, &err);
  TEST_ASSERT_EQUAL(4, sll_size(list, &err));
}

void
t_peek_empty_list()
{
  int x = 0;
  sll_peek(list, 10, &x, &err);
  TEST_ASSERT_EQUAL(0, x);
  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_peek_head()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 40, &err);
    
  int x = 0;
  sll_peek(list, 0, &x, &err);
  TEST_ASSERT_EQUAL(40, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_peek_tail()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 40, &err);
    
  int x = 0;
  sll_peek(list, 3, &x, &err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_peek_non_empty_list()
{
  sll_push_head(list, 50, &err);
  sll_push_head(list, 40, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 10, &err);

  int x = 0;
  sll_peek(list, 2, &x, &err);
  TEST_ASSERT_EQUAL(30, x);
  TEST_ASSERT_EQUAL(0, err);

  sll_peek(list, 3, &x, &err);
  TEST_ASSERT_EQUAL(40, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_head_from_empty_list()
{
  sll_remove_head(list, &err);
  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_remove_head_from_non_empty_list()
{
  sll_push_head(list, 50, &err);
  sll_push_head(list, 40, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 10, &err);

  sll_remove_head(list, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, sll_size(list, &err));

  int x = 0;
  sll_peek(list, 2, &x, &err);
  TEST_ASSERT_EQUAL(40, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_tail_from_empty_list()
{
  sll_remove_tail(list, &err);
  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_remove_tail_from_non_empty_list()
{
  sll_push_tail(list, 50, &err);
  sll_push_tail(list, 40, &err);
  sll_push_tail(list, 30, &err);
  sll_push_tail(list, 20, &err);
  sll_push_tail(list, 10, &err);

  sll_remove_tail(list, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, sll_size(list, &err));

  int x = 0;
  sll_peek(list, 3, &x, &err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_at_from_empty_list()
{
  sll_remove_at(list, 2, &err);
  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_remove_head_with_remove_at()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 10, &err);

  sll_remove_at(list, 0, &err);

  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_tail_with_remove_at()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 10, &err);
  
  sll_remove_at(list, sll_size(list, &err)-1, &err);

  TEST_ASSERT_EQUAL(1, sll_size(list, &err));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_at_invalid_index()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 10, &err);

  sll_remove_at(list, 10, &err);
  TEST_ASSERT_EQUAL(SLL_OUT_OF_BOUNDS, err);
}

void
t_remove_at_valid_index()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 40, &err);
  sll_push_head(list, 50, &err);

  sll_remove_at(list, 3, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, sll_size(list, &err));

  sll_remove_at(list, 1, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(3, sll_size(list, &err));
}

void
t_reverse_empty()
{
  sll_reverse(list, &err);

  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_reverse_one_item_list()
{
  sll_push_head(list, 10, &err);

  sll_reverse(list, &err);

  TEST_ASSERT_EQUAL(0, err);
}

void
t_reverse_non_empty()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 40, &err);
  sll_push_head(list, 50, &err);

  sll_reverse(list, &err);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_convert_empty_list_to_array()
{
  sll_convert_to_array(list, NULL, &err);

  TEST_ASSERT_EQUAL(SLL_EMPTY, err);
}

void
t_convert_non_empty_list_to_array()
{
  sll_push_head(list, 10, &err);
  sll_push_head(list, 20, &err);
  sll_push_head(list, 30, &err);
  sll_push_head(list, 40, &err);
  sll_push_head(list, 50, &err);

  int array[sll_size(list, &err)];
  sll_convert_to_array(list, array, &err);

  int x = 0, y = 0;
  sll_peek(list, 0, &x, &err);
  sll_peek(list, 4, &y, &err);
  TEST_ASSERT_EQUAL(50, x);
  TEST_ASSERT_EQUAL(10, y);
  TEST_ASSERT_EQUAL(0, err);

  TEST_ASSERT_EQUAL(x, array[0]);
  TEST_ASSERT_EQUAL(y, array[4]);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_init_not_return_NULL);
  RUN_TEST(t_push_to_empty_size_will_be_1);
  RUN_TEST(t_is_empty);
  RUN_TEST(t_push_head_to_empty);
  RUN_TEST(t_push_head_to_non_empty);
  RUN_TEST(t_size);
  RUN_TEST(t_push_tail_to_empty);
  RUN_TEST(t_push_tail_to_non_empty);
  RUN_TEST(t_push_at_0_to_empty_list);
  RUN_TEST(t_push_at_0_to_non_empty_list);
  RUN_TEST(t_push_at_non_empty_list_with_tail_index);
  RUN_TEST(t_push_at_invalid_index);
  RUN_TEST(t_push_at_valid_index_not_0_or_tail);
  RUN_TEST(t_peek_empty_list);
  RUN_TEST(t_peek_head);
  RUN_TEST(t_peek_tail);
  RUN_TEST(t_peek_non_empty_list);
  RUN_TEST(t_remove_head_from_empty_list);
  RUN_TEST(t_remove_head_from_non_empty_list);
  RUN_TEST(t_remove_tail_from_empty_list);
  RUN_TEST(t_remove_tail_from_non_empty_list);
  RUN_TEST(t_remove_at_from_empty_list);
  RUN_TEST(t_remove_head_with_remove_at);
  RUN_TEST(t_remove_tail_with_remove_at);
  RUN_TEST(t_remove_at_invalid_index);
  RUN_TEST(t_remove_at_valid_index);
  RUN_TEST(t_reverse_empty);
  RUN_TEST(t_reverse_one_item_list);
  RUN_TEST(t_reverse_non_empty);
  RUN_TEST(t_convert_empty_list_to_array);
  RUN_TEST(t_convert_non_empty_list_to_array);

  return UNITY_END();
}

