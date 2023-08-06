cmake_minimum_required(VERSION 3.10)
project(Dictionary)

set(OSBit 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBit 64)
endif()

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
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

target_link_libraries(${PROJECT_NAME} App raylib)
