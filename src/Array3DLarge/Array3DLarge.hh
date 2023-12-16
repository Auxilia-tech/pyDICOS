#ifndef EXPORT_ARRAY3DLARGE_FILE_H
#define EXPORT_ARRAY3DLARGE_FILE_H

#include "../headers.hh"
#include "SDICOS/Array3DLarge.h"

using namespace SDICOS;

template<typename T>
void export_Array3DLarge(py::module &m,  const std::string & typestr){

    std::string pyclass_array3d_large_name = std::string("Array3DLarge") + typestr;

    py::class_<Array3DLarge<T>>(m, pyclass_array3d_large_name.c_str(), py::buffer_protocol())
        .def(py::init<>())
        .def(py::init<const S_UINT32, 
                      const S_UINT32, 
                      const S_UINT32, 
                      const MemoryPolicy::VOLUME_MEMORY_POLICY>(), 
                       py::arg("nWidth"), 
                       py::arg("nHeight"), 
                       py::arg("nDepth"), 
                       py::arg("memoryPolicy"))

        .def(py::init<const Array3DLarge<T>&>())

        .def("__copy__", [](const Array3DLarge<T> &self) { return Array3DLarge<T>(self); })
        .def("__deepcopy__", [](const Array3DLarge<T> &self, py::dict) { return Array3DLarge<T>(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("SetMemoryPolicy", &Array3DLarge<T>::SetMemoryPolicy, py::arg("nMemPolicy")) 
        .def("OwnsSlices", &Array3DLarge<T>::OwnsSlices)
        .def("GetSlice",(Array2D<T>*(Array3DLarge<T>::*)(const S_UINT32))&Array3DLarge<T>::GetSlice, py::arg("nD"), py::return_value_policy::reference_internal)
        .def("AddSlice",(Array2D<T>*(Array3DLarge<T>::*)(const S_UINT32, const S_UINT32))&Array3DLarge<T>::AddSlice, py::arg("width"), py::arg("height"))
        .def("AddSlice",(Array2D<T>*(Array3DLarge<T>::*)(T*, const S_UINT32, const S_UINT32))&Array3DLarge<T>::AddSlice, py::arg("pSlice"), py::arg("width"), py::arg("height"))
        .def("AddSlice",(bool(Array3DLarge<T>::*)(Array2D<T>*, 
                                                  const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY, 
                                                  const T*))&Array3DLarge<T>::AddSlice, 
                                                  py::arg("pNewSlice"), 
                                                  py::arg("nFailurePolicy") = Array3DLargeBase::ADD_SLICE_FAILURE_POLICY::EARLY_OUT, 
                                                  py::arg("pfFillValue") = S_NULL)
        .def("__getitem__", (const Array2D<T>& (Array3DLarge<T>::*)(S_UINT32) const) &Array3DLarge<T>::operator[], py::arg("n"))
        .def("__getitem__", (Array2D<T>& (Array3DLarge<T>::*)(S_UINT32)) &Array3DLarge<T>::operator[], py::arg("n"))
        .def("Zero", &Array3DLarge<T>::Zero, py::arg("zero"))
        .def("GetWidth", &Array3DLarge<T>::GetWidth)
        .def("GetHeight", &Array3DLarge<T>::GetHeight)
        .def("GetDepth", &Array3DLarge<T>::GetDepth)
        .def_buffer([](Array3DLarge<T> &m) -> py::buffer_info {  
            return py::buffer_info(m.GetBuffer(), 
                                   sizeof(T), 
                                   py::format_descriptor<T>::format(), 
                                   3, 
                                   { m.GetDepth(), m.GetHeight(), m.GetWidth() },
                                   { sizeof(T) * m.GetWidth() * m.GetHeight(), sizeof(T) * m.GetWidth(), sizeof(T) }
            );
        });
}

#endif