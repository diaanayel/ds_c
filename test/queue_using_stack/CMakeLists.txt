add_library(stack ${PROJECT_SOURCE_DIR}/src/stack/stack.c)
add_library(amqueue ${PROJECT_SOURCE_DIR}/src/queue_using_stack/amqueue.c)

target_link_libraries(amqueue stack)

add_executable(t_amqueue t_amqueue.c)

target_link_libraries(t_amqueue amqueue unity)

add_test(t_amqueue ${TEST_OUTPUT_PATH}/t_amqueue)

