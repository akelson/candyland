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

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY git@github.com:google/benchmark.git
  GIT_TAG main
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(googlebenchmark)

add_library(candy candy.cpp)
add_library(sim sim.cpp)

add_executable(sim_main sim_main.cpp sim)
target_link_libraries(sim_main candy)

add_executable(test test.cpp)
target_link_libraries(test candy GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test)

add_executable(mybenchmark benchmark.cpp)
target_link_libraries(mybenchmark candy sim benchmark::benchmark_main)