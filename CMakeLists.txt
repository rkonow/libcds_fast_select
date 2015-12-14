cmake_minimum_required(VERSION 2.8)
project(bitfucikingselect)
set(CMAKE_CXX_FLAGS " -std=c++11 -O3 -msse4.2 -mpopcnt  ")

add_subdirectory(libcds/)
include_directories(libcds/src/utils/)
include_directories(libcds/src/static/sequence/)
include_directories(libcds/src/static/permutation/)
include_directories(libcds/src/static/bitsequence/)
include_directories(libcds/src/static/mapper/)
include_directories(libcds/src/static/coders/)
include_directories(./)


add_executable(testbitmap bitsequenceTest.cpp)
add_executable(testrangesum rangesumTest.cpp)

target_link_libraries (testbitmap LINK_PUBLIC cds )
target_link_libraries (testrangesum LINK_PUBLIC cds )