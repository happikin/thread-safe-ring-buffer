cmake_minimum_required(VERSION 3.10)
project(thread-safe-buffer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(ring_buffer_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_link_libraries(ring_buffer_test pthread)