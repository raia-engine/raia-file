cmake_minimum_required(VERSION 3.25)
project(raia_file C)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_C_STANDARD 11)

add_library(raia_file SHARED
        src/raia_file.c
        src/duktape/duktape.c
        src/util/util_file.c
        src/util/util_file.h
        src/parson/parson.c src/wrapper/wrapper_parson.c src/wrapper/wrapper_parson.h)

target_link_libraries(raia_file m)

set_target_properties(raia_file PROPERTIES PREFIX "")