add_library(stack ${PROJECT_SOURCE_DIR}/src/stack/stack.c)
add_library(fsqueue ${PROJECT_SOURCE_DIR}/src/queue_using_stack/fsqueue.c)

target_link_libraries(fsqueue stack)

add_executable(t_fsqueue t_fsqueue.c)

target_link_libraries(t_fsqueue fsqueue unity)

add_test(t_fsqueue ${TEST_OUTPUT_PATH}/t_fsqueue)

