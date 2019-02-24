get_filename_component(testy_project_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
get_filename_component(testy_project_dir ${testy_project_dir} PATH)

message(STATUS "Testy project direcotyr: ${testy_project_dir}")

set(testy_build_dir "${CMAKE_CURRENT_BINARY_DIR}/testy-build")
set(testy_working_dir "${CMAKE_CURRENT_BINARY_DIR}/third-party-deps")
message(STATUS "Building Testy in: ${testy_build_dir}")
message(STATUS "Installing Testy to: ${testy_working_dir}")

file(MAKE_DIRECTORY "${testy_working_dir}")
file(MAKE_DIRECTORY "${testy_build_dir}")
#file(REMOVE_RECURSE "${testy_project_dir}/build")
#file(MAKE_DIRECTORY "${testy_project_dir}/build")

execute_process(
    COMMAND "${CMAKE_COMMAND}" 
        -DTESTY_ENABLE_TESTS=0 
        -DCMAKE_INSTALL_PREFIX=${testy_working_dir}
        ${testy_project_dir}
    WORKING_DIRECTORY "${testy_build_dir}"
    ERROR_VARIABLE testy_cmake_error
)

message(STATUS "cmake result: ${testy_cmake_error}")

execute_process(
    COMMAND "${CMAKE_MAKE_PROGRAM}"
    WORKING_DIRECTORY "${testy_build_dir}"
    ERROR_VARIABLE testy_cmake_error
)

message(STATUS "make result: ${testy_cmake_error}")

execute_process(
    COMMAND "${CMAKE_MAKE_PROGRAM}" install
    WORKING_DIRECTORY "${testy_build_dir}"
    ERROR_VARIABLE testy_cmake_error
)

message(STATUS "make install result: ${testy_cmake_error}")

list(APPEND CMAKE_PREFIX_PATH ${testy_working_dir})

find_package(Testy REQUIRED)
