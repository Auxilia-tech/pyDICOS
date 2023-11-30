#include "../headers.hh"
#include "SDICOS/Volume.h"
 
using namespace SDICOS;



void export_Volume(py::module &m)
{
    py::class_<Volume::SliceIterator>(m, "SliceIterator")
        .def(py::init<>())
        .def(py::init<const Volume&>(), py::arg("vol"))
        .def("__copy__", [](const Volume::SliceIterator &self) { return Volume::SliceIterator(self); })
        .def("__deepcopy__", [](const Volume::SliceIterator &self, py::dict) { return Volume::SliceIterator(self); })
        .def("InitBegin", &Volume::SliceIterator::InitBegin,  py::arg("vol"))
        .def("GetVolumeDataType", &Volume::SliceIterator::GetVolumeDataType)
        .def("GetCurrentSlice", &Volume::SliceIterator::GetCurrentSlice)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self += S_INT32())
        .def(py::self -= S_INT32());
    
    py::enum_<ImageDataBase::IMAGE_DATA_TYPE>(m, "IMAGE_DATA_TYPE")
        .value("enumUndefinedDataType", ImageDataBase::IMAGE_DATA_TYPE::enumUndefinedDataType)
        .value("enumSigned8Bit", ImageDataBase::IMAGE_DATA_TYPE::enumSigned8Bit)
        .value("enumUnsigned8Bit",ImageDataBase::IMAGE_DATA_TYPE::enumUnsigned8Bit)
        .value("enumSigned16Bit", ImageDataBase::IMAGE_DATA_TYPE::enumSigned16Bit)
        .value("enumUnsigned16Bit", ImageDataBase::IMAGE_DATA_TYPE::enumUnsigned16Bit)
        .value("enumSigned32Bit", ImageDataBase::IMAGE_DATA_TYPE::enumSigned32Bit)
        .value("enumUnsigned32Bit", ImageDataBase::IMAGE_DATA_TYPE::enumUnsigned32Bit)
        .value("enumSigned64Bit", ImageDataBase::IMAGE_DATA_TYPE::enumSigned64Bit)
        .value("enumUnsigned64Bit", ImageDataBase::IMAGE_DATA_TYPE::enumUnsigned64Bit)
        .value("enumFloat", ImageDataBase::IMAGE_DATA_TYPE::enumFloat)
        .export_values();

    py::class_<ImageDataBase>(m, "ImageDataBase");
    py::class_<Volume, ImageDataBase>(m, "Volume")
        .def_property_readonly_static("VOLUME_MEMORY_POLICY", [m](py::object) {
            return m.attr("VOLUME_MEMORY_POLICY");
        })  
        .def_property_readonly_static("IMAGE_DATA_TYPE", [m](py::object) {
            return m.attr("IMAGE_DATA_TYPE");
        })  
        .def(py::init<>())
        .def(py::init<const ImageDataBase::IMAGE_DATA_TYPE, const MemoryPolicy::VOLUME_MEMORY_POLICY>(),
                      py::arg("nDataType") = ImageDataBase::IMAGE_DATA_TYPE::enumUndefinedDataType, 
                      py::arg("nMemoryPolicy") = MemoryPolicy::OWNS_SLICES)
        .def("__copy__", [](const Volume &self) { return Volume(self); })
        .def("__deepcopy__", [](const Volume &self, py::dict) { return Volume(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Allocate", py::overload_cast<const ImageDataBase::IMAGE_DATA_TYPE>(&Volume::Allocate),  py::arg("nDataType"))
        .def("Allocate", py::overload_cast<const ImageDataBase::IMAGE_DATA_TYPE, S_UINT32, const S_UINT32, const S_UINT32>(&Volume::Allocate),  
                                           py::arg("nDataType"),  py::arg("nWidth"),  py::arg("nHeight"),  py::arg("nDepth"))
        .def("GetSigned8", (Array3DLarge<S_INT8>* (Volume::*)()) &Volume::GetSigned8)
        .def("GetSigned16", (Array3DLarge<S_INT16>* (Volume::*)()) &Volume::GetSigned16)
        .def("GetSigned32", (Array3DLarge<S_INT32>* (Volume::*)()) &Volume::GetSigned32)     
        .def("GetSigned64", (Array3DLarge<S_INT64>* (Volume::*)()) &Volume::GetSigned64)
        .def("GetUnSigned8", (Array3DLarge<S_UINT8>* (Volume::*)()) &Volume::GetUnsigned8)
        .def("GetUnSigned16", (Array3DLarge<S_UINT16>* (Volume::*)()) &Volume::GetUnsigned16)     
        .def("GetUnSigned32", (Array3DLarge<S_UINT32>* (Volume::*)()) &Volume::GetUnsigned32)
        .def("GetUnSigned64", (Array3DLarge<S_UINT64>* (Volume::*)()) &Volume::GetUnsigned64)
        .def("GetFloat", (Array3DLarge<float>* (Volume::*)()) &Volume::GetFloat)
        .def("GetSigned8", (const Array3DLarge<S_INT8>* (Volume::*)() const) &Volume::GetSigned8)
        .def("GetSigned16", (const Array3DLarge<S_INT16>* (Volume::*)() const) &Volume::GetSigned16)
        .def("GetSigned32", (const Array3DLarge<S_INT32>* (Volume::*)() const) &Volume::GetSigned32)     
        .def("GetSigned64", (const Array3DLarge<S_INT64>* (Volume::*)() const) &Volume::GetSigned64)
        .def("GetUnsigned8", (const Array3DLarge<S_UINT8>* (Volume::*)() const) &Volume::GetUnsigned8)
        .def("GetUnsigned16", (const Array3DLarge<S_UINT16>* (Volume::*)() const) &Volume::GetUnsigned16)     
        .def("GetUnsigned32", (const Array3DLarge<S_UINT32>* (Volume::*)() const) &Volume::GetUnsigned32)
        .def("GetUnsigned64", (const Array3DLarge<S_UINT64>* (Volume::*)() const) &Volume::GetUnsigned64)
        .def("GetWidth", &Volume::GetWidth) 
        .def("GetHeight", &Volume::GetHeight) 
        .def("GetDepth", &Volume::GetDepth)
        .def("GetSliceSize", &Volume::GetSliceSize)
        .def("GetSliceSizeInBytes", &Volume::GetSliceSizeInBytes)
        .def("GetSizeInBytes", &Volume::GetSizeInBytes)
        .def("GetDepth", &Volume::GetDepth)
        .def("GetCapacity", &Volume::GetCapacity);
}