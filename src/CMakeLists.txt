
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS CT/*.cc DX/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

# Include directories containing the C++ library's header files
target_include_directories(pyDICOS PRIVATE /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/include)


add_library(DICOS_64R STATIC IMPORTED)
set_target_properties(DICOS_64R PROPERTIES IMPORTED_LOCATION /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/lib/libDICOS_64R.a)
target_link_libraries(pyDICOS PRIVATE DICOS_64R)

# Optionally, specify the C++ standard explicitly (required for some compilers)
target_compile_features(pyDICOS PRIVATE cxx_std_17)
