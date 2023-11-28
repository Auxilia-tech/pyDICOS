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
                                           py::arg("nDataType"),  py::arg("nWidth"),  py::arg("nHeight"),  py::arg("nDepth"));
  
}