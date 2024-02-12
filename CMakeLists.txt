cmake_minimum_required(VERSION 3.12)
project(pyDICOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# cmake_policy(SET CMP0148 NEW)

find_package(pybind11 REQUIRED)

add_subdirectory(src)

