add_library(queue_with_stack ${PROJECT_SOURCE_DIR}/src/queue_with_stack/queue_with_stack.c)

add_executable(t_queue_with_stack t_queue_with_stack.c)

target_link_libraries(t_queue_with_stack queue_with_stack unity)

add_test(t_queue_with_stack ${TEST_OUTPUT_PATH}/t_queue_with_stack)

