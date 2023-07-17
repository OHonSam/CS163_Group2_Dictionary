cmake_minimum_required(VERSION 3.10)
project(Dictionary)

add_library(Lib INTERFACE)
target_include_directories(Lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB data ${CMAKE_CURRENT_SOURCE_DIR}/data/*)
file(COPY ${data} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

# add_subdirectory(App)
# add_subdirectory(json)

add_subdirectory(DataStructure)
add_subdirectory(Dict)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Dict)
