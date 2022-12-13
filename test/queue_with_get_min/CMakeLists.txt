add_library(queue ${PROJECT_SOURCE_DIR}/src/queue/queue.c)
add_library(gmqueue ${PROJECT_SOURCE_DIR}/src/queue_with_get_min/gmqueue.c)

target_link_libraries(gmqueue queue)

add_executable(t_gmqueue t_gmqueue.c)

target_link_libraries(t_gmqueue gmqueue unity)

add_test(t_gmqueue ${TEST_OUTPUT_PATH}/t_gmqueue)

