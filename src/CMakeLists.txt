
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS CT/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

# Include directories containing the C++ library's header files
target_include_directories(pyDICOS PRIVATE /opt/stratovan/sdicos/include)


target_link_libraries(pyDICOS PRIVATE /opt/stratovan/sdicos/lib/libDICOS_64R.a)

# Optionally, specify the C++ standard explicitly (required for some compilers)
target_compile_features(pyDICOS PRIVATE cxx_std_14)
