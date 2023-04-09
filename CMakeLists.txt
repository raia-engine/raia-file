cmake_minimum_required(VERSION 3.25)
project(raia_file C)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_C_STANDARD 11)

add_library(raia_file SHARED src/raia_file.c src/duktape/duktape.c)

set_target_properties(raia_file PROPERTIES PREFIX "")