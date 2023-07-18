cmake_minimum_required(VERSION 3.10)
project(Dictionary)

set(OSBit 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBit 64)
endif()

set(AllOutDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBit}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${AllOutDir}/StaticLibs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${AllOutDir}/SharedLibs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AllOutDir})

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${AllOutDir})

add_library(Lib INTERFACE)
target_include_directories(Lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory(json)

add_subdirectory(DataStructure)
add_subdirectory(Dict)
add_subdirectory(App)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} App)
