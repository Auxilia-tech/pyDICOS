#ifndef EXPORT_IMAGE2D_FILE_H
#define EXPORT_IMAGE2D_FILE_H


#include "../headers.hh"
#include "SDICOS/Image2D.h"

using namespace SDICOS;

void export_Image2D(py::module &m)
{
    py::class_<Image2D, ImageDataBase>(m, "Image2D", py::buffer_protocol(), py::dynamic_attr())
        .def(py::init<const ImageDataBase::IMAGE_DATA_TYPE, 
                      const MemoryPolicy::VOLUME_MEMORY_POLICY>(), 
                       py::arg("nDataType") = ImageDataBase::IMAGE_DATA_TYPE::enumUndefinedDataType, 
                       py::arg("nMemoryPolicy") = MemoryPolicy::OWNS_DATA)
        .def(py::init<const Image2D&>())
        .def("__copy__", [](const Image2D &self) { return Image2D(self); })
        .def("__deepcopy__", [](const Image2D &self, py::dict) { return Image2D(self); })
        .def("__assign__", (Image2D& (Image2D::*)(const Image2D &)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_INT8>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_UINT8>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_INT16>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_UINT16>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_INT32>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_UINT32>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_INT64>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<S_UINT64>&)) &Image2D::operator=)
        .def("__assign__", (Image2D& (Image2D::*)(const Array2D<float>&)) &Image2D::operator=)
        .def("__eq__", (bool (Image2D::*)(const Image2D &) const) &Image2D::operator==)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_INT8> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Image2D &) const) &Image2D::operator!=)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_INT8> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_UINT8> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_UINT8> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_INT16> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_INT16> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_UINT16> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_UINT16> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_INT32> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_INT32> &) const) &Image2D::operator!=)       
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_UINT32> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_UINT32> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_INT64> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_INT64> &) const) &Image2D::operator!=)
        .def("__eq__", (bool (Image2D::*)(const Array2D<S_UINT64> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<S_UINT64> &) const) &Image2D::operator!=)             
        .def("__eq__", (bool (Image2D::*)(const Array2D<float> &) const) &Image2D::operator==)
        .def("__ne__", (bool (Image2D::*)(const Array2D<float> &) const) &Image2D::operator!=)   
        .def("GetBitsPerPixel", &Image2D::GetBitsPerPixel) 
        .def("GetBitsStoredPerPixel", &Image2D::GetBitsStoredPerPixel)  
        .def("GetHighBit", &Image2D::GetHighBit) 
        .def("GetWidth", &Image2D::GetWidth) 
        .def("GetHeight", &Image2D::GetHeight) 
        .def("GetSize", &Image2D::GetSize) 
        .def("FreeMemory", &Image2D::FreeMemory) 
        .def("SetMemoryPolicy", &Image2D::SetMemoryPolicy, py::arg("nMemoryPolicy"))   
        .def("GetMemoryPolicy", &Image2D::GetMemoryPolicy)
        .def("SetMemoryManager", &Image2D::SetMemoryManager, py::arg("pMemManager"))    
        .def("GetMemoryManager", &Image2D::GetMemoryManager)    
        .def("Allocate", py::overload_cast<const ImageDataBase::IMAGE_DATA_TYPE>(&Image2D::Allocate),  py::arg("nDataType"))
        .def("Allocate", py::overload_cast<const ImageDataBase::IMAGE_DATA_TYPE, S_UINT32, const S_UINT32>(&Image2D::Allocate),  
                                           py::arg("nDataType"),  py::arg("nWidth"),  py::arg("nHeight"))
        .def("SetSize", &Image2D::SetSize, py::arg("nWidth"), py::arg("nHeight"))    
        .def("ApplyRescale", &Image2D::ApplyRescale, py::arg("fSlope"), py::arg("fIntercept"))    
        .def("GetImageDataType", &Image2D::GetImageDataType)    
        .def("Set", &Image2D::Set, py::arg("ipm"), py::arg("bMoveData"))    
        .def("Move", &Image2D::Move, py::arg("imgSrc"))  
        .def("GetSigned8", (Array2D<S_INT8>* (Image2D::*)()) &Image2D::GetSigned8, py::return_value_policy::reference_internal)
        .def("GetSigned16", (Array2D<S_INT16>* (Image2D::*)()) &Image2D::GetSigned16, py::return_value_policy::reference_internal)
        .def("GetSigned32", (Array2D<S_INT32>* (Image2D::*)()) &Image2D::GetSigned32, py::return_value_policy::reference_internal)     
        .def("GetSigned64", (Array2D<S_INT64>* (Image2D::*)()) &Image2D::GetSigned64, py::return_value_policy::reference_internal)
        .def("GetUnSigned8", (Array2D<S_UINT8>* (Image2D::*)()) &Image2D::GetUnsigned8, py::return_value_policy::reference_internal)
        .def("GetUnSigned16", (Array2D<S_UINT16>* (Image2D::*)()) &Image2D::GetUnsigned16, py::return_value_policy::reference_internal)     
        .def("GetUnSigned32", (Array2D<S_UINT32>* (Image2D::*)()) &Image2D::GetUnsigned32, py::return_value_policy::reference_internal)
        .def("GetUnSigned64", (Array2D<S_UINT64>* (Image2D::*)()) &Image2D::GetUnsigned64, py::return_value_policy::reference_internal)
        .def("GetFloat", (Array2D<float>* (Image2D::*)()) &Image2D::GetFloat, py::return_value_policy::reference_internal)
        .def("GetSigned8", (const Array2D<S_INT8>* (Image2D::*)() const) &Image2D::GetSigned8, py::return_value_policy::reference_internal)
        .def("GetSigned16", (const Array2D<S_INT16>* (Image2D::*)() const) &Image2D::GetSigned16, py::return_value_policy::reference_internal)
        .def("GetSigned32", (const Array2D<S_INT32>* (Image2D::*)() const) &Image2D::GetSigned32, py::return_value_policy::reference_internal)     
        .def("GetSigned64", (const Array2D<S_INT64>* (Image2D::*)() const) &Image2D::GetSigned64, py::return_value_policy::reference_internal)
        .def("GetUnsigned8", (const Array2D<S_UINT8>* (Image2D::*)() const) &Image2D::GetUnsigned8, py::return_value_policy::reference_internal)
        .def("GetUnsigned16", (const Array2D<S_UINT16>* (Image2D::*)() const) &Image2D::GetUnsigned16, py::return_value_policy::reference_internal)     
        .def("GetUnsigned32", (const Array2D<S_UINT32>* (Image2D::*)() const) &Image2D::GetUnsigned32, py::return_value_policy::reference_internal)
        .def("GetUnsigned64", (const Array2D<S_UINT64>* (Image2D::*)() const) &Image2D::GetUnsigned64, py::return_value_policy::reference_internal)
        .def("GetAsBuffer", &Image2D::GetAsBuffer, py::arg("mbImage"));
}

#endif