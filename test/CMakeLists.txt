cmake_minimum_required(VERSION 3.15)

project(TraceForCppTest LANGUAGES CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

message(Error ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE TraceForCpp)
