cmake_minimum_required(VERSION 3.22)

project(A_star_v2)

add_executable(a_star_v2 src/a_star_v2.cpp)

include_directories(include)

file(GLOB_RECURSE HEADER_FILES "include/*.h")
add_custom_target(include SOURCES ${HEADER_FILES})
