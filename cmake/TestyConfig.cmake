get_filename_component(
    testy_conf_dir
    ${CMAKE_CURRENT_LIST_FILE}
    PATH
)
include("${testy_conf_dir}/TestyExports.cmake")
