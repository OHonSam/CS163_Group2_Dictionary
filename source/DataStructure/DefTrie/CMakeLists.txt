cmake_minimum_required(VERSION 3.10)
project(DefTrie)

add_subdirectory(SmallTrie)

add_library(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Lib Word SmallTrie HashTable)