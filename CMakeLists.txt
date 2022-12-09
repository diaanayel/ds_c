cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.0)

project(ds VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(${PROJECT_SOURCE_DIR}/src/includes)

if(TARGET_GROUP STREQUAL release)
  message( ">>> building for production !")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/release)
  add_subdirectory(${PROJECT_SOURCE_DIR}/src)
elseif(TARGET_GROUP STREQUAL test)
  message(">>> building for testing !")
  include(CTest)
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
else()
    message(FATAL_ERROR "unknown TARGET_GROUP (set using -DTARGET_GROUP=release/test)!")
endif()
