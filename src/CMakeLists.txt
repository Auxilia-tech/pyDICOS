
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

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(MY_LIB_SUFFIX ".pyd")
    set(DICOS_LIB_PATH "$ENV{SDICOS_PATH}/lib/VS2022/DICOS_64R.lib")
    target_link_libraries(pyDICOS PRIVATE ws2_32) # Fix error LNK2001
else()
    set(MY_LIB_SUFFIX ".so")
    set(DICOS_LIB_PATH "$ENV{SDICOS_PATH}/lib/libDICOS_64R.a")
endif()


set_target_properties(pyDICOS PROPERTIES SUFFIX "${MY_LIB_SUFFIX}")

install(TARGETS pyDICOS DESTINATION ${CMAKE_SOURCE_DIR}/python)

target_include_directories(pyDICOS PRIVATE $ENV{SDICOS_PATH}/include)
target_link_libraries(pyDICOS PRIVATE "${DICOS_LIB_PATH}")

target_compile_features(pyDICOS PRIVATE cxx_std_17)
