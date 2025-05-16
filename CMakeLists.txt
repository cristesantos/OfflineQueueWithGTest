cmake_minimum_required(VERSION 3.14)
project(OfflineQueueWithGTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Adicionar GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main main.cpp src/Queue.cpp)
add_executable(QueueTest tests/QueueTest.cpp src/Queue.cpp)

target_link_libraries(QueueTest gtest_main)
include(GoogleTest)
gtest_discover_tests(QueueTest)