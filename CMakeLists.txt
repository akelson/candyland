cmake_minimum_required(VERSION 3.2)
project(params)

project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark
  GIT_TAG main
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(googlebenchmark)

include(GoogleTest)
include(CTest)
enable_testing()

add_library(candy candy.cpp)
add_library(sim sim.cpp)

add_executable(sim_main sim_main.cpp sim)
target_link_libraries(sim_main candy)

add_executable(run_tests test.cpp)
target_link_libraries(run_tests candy GTest::gtest_main)
gtest_discover_tests(run_tests)

add_executable(run_benchmarks benchmark.cpp)
target_link_libraries(run_benchmarks candy sim benchmark::benchmark_main)