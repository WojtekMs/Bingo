add_library(json INTERFACE)
target_sources(json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann/json.hpp)
target_include_directories(json SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
    fmt 
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9 # release 8.1.1
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    ranges
    GIT_REPOSITORY https://github.com/ericniebler/range-v3
    GIT_TAG d800a032132512a54c291ce55a2a43e0460591c7 # commit from Feb 19 2022
)
FetchContent_MakeAvailable(ranges)

find_package(
  SFML 2.5.1
  COMPONENTS graphics window system
  REQUIRED)
