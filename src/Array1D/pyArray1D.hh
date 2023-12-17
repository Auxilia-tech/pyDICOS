#ifndef EXPORT_ARRAY1D_FILE_H
#define EXPORT_ARRAY1D_FILE_H

#include "../headers.hh"
#include "SDICOS/Array1D.h"
#include "CustomArray1D.hh"

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
        .def("__getitem__", (const T& (Array1D<T>::*)(S_UINT32) const) &Array1D<T>::operator[], py::arg("n"))
        .def("__getitem__", (T& (Array1D<T>::*)(S_UINT32)) &Array1D<T>::operator[], py::arg("n"))
        .def("GetBuffer", (const T* (Array1D<T>::*)() const) &Array1D<T>::GetBuffer, py::return_value_policy::reference_internal)
        .def("GetBuffer", (T* (Array1D<T>::*)()) &Array1D<T>::GetBuffer, py::return_value_policy::reference_internal)
        .def_buffer([](Array1D<T> &m) -> py::buffer_info {  
                return py::buffer_info(m.GetBuffer(), sizeof(T), py::format_descriptor<T>::format(), 1,{m.GetSize()}, {sizeof(T)});
        });
}


void export_Array1DDcsLongString(py::module &m){
    py::class_<Array1D<DcsLongString>>(m, "Array1DDcsLongString", py::buffer_protocol())
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("size"))
        .def(py::init<const Array1D<DcsLongString>&>())
        .def("Empty", &Array1D<DcsLongString>::Empty)
        .def("Clear", &Array1D<DcsLongString>::Clear)
        .def("SetSize", &Array1D<DcsLongString>::SetSize, py::arg("nSize"), py::arg("bAllocateExtraCapacity"))
        .def("Reserve", &Array1D<DcsLongString>::Reserve, py::arg("reserveCapacity"))
        .def("Extend", &Array1D<DcsLongString>::Extend, py::arg("numAdditionalElements"))
        .def("SetOverlay", &Array1D<DcsLongString>::SetOverlay, py::arg("pBuf"), py::arg("nSize"))
        .def("Zero", &Array1D<DcsLongString>::Zero, py::arg("zero"))
        .def("GetSize", py::overload_cast<>(&Array1D<DcsLongString>::GetSize, py::const_))
        .def("GetSize", py::overload_cast<S_UINT32&>(&Array1D<DcsLongString>::GetSize, py::const_), py::arg("nSize"))
        .def("GetCapacity", py::overload_cast<>(&Array1D<DcsLongString>::GetCapacity, py::const_))
        .def("GetCapacity", py::overload_cast<S_UINT32&>(&Array1D<DcsLongString>::GetCapacity, py::const_), py::arg("nCapacity"))
        .def("GetNumUnusedElements", &Array1D<DcsLongString>::GetNumUnusedElements)
        .def("__getitem__", (const DcsLongString& (Array1D<DcsLongString>::*)(S_UINT32) const) &Array1D<DcsLongString>::operator[], py::arg("n"))
        .def("__getitem__", (DcsLongString& (Array1D<DcsLongString>::*)(S_UINT32)) &Array1D<DcsLongString>::operator[], py::arg("n"))
        .def("GetBuffer", (const DcsLongString* (Array1D<DcsLongString>::*)() const) &Array1D<DcsLongString>::GetBuffer, py::return_value_policy::reference_internal)
        .def("GetBuffer", (DcsLongString* (Array1D<DcsLongString>::*)()) &Array1D<DcsLongString>::GetBuffer, py::return_value_policy::reference_internal);
}


void export_CustomArray1DDcsLongString(py::module &m){
    py::class_<CustomArray1D<DcsLongString>, Array1D<DcsLongString>>(m, "CustomArray1DDcsLongString")
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("size"))
        .def("Empty", &Array1D<DcsLongString>::Empty)
        .def("Clear", &Array1D<DcsLongString>::Clear)
        .def("SetSize", &Array1D<DcsLongString>::SetSize, py::arg("nSize"), py::arg("bAllocateExtraCapacity"))
        .def("Reserve", &Array1D<DcsLongString>::Reserve, py::arg("reserveCapacity"))
        .def("Extend", &Array1D<DcsLongString>::Extend, py::arg("numAdditionalElements"))
        .def("SetOverlay", &Array1D<DcsLongString>::SetOverlay, py::arg("pBuf"), py::arg("nSize"))
        .def("Zero", &Array1D<DcsLongString>::Zero, py::arg("zero"))
        .def("GetSize", py::overload_cast<>(&Array1D<DcsLongString>::GetSize, py::const_))
        .def("GetSize", py::overload_cast<S_UINT32&>(&Array1D<DcsLongString>::GetSize, py::const_), py::arg("nSize"))
        .def("GetCapacity", py::overload_cast<>(&Array1D<DcsLongString>::GetCapacity, py::const_))
        .def("GetCapacity", py::overload_cast<S_UINT32&>(&Array1D<DcsLongString>::GetCapacity, py::const_), py::arg("nCapacity"))
        .def("GetNumUnusedElements", &Array1D<DcsLongString>::GetNumUnusedElements)
        .def("__getitem__", (const DcsLongString& (Array1D<DcsLongString>::*)(S_UINT32) const) &Array1D<DcsLongString>::operator[], py::arg("n"))
        .def("__getitem__", (DcsLongString& (Array1D<DcsLongString>::*)(S_UINT32)) &Array1D<DcsLongString>::operator[], py::arg("n"))
        .def("GetBuffer", (const DcsLongString* (Array1D<DcsLongString>::*)() const) &Array1D<DcsLongString>::GetBuffer, py::return_value_policy::reference_internal)
        .def("GetBuffer", (DcsLongString* (Array1D<DcsLongString>::*)()) &Array1D<DcsLongString>::GetBuffer, py::return_value_policy::reference_internal)
        .def("SetBuffer", &CustomArray1D<DcsLongString>::SetBuffer, py::arg("i"), py::arg("value"));
   
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
        .def("GetBuffer", (const Array2D<T>* (Array1D<Array2D<T>>::*)() const) &Array1D<Array2D<T>>::GetBuffer, py::return_value_policy::reference_internal)
        .def("GetBuffer", (Array2D<T>* (Array1D<Array2D<T>>::*)()) &Array1D<Array2D<T>>::GetBuffer, py::return_value_policy::reference_internal);
}



#endif