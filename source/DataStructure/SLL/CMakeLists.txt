cmake_minimum_required(VERSION 3.10)
project(SLL)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.inl)

target_link_libraries(${PROJECT_NAME} INTERFACE Lib Word)