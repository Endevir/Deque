cmake_minimum_required(VERSION 3.6)
project(Deque)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -O3")
add_subdirectory(gtest)
include_directories(gtest/googletest/include)
include_directories(gtest/googlemock/include)

set(SOURCE_FILES main.cpp deque.h deque_iterator.h test.cpp)
add_executable(Deque ${SOURCE_FILES})
target_link_libraries(Deque gtest gtest_main)