#include <unity.h>
#include <tree.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !

int err;
Tree *tree;

void setUp (void) {
  err = 0;
  tree = tree_init();
}

void tearDown (void) {
  tree_free(tree, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_push_to_empty()
{
  tree_push(tree, 10, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, tree->size);
  TEST_ASSERT_EQUAL(10, tree->root->data);
}

void
t_push_one_bigger_element_to_non_empty()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, tree->size);
  TEST_ASSERT_EQUAL(10, tree->root->data);
  TEST_ASSERT_EQUAL(20, tree->root->rt->data);
}

void
t_push_one_smaller_element_to_non_empty()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 5, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, tree->size);
  TEST_ASSERT_EQUAL(10, tree->root->data);
  TEST_ASSERT_EQUAL(5, tree->root->lt->data);
}


void
t_push_two_elements_to_non_empty()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 5, &err);
  tree_push(tree, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(3, tree->size);
  TEST_ASSERT_EQUAL(10, tree->root->data);
  TEST_ASSERT_EQUAL(5, tree->root->lt->data);
  TEST_ASSERT_EQUAL(20, tree->root->rt->data);
}

void
t_push_multiple_elements()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 8, &err);
  tree_push(tree, 7, &err);
  tree_push(tree, 9, &err);
  tree_push(tree, 12, &err);
  tree_push(tree, 11, &err);
  tree_push(tree, 14, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(7, tree->size);

  tree_visualize(tree, &err);
}

/*

void
t_peek_empty_tree()
{
  int x = 0;
  tree_peek(tree, &x, &err);

  TEST_ASSERT_EQUAL(TREE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_peek_non_empty_tree()
{
  int x = 0;
  
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);
  tree_push(tree, 30, &err);
  tree_push(tree, 40, &err);

  tree_peek(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_get_min()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);
  tree_push(tree, 3, &err);
  tree_push(tree, 4, &err);

  int x;
  tree_get_min(tree, &x, &err);

  TEST_ASSERT_EQUAL(3, x);
}

void
t_pop_empty_tree()
{
  int x = 0;
  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(TREE_EMPTY, err);
  TEST_ASSERT_EQUAL(0, x);
}

void
t_pop_one_element_tree()
{
  int x = 0;
  
  tree_push(tree, 10, &err);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(0, tree->size);
}

void
t_get_min_after_pop_bigger_element()
{
  int x = 0;
  
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, tree->size);

  tree_get_min(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
}

void
t_get_min_after_pop_smaller_element()
{
  int x = 0;
  
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);
  tree_push(tree, 4, &err);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);

  tree_get_min(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(4, x);
}

void
t_pop_two_elemnt_tree()
{
  int x = 0;
  
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
  TEST_ASSERT_EQUAL(1, tree->size);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(20, x);
  TEST_ASSERT_EQUAL(0, tree->size);
}

void
t_clear()
{
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);
  tree_push(tree, 30, &err);

  tree_clear(tree, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, tree->size);
}

void
t_push_after_clearing()
{
  int x = 0;
  
  tree_push(tree, 10, &err);
  tree_push(tree, 20, &err);
  tree_push(tree, 30, &err);

  tree_pop(tree, &x, &err);
  tree_pop(tree, &x, &err);
  tree_pop(tree, &x, &err);

  tree_push(tree, 10, &err);
  tree_push(tree, 30, &err);

  TEST_ASSERT_EQUAL(0, err);

  tree_pop(tree, &x, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, x);
}

void
t_passing_err_handler_as_null()
{
  int x;
  tree_push(tree, 10, NULL);
  tree_clear(tree, NULL);
  tree_pop(tree, &x, NULL);
  tree_peek(tree, &x, NULL);
}

void
t_passing_outputVar_as_null()
{
  tree_push(tree, 10, NULL);
  tree_clear(tree, NULL);
  tree_pop(tree, NULL, NULL);
  tree_peek(tree, NULL, NULL);
}

void
t_passing_tree_as_null()
{
  tree_push(NULL, 10, NULL);
  tree_clear(NULL, NULL);
  tree_pop(NULL, NULL, NULL);
  tree_peek(NULL, NULL, NULL);
}
*/

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  // RUN_TEST(t_init_and_free);
  RUN_TEST(t_push_to_empty);
  RUN_TEST(t_push_one_bigger_element_to_non_empty);
  RUN_TEST(t_push_one_smaller_element_to_non_empty);
  RUN_TEST(t_push_two_elements_to_non_empty);
  RUN_TEST(t_push_multiple_elements);
  // RUN_TEST(t_peek_empty_tree);
  // RUN_TEST(t_peek_non_empty_tree);
  // RUN_TEST(t_get_min);
  // RUN_TEST(t_pop_empty_tree);
  // RUN_TEST(t_pop_one_element_tree);
  // RUN_TEST(t_get_min_after_pop_bigger_element);
  // RUN_TEST(t_get_min_after_pop_smaller_element);
  // RUN_TEST(t_pop_two_elemnt_tree);
  // RUN_TEST(t_clear);
  // RUN_TEST(t_push_after_clearing);
  // RUN_TEST(t_passing_err_handler_as_null);
  // RUN_TEST(t_passing_outputVar_as_null);
  // RUN_TEST(t_passing_tree_as_null);

  return UNITY_END();
}

