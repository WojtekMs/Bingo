add_executable(${PROJECT_NAME} main.cpp)
add_library(${PROJECT_NAME}-lib)
target_sources(
  ${PROJECT_NAME}-lib
  PRIVATE parser/JsonParser.cpp utils.cpp
  PUBLIC parser/JsonParser.hpp parser/IParser.hpp utils.hpp)

target_include_directories(${PROJECT_NAME}-lib
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}-lib PUBLIC json fmt::fmt range-v3::range-v3 sfml-graphics sfml-window sfml-system GL)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)
