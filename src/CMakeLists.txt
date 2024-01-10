
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS 
    Array1D/*.hh
    Array2D/*.hh
    Point3D/*.hh
    MemManager/*.cc 
    ErrorLog/*.cc 
    DcsString/*.cc 
    FILESYSTEM/*.cc 
    CT/*.cc 
    Section/*.cc
    Vector3D/*.hh
    Volume/*.cc
    Array3DLarge/*.hh
    DX/*.cc
    TDR/*.cc
    Image2D/*.cc
    Bitmap/*.cc
    DcsGUID/*.cc
    SopClassUID/*.cc
    GeneralSeriesModule/*.cc
    DcsClient/*.cc
    IDcsServer/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

target_include_directories(pyDICOS PRIVATE "/home/ahau/Stratovan\ Corporation/SDICOS-64/include")
target_link_libraries(pyDICOS PRIVATE "/home/ahau/Stratovan\ Corporation/SDICOS-64/lib/libDICOS_64R.a")

target_compile_features(pyDICOS PRIVATE cxx_std_17)

set_target_properties(pyDICOS PROPERTIES OUTPUT_NAME "pyDICOS")