#ifndef EXPORT_ARRAY1D_FILE_H
#define EXPORT_ARRAY1D_FILE_H

#include "../headers.hh"
#include "SDICOS/Array1D.h"

using namespace SDICOS;

template<typename T>
void export_Array1D(py::module &m, const std::string & typestr){
    std::string pyclass_array1D_name = std::string("Array1D") + typestr;
    py::class_<Array1D<T>>(m, pyclass_array1D_name.c_str(), py::buffer_protocol())
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("size"))
        .def(py::init<const Array1D<T>&>())
        .def("Empty", &Array1D<T>::Empty)
        .def("Clear", &Array1D<T>::Clear)
        .def("SetSize", &Array1D<T>::SetSize, py::arg("nSize"), py::arg("bAllocateExtraCapacity"))
        .def("Reserve", &Array1D<T>::Reserve, py::arg("reserveCapacity"))
        .def("Extend", &Array1D<T>::Extend, py::arg("numAdditionalElements"))
        .def("SetOverlay", &Array1D<T>::SetOverlay, py::arg("pBuf"), py::arg("nSize"))
        .def("Zero", &Array1D<T>::Zero, py::arg("zero"))
        .def("GetSize", py::overload_cast<>(&Array1D<T>::GetSize, py::const_))
        .def("GetSize", py::overload_cast<S_UINT32&>(&Array1D<T>::GetSize, py::const_), py::arg("nSize"))
        .def("GetCapacity", py::overload_cast<>(&Array1D<T>::GetCapacity, py::const_))
        .def("GetCapacity", py::overload_cast<S_UINT32&>(&Array1D<T>::GetCapacity, py::const_), py::arg("nCapacity"))
        .def("GetNumUnusedElements", &Array1D<T>::GetNumUnusedElements)
        .def("__getitem__", [](const Array1D<T>& array, S_UINT32 index) { return array[index]; })
        .def("__setitem__", [](Array1D<T>& array, S_UINT32 index, const T& value) { array[index] = value; })
        .def("GetBuffer", (const T* (Array1D<T>::*)() const) &Array1D<T>::GetBuffer, py::return_value_policy::reference)
        .def("GetBuffer", (T* (Array1D<T>::*)()) &Array1D<T>::GetBuffer, py::return_value_policy::reference)
        //.def_buffer([](Array1D<T> &m) -> py::buffer_info {  
        //    return py::buffer_info(m.GetBuffer(), sizeof(T), py::format_descriptor<T>::format(), 1,{m.GetSize()}, {sizeof(T)});
        //});
        .def("GetData", [](Array1D<T> &m) -> py::array_t<T> {
            return py::array_t<T>({m.GetSize()}, {sizeof(T)}, m.GetBuffer());
        });
}

template<typename T>
void export_Array1DArray2D(py::module &m, const std::string & typestr){
    std::string pyclass_array1Darray2D_name = std::string("Array1DArray2D") + typestr;
    py::class_<Array1D<Array2D<T>>>(m, pyclass_array1Darray2D_name.c_str())
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("size"))
        .def(py::init<const Array1D<Array2D<T>>&>())
        .def("__eq__", &Array1D<Array2D<T>>::operator==)
        .def("__ne__", &Array1D<Array2D<T>>::operator!=)
        .def("Empty", &Array1D<Array2D<T>>::Empty)
        .def("Clear", &Array1D<Array2D<T>>::Clear)
        .def("SetSize", &Array1D<Array2D<T>>::SetSize, py::arg("nSize"), py::arg("bAllocateExtraCapacity") = false)
        .def("Reserve", &Array1D<Array2D<T>>::Reserve, py::arg("reserveCapacity"))
        .def("Extend", &Array1D<Array2D<T>>::Extend, py::arg("numAdditionalElements"))
        .def("SetOverlay", &Array1D<Array2D<T>>::SetOverlay, py::arg("pBuf"), py::arg("nSize"))
        .def("Zero", &Array1D<Array2D<T>>::Zero, py::arg("zero"))
        .def("GetSize", py::overload_cast<>(&Array1D<Array2D<T>>::GetSize, py::const_))
        .def("GetSize", py::overload_cast<S_UINT32&>(&Array1D<Array2D<T>>::GetSize, py::const_), py::arg("nSize"))
        .def("GetCapacity", py::overload_cast<>(&Array1D<Array2D<T>>::GetCapacity, py::const_))
        .def("GetCapacity", py::overload_cast<S_UINT32&>(&Array1D<Array2D<T>>::GetCapacity, py::const_), py::arg("nCapacity"))
        .def("GetNumUnusedElements", &Array1D<Array2D<T>>::GetNumUnusedElements)
        .def("GetBuffer", (const Array2D<T>* (Array1D<Array2D<T>>::*)() const) &Array1D<Array2D<T>>::GetBuffer, py::return_value_policy::reference)
        .def("GetBuffer", (Array2D<T>* (Array1D<Array2D<T>>::*)()) &Array1D<Array2D<T>>::GetBuffer, py::return_value_policy::reference);
}



#endif