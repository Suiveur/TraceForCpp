cmake_minimum_required(VERSION 3.15)

project(TraceForCpp LANGUAGES CXX)

# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 搜索 src 目录下的所有源文件
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 创建静态库
add_library(TraceForCpp STATIC ${SRC_LIST})

target_compile_features(TraceForCpp PUBLIC cxx_std_17)
