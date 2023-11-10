cmake_minimum_required(VERSION 3.12)
project(pyDICOS)

# Use C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Find Python and pybind11
find_package(pybind11 REQUIRED)

add_subdirectory(src)

set_target_properties(pyDICOS PROPERTIES OUTPUT_NAME "pyDICOS")
