cmake_minimum_required(VERSION 3.12)
project(pyDICOS)

set(CMAKE_CXX_STANDARD 14)

# Find Python and pybind11
find_package(pybind11 REQUIRED)

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS src/CT/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS ${SOURCE} pyDICOS.cc)

target_link_libraries(pyDICOS PRIVATE /opt/stratovan/sdicos/lib/libDICOS_64R.a)

# Include directories containing the C++ library's header files
target_include_directories(pyDICOS PRIVATE /opt/stratovan/sdicos/include)

# Set the module name
set_target_properties(pyDICOS PROPERTIES OUTPUT_NAME "pyDICOS")

# Optionally, specify the C++ standard explicitly (required for some compilers)
target_compile_features(pyDICOS PRIVATE cxx_std_14)