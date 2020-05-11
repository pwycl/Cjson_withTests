cmake_minimum_required(VERSION 3.10)
project(Cjson_withTests)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

#add_compile_options(-fprofile-arcs -ftest-coverage -fPIC -O0)
#add_link_options(-fprofile-arcs -ftest-coverage -fPIC -O0)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

add_executable(Cjson_withTests ${SOURCE_FILES})
#add_compile_options(--coverage)
#add_link_options(--coverage)
include_directories(Cjson_lib)
add_subdirectory(Cjson_lib)

target_link_libraries(Cjson_withTests Cjson_lib)

add_subdirectory(Google_tests)