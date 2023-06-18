include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(
  ${PROJECT_NAME}-ut
  ${CMAKE_CURRENT_SOURCE_DIR}/JsonParserTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bingo/BingoTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bingo/BoardTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_utils.cpp)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gtest_main)
target_include_directories(${PROJECT_NAME}-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
