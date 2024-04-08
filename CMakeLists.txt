cmake_minimum_required(VERSION 3.20.0)
project(serial_port)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(
    ${PROJECT_SOURCE_DIR}/src 
    serial_SRCS)

add_library(
    serial SHARED 
    ${serial_SRCS})

target_include_directories(
    serial PUBLIC 
    ${PROJECT_SOURCE_DIR}/include)

add_executable(serial_port example.cpp)

target_include_directories(
    serial_port PUBLIC 
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    serial_port 
    PUBLIC 
    serial)