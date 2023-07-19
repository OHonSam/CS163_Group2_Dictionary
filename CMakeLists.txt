cmake_minimum_required(VERSION 3.10)
project(Dictionary)

if(MSVC)
    add_compile_options(/stdc++latest)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(BUILD_SHARED_LIBS ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)