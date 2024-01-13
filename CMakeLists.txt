cmake_minimum_required(VERSION 3.10)

project(FA
  LANGUAGES CXX C
)

find_package(Threads)


add_executable(tests
  dArray.c
  tests.cc
  googletest/googletest/src/gtest-all.cc
)

target_include_directories(tests
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_link_libraries(tests
  PRIVATE
    Threads::Threads
)

target_compile_options(tests
  PRIVATE
    "-Wall" "-Wextra" "-pedantic" "-g" "-O2"
)

set_target_properties(tests
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
