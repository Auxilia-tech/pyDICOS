
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS CT/*.cc) #DX/*.cc TDR/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

# Include directories containing the C++ library's header files
target_include_directories(pyDICOS PRIVATE /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/include)

target_link_libraries(pyDICOS PRIVATE /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/lib/libDICOS_64R.a)

# Optionally, specify the C++ standard explicitly (required for some compilers)
target_compile_features(pyDICOS PRIVATE cxx_std_17)

set_target_properties(pyDICOS PROPERTIES OUTPUT_NAME "pyDICOS")