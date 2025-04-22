cmake_minimum_required(VERSION 3.15)

project(shared_ptr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(shared_ptr unit_tests.cpp)

target_include_directories(shared_ptr PRIVATE ../SharedPtr)
target_link_libraries(shared_ptr PRIVATE GTest::gtest_main)
target_compile_options(shared_ptr PRIVATE -Wall -Wextra -Werror)

include(GoogleTest)
gtest_discover_tests(shared_ptr)