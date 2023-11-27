
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS 
    Array1D/*.cc
    MemManager/*.cc 
    ErrorLog/*.cc 
    DcsString/*.cc 
    FILESYSTEM/*.cc 
    CT/*.cc 
    Section/*.cc
    Vector3D/*.hh
    Volume/*.cc)#DX/*.cc TDR/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

target_include_directories(pyDICOS PRIVATE /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/include)
target_link_libraries(pyDICOS PRIVATE /home/ahau/freelance/Louis/pyDICOS/pyDICOS/stratovan/sdicos/lib/libDICOS_64R.a)

target_compile_features(pyDICOS PRIVATE cxx_std_17)

set_target_properties(pyDICOS PROPERTIES OUTPUT_NAME "pyDICOS")