cmake_minimum_required(VERSION 3.1)

project(m4s)

set(CMAKE_MODULE_PATH
    $ENV{CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/devbase/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/environment/cmake
)
include(m4s)

add_subdirectory(documentation)
add_subdirectory(source)
