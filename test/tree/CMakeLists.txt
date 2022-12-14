add_library(bst ${PROJECT_SOURCE_DIR}/src/tree/bst.c)

add_executable(t_bst t_bst.c)

target_link_libraries(t_bst bst unity)

add_test(t_bst ${TEST_OUTPUT_PATH}/t_bst)

