add_library(queue ${PROJECT_SOURCE_DIR}/src/queue/queue.c)
add_executable(t_queue t_queue.c)

target_link_libraries(t_queue queue unity)

add_test(t_queue ${TEST_OUTPUT_PATH}/t_queue)

