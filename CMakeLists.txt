cmake_minimum_required(VERSION 2.6)

project(TestyMcTestFace CXX)

add_library(
    TestyMcTestFace
    include/testy/testy.hpp
    src/testy.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_definitions(
    -Wall -Werror -Wextra -pedantic
)

enable_testing()
add_subdirectory(tests)
