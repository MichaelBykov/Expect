cmake_minimum_required(VERSION 3.0.0)
project(Expect VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include(CTest)
enable_testing()

include_directories(Include)

add_library(Expect
  Source/Expect.cpp
  Source/Global/toString.cpp
  Source/Test/Test.cpp
  Source/Suite/Suite.cpp
  Source/Expression/ExactExpression.cpp
  Source/Expression/MiscExpression.cpp
  Source/Evaluate/Evaluate.cpp
  Source/Evaluate/Section.cpp
  Source/Matching/Matchers.cpp
  Source/Driver/TestState.cpp
  Source/Driver/Driver.cpp
  Source/Driver/CommandLineDriver.cpp
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
