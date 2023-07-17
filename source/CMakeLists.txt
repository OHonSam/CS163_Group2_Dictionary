cmake_minimum_required(VERSION 3.10)
project(Dictionary)

add_library(Lib INTERFACE)
target_include_directories(Lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets COPYONLY)

add_subdirectory(App)
add_subdirectory(json)

add_subdirectory(DataStructure)
add_subdirectory(Dict)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Dict)
