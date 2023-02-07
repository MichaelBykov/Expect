cmake_minimum_required(VERSION 3.0.0)
project(Expect VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)



add_library(Expect Source/Expect.cpp)
target_include_directories(Expect PUBLIC Include)

add_library(AutoExpect Source/AutoExpect.cpp)
target_include_directories(AutoExpect PUBLIC Include)



add_executable(TestsGeneral Tests/General/main.cpp Tests/General/benchmarks.cpp)
target_link_libraries(TestsGeneral AutoExpect)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
