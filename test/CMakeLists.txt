set(UNITY_PATH path/to/unity/test/framework)
set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)

include_directories(${UNITY_PATH}/src)

add_library(unity STATIC ${UNITY_PATH}/src/unity.c)
target_include_directories(unity PUBLIC ${UNITY_PATH}/src)

add_library(sl_list ${PROJECT_SOURCE_DIR}/src/sl_list/sl_list.c)
add_executable(t_sl_list sl_list/t_sl_list.c)

target_link_libraries(t_sl_list sl_list unity)

add_test(t_sl_list ${TEST_OUTPUT_PATH}/t_sl_list)

