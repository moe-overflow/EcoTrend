cmake_minimum_required(VERSION 3.8)

# Necessary before calling project(...)
include(${CMAKE_SOURCE_DIR}/cmake/vcpkg_toolchain.cmake)
set_vcpkg_toolchain()

set(TARGET_NAME "EcoTrendReporter")

project(${TARGET_NAME} CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(TEMPLATE_PATH "${CMAKE_SOURCE_DIR}/resources/report_templates")
add_definitions(-DTEMPLATE_PATH="${TEMPLATE_PATH}")

set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/resources/assets")
add_definitions(-DASSETS_PATH="${ASSETS_PATH}")


add_subdirectory(src)

