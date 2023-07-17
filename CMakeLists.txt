cmake_minimum_required(VERSION 3.10)
project(Dictionary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)