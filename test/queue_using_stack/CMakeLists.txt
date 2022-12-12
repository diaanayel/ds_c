add_library(stack ${PROJECT_SOURCE_DIR}/src/stack/stack.c)
add_library(squeue ${PROJECT_SOURCE_DIR}/src/queue_using_stack/squeue.c)

target_link_libraries(squeue stack)

add_executable(t_squeue t_squeue.c)

target_link_libraries(t_squeue squeue unity)

add_test(t_squeue ${TEST_OUTPUT_PATH}/t_squeue)

