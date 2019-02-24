cmake_minimum_required(VERSION 2.6)

project(TestyMcTestFace CXX)

get_filename_component(
    this_dir
    ${CMAKE_CURRENT_LIST_FILE}
    PATH
)

set(
    TESTY_ENABLE_TESTS
    OFF
    CACHE BOOL "Enable tests for ${PROJECT_NAME}"
)

add_library(
    testy
    include/testy/testy.hpp
    src/testy.cpp
)

include_directories(${this_dir}/include)

add_definitions(
    -Wall -Werror -Wextra -pedantic
)

if(${TESTY_ENABLE_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

install(
    TARGETS testy
    EXPORT TestyExports
    ARCHIVE DESTINATION lib
)

install(
    FILES 
        ${this_dir}/cmake/TestyConfig.cmake
        ${this_dir}/cmake/TestyExports-Includes.cmake
    DESTINATION lib/Testy/cmake
)

install(
    DIRECTORY ${this_dir}/include/
    DESTINATION include
)

install(
    EXPORT TestyExports
    NAMESPACE Testy::
    FILE TestyExports.cmake
    DESTINATION lib/Testy/cmake
)
