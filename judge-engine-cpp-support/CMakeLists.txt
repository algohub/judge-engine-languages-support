cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME_STR judge-engine-cpp-support)
project(${PROJECT_NAME_STR})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
target_link_libraries(${PROJECT_TEST_NAME} gtest gtest_main)

add_test(test1 ${PROJECT_TEST_NAME})
