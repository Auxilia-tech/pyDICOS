
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
    IDcsServer/*.cc
    DcsServer/*.cc
    IReceiveCallback/*.cc
    IClientAuthenticationCallback/*.cc)

# Define the Python extension module
pybind11_add_module(pyDICOS 
                    ${SOURCE} 
                    pyDICOS.cc)

set_target_properties(pyDICOS PROPERTIES SUFFIX ".so")
install(TARGETS pyDICOS DESTINATION ${CMAKE_SOURCE_DIR}/python)

target_include_directories(pyDICOS PRIVATE $ENV{SDICOS_PATH}/include)
target_link_libraries(pyDICOS PRIVATE $ENV{SDICOS_PATH}/lib/libDICOS_64R.a)

target_compile_features(pyDICOS PRIVATE cxx_std_17)
