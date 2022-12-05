cmake_minimum_required(VERSION 3.0.0)
project(Expect VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(Include)

add_library(Expect
  Source/Expect.cpp
)

add_library(AutoExpect
  Source/Driver/main.cpp
)
target_link_libraries(AutoExpect Expect)

add_executable(TestsGeneral Tests/General/main.cpp)
target_link_libraries(TestsGeneral AutoExpect)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
