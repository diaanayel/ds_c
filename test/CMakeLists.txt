set(UNITY_PATH /data/data/com.termux/files/home/sysTools/tools/Unity)
set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)

include_directories(${UNITY_PATH}/src)

add_library(unity STATIC ${UNITY_PATH}/src/unity.c)
target_include_directories(unity PUBLIC ${UNITY_PATH}/src)

#add_subdirectory(sl_list)
#add_subdirectory(stack)
#add_subdirectory(queue)

#add_subdirectory(queue_using_stack)
#add_subdirectory(queue_with_get_min)


add_subdirectory(tree)
