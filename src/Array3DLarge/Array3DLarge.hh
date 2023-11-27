#include "../headers.hh"
#include "SDICOS/Array3DLarge.h"

using namespace SDICOS;

template<typename T>
void export_Array3DLarge(py::module &m,  const std::string & typestr){

    py::enum_<ITERATION_DIRECTION>(m, "ITERATION_DIRECTION")
        .value("ITERATION_DIRECTION_FORWARD", ITERATION_DIRECTION::ITERATION_DIRECTION_FORWARD)
        .value("ITERATION_DIRECTION_BACKWARD", ITERATION_DIRECTION::ITERATION_DIRECTION_BACKWARD)
        .value("ITERATION_END", ITERATION_DIRECTION::ITERATION_END)
        .export_values();

    std::string pyclass_array3d_large_name = std::string("Array3DLarge") + typestr;
    std::string pyclass_array1d_name = std::string("Array1D") + typestr;

    py::class_<Array3DLargeBase>(m, "Array3DLargeBase");
    py::class_<Array1D<Array2D<T>*>>(m, pyclass_array1d_name.c_str());
    py::class_<Array3DLarge<T>, Array1D<Array2D<T>*>, Array3DLargeBase>(m, pyclass_array3d_large_name.c_str())
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
        .def("GetSlice",(Array2D<T>*(Array3DLarge<T>::*)(const S_UINT32))&Array3DLarge<T>::GetSlice, py::arg("nD"))
        .def("AddSlice",(Array2D<T>*(Array3DLarge<T>::*)(const S_UINT32, const S_UINT32))&Array3DLarge<T>::AddSlice, py::arg("width"), py::arg("height"))
        .def("AddSlice",(Array2D<T>*(Array3DLarge<T>::*)(T*, const S_UINT32, const S_UINT32))&Array3DLarge<T>::AddSlice, py::arg("pSlice"), py::arg("width"), py::arg("height"))
        .def("AddSlice",(bool(Array3DLarge<T>::*)(Array2D<T>*, 
                                                  const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY, 
                                                  const T*))&Array3DLarge<T>::AddSlice, 
                                                  py::arg("pNewSlice"), 
                                                  py::arg("nFailurePolicy") = Array3DLargeBase::ADD_SLICE_FAILURE_POLICY::EARLY_OUT, 
                                                  py::arg("pfFillValue") = S_NULL)

        .def("AddSlices",(bool(Array3DLarge<T>::*)(Array2D<T>**, 
                                                  const S_UINT32))&Array3DLarge<T>::AddSlices, 
                                                  py::arg("pNewSlices"), 
                                                  py::arg("numSlices"));

}