cmake_minimum_required(VERSION 3.10)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# add data structures
set(DS_LIST HashTable Trie SLL)

foreach(DS ${DS_LIST})
  set(TEST_NAME ${DS}_test)
  add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
  target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest ${DS})
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()