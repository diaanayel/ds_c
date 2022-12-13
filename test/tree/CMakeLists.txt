add_library(tree ${PROJECT_SOURCE_DIR}/src/tree/tree.c)

add_executable(t_tree t_tree.c)

target_link_libraries(t_tree tree unity)

add_test(t_tree ${TEST_OUTPUT_PATH}/t_tree)

