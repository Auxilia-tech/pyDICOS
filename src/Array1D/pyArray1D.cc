#include "../headers.hh"

#include "SDICOS/Array1D.h"
#include "SDICOS/MemoryBuffer.h"

using namespace SDICOS;

void export_ARRAY1D(py::module &m){
    py::class_<Array1D<std::pair<bool, MemoryBuffer>>>(m,"Array1D")
        .def(py::init<>())
        .def(py::init<const S_UINT32>())
        .def(py::init<const Array1D<std::pair<bool, MemoryBuffer>>&>())
        .def("__eq__", &Array1D<std::pair<bool, MemoryBuffer>>::operator==)
        .def("__ne__", &Array1D<std::pair<bool, MemoryBuffer>>::operator!=)
        .def("Empty", &Array1D<std::pair<bool, MemoryBuffer>>::Empty)
        .def("Clear", &Array1D<std::pair<bool, MemoryBuffer>>::Clear)
        .def("SetSize", &Array1D<std::pair<bool, MemoryBuffer>>::SetSize, py::arg("nSize"), py::arg("bAllocateExtraCapacity"))
        .def("Reserve", &Array1D<std::pair<bool, MemoryBuffer>>::Reserve, py::arg("reserveCapacity"))
        .def("Extend", &Array1D<std::pair<bool, MemoryBuffer>>::Extend, py::arg("numAdditionalElements"))
        .def("SetOverlay", &Array1D<std::pair<bool, MemoryBuffer>>::SetOverlay, py::arg("pBuf"), py::arg("nSize"))
        .def("Zero", &Array1D<std::pair<bool, MemoryBuffer>>::Zero, py::arg("zero"))
        .def("GetSize", py::overload_cast<>(&Array1D<std::pair<bool, MemoryBuffer>>::GetSize, py::const_))
        .def("GetSize", py::overload_cast<S_UINT32&>(&Array1D<std::pair<bool, MemoryBuffer>>::GetSize, py::const_), py::arg("nSize"))
        .def("GetCapacity", py::overload_cast<>(&Array1D<std::pair<bool, MemoryBuffer>>::GetCapacity, py::const_))
        .def("GetCapacity", py::overload_cast<S_UINT32&>(&Array1D<std::pair<bool, MemoryBuffer>>::GetCapacity, py::const_), py::arg("nCapacity"))
        .def("GetNumUnusedElements", &Array1D<std::pair<bool, MemoryBuffer>>::GetNumUnusedElements)
        .def("__getitem__", [](const Array1D<std::pair<bool, MemoryBuffer>>& array, S_UINT32 index) { return array[index]; })
        .def("__setitem__", [](Array1D<std::pair<bool, MemoryBuffer>>& array, S_UINT32 index, const std::pair<bool, MemoryBuffer>& value) { array[index] = value; })
        .def("GetBuffer", (const std::pair<bool, MemoryBuffer>* (Array1D<std::pair<bool, MemoryBuffer>>::*)() const) &Array1D<std::pair<bool, MemoryBuffer>>::GetBuffer)
        .def("GetBuffer", (std::pair<bool, MemoryBuffer>* (Array1D<std::pair<bool, MemoryBuffer>>::*)()) &Array1D<std::pair<bool, MemoryBuffer>>::GetBuffer);
}