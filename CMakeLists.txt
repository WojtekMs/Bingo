cmake_minimum_required(VERSION 3.16)

project(bingo-generator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W3 /WX $<$<CONFIG:Release>:/O2>)
else()
  add_compile_options(-Wall -pedantic -Werror -Wextra -O3)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(clang-tidy)

option(ENABLE_CLANG_TIDY "This variable enables 'tidy' target" OFF)
if(ENABLE_CLANG_TIDY)
  set(CLANG_TIDY_VERSION
      12
      CACHE STRING "This variable defines clang tidy version to be used")
  add_tidy_target(${CLANG_TIDY_VERSION} FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
endif()

add_subdirectory(external)
add_subdirectory(src)

option(ENABLE_TESTS "This variable enables unit testing" OFF)
if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
