add_library(stack ${PROJECT_SOURCE_DIR}/src/stack/stack.c)
add_executable(t_stack t_stack.c)

target_link_libraries(t_stack stack unity)

add_test(t_stack ${TEST_OUTPUT_PATH}/t_stack)

