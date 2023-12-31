cmake_minimum_required(VERSION 3.14)
project(sort_bench)
enable_testing()

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0)

FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark
    )

add_executable(${PROJECT_NAME} benchmark.cpp QuickSort.cpp HeapSort.cpp)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
