#include "unity_internals.h"
#include <unity.h>
#include <bst.h>

// visualization of steps canbe checkes using printfs in any function
// memory tests should be done !
int err;
Bst tree;

void setUp (void) {
  err = 0;
  tree = bst_init();
}

void tearDown (void) {
  bst_free(tree, &err);
}

void
t_test_environment()
{
  TEST_ASSERT_EQUAL(1, 1);
}

void
t_insert_to_empty()
{
  bst_insert(tree, 10, &err);
  TEST_ASSERT_EQUAL(0, err);
}

void
t_size()
{
  bst_insert(tree, 10, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, bst_size(tree));
}

void
t_get_root_node()
{
  TNode root;

  bst_insert(tree, 10, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(1, bst_size(tree));

  root = bst_get_root(tree, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_NOT_EQUAL(NULL, root);
}

void
t_get_node_data()
{
  TNode root;
  int root_data;

  bst_insert(tree, 10, &err);

  root = bst_get_root(tree, &err);

  bst_get_node_data(root, &root_data, &err);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(10, root_data);
}

void // can be confirmed with visualize_node method !
t_insert_one_bigger_data_should_be_to_rt()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, bst_size(tree));
}

void // can be confirmed with visualize_node method !
t_insert_one_smaller_data_should_be_to_lt()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 5, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, bst_size(tree));
}

void // can be confirmed with visualize_node method !
t_insert_two_nodes_on_root_should_be_on_both_sides()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 5, &err);
  bst_insert(tree, 20, &err);

  TEST_ASSERT_EQUAL(0, err);
}

void // can be confirmed with visualize_node method !
t_insert_multiple_nodes()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 9, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(7, bst_size(tree));
}

void
t_search_empty_tree()
{
  TEST_ASSERT_EQUAL(false, bst_search(tree, 10, &err));
  TEST_ASSERT_EQUAL(BST_EMPTY, err);
}

void
t_search_for_non_existing_item_in_non_empty_tree()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 9, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);

  TEST_ASSERT_EQUAL(false, bst_search(tree, 100, &err));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_search_for_existing_item_in_non_empty_tree()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 9, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);

  TEST_ASSERT_EQUAL(true, bst_search(tree, 10, &err));
  TEST_ASSERT_EQUAL(true, bst_search(tree, 7, &err));
  TEST_ASSERT_EQUAL(true, bst_search(tree, 11, &err));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_from_empty_tree()
{
  TEST_ASSERT_EQUAL(false, bst_remove(tree, 10,&err));
  TEST_ASSERT_EQUAL(BST_EMPTY, err);
}

void
t_remove_one_node_tree()
{
  bst_insert(tree, 10, &err);

  TEST_ASSERT_EQUAL(true, bst_remove(tree, 10,&err));
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, bst_size(tree));

}

void
t_insert_after_removing_last_node()
{
  bst_insert(tree, 10, &err);
  
  TEST_ASSERT_EQUAL(true, bst_remove(tree, 10,&err));

  bst_insert(tree, 10, &err);
  bst_insert(tree, 30, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(2, bst_size(tree));
}

void
t_remove_leaf_node()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 9, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);

  TEST_ASSERT_EQUAL(true, bst_remove(tree, 7,&err));
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(6, bst_size(tree));

  TEST_ASSERT_EQUAL(false, bst_search(tree, 7, &err));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_node_with_one_child()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);

  TEST_ASSERT_EQUAL(true, bst_remove(tree, 8,&err));
  TEST_ASSERT_EQUAL(5, bst_size(tree));
  TEST_ASSERT_EQUAL(0, err);
}

void
t_remove_node_with_two_children()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 8, &err);
  bst_insert(tree, 7, &err);
  bst_insert(tree, 9, &err);
  bst_insert(tree, 12, &err);
  bst_insert(tree, 11, &err);
  bst_insert(tree, 14, &err);
  bst_insert(tree, 19, &err);
  bst_insert(tree, 15, &err);
  bst_insert(tree, 3, &err);
  bst_insert(tree, 100, &err);

  TEST_ASSERT_EQUAL(true, bst_remove(tree, 10,&err));
  TEST_ASSERT_EQUAL(0, err);

  TEST_ASSERT_EQUAL(false, bst_search(tree, 10, &err));
  TEST_ASSERT_EQUAL(0, err);
}


/*
void
t_clear()
{
  bst_insert(tree, 10, &err);
  bst_insert(tree, 20, &err);
  bst_insert(tree, 30, &err);

  bst_clear(tree, &err);

  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(0, tree->size);
}

void
t_passing_err_handler_as_null()
{
  int x;
  bst_insert(tree, 10, NULL);
  bst_clear(tree, NULL);
  bst_remove(tree, &x, NULL);
  bst_search(tree, &x, NULL);
}

void
t_passing_outputVar_as_null()
{
  bst_insert(tree, 10, NULL);
  bst_clear(tree, NULL);
  bst_remove(tree, NULL, NULL);
  bst_search(tree, NULL, NULL);
}

void
t_passing_bst_as_null()
{
  bst_insert(NULL, 10, NULL);
  bst_clear(NULL, NULL);
  bst_remove(NULL, NULL, NULL);
  bst_search(NULL, NULL, NULL);
}
*/

int main(void){
  UNITY_BEGIN();

  RUN_TEST(t_test_environment);
  RUN_TEST(t_insert_to_empty);
  RUN_TEST(t_insert_one_bigger_data_should_be_to_rt);
  RUN_TEST(t_insert_one_smaller_data_should_be_to_lt);
  RUN_TEST(t_size);
  RUN_TEST(t_get_root_node);
  RUN_TEST(t_get_node_data);
  RUN_TEST(t_insert_two_nodes_on_root_should_be_on_both_sides);
  RUN_TEST(t_insert_multiple_nodes);
  RUN_TEST(t_search_empty_tree);
  RUN_TEST(t_search_for_non_existing_item_in_non_empty_tree);
  RUN_TEST(t_search_for_existing_item_in_non_empty_tree);
  RUN_TEST(t_remove_from_empty_tree);
  RUN_TEST(t_remove_one_node_tree);
  RUN_TEST(t_insert_after_removing_last_node);
  RUN_TEST(t_remove_leaf_node);
  RUN_TEST(t_remove_node_with_one_child);
  RUN_TEST(t_remove_node_with_two_children);
  // RUN_TEST(t_remove_two_node_tree);
  // RUN_TEST(t_clear);
  // RUN_TEST(t_passing_err_handler_as_null);
  // RUN_TEST(t_passing_outputVar_as_null);
  // RUN_TEST(t_passing_bst_as_null);

  return UNITY_END();
}

