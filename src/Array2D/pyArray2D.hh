#ifndef EXPORT_ARRAY2D_FILE_H
#define EXPORT_ARRAY2D_FILE_H


#include "../headers.hh"
#include "SDICOS/Array2D.h"

using namespace SDICOS;

template<typename T>
class PyArray2D : public Array2D<T> {
public:
    using classarray2d = Array2D<T>;
     bool SetSize(S_UINT32 nWidth, S_UINT32 nHeight) override 
                 { PYBIND11_OVERRIDE(bool,  classarray2d, SetSize, nWidth, nHeight); }
     bool SetOverlay(S_UINT8 pBuf[], const S_UINT32 nWidth, const S_UINT32 nHeight) override 
                 { PYBIND11_OVERRIDE(bool,  classarray2d, SetOverlay, pBuf, nWidth, nHeight); }
     void MoveData(T* pSource, const S_UINT32 nWidth, const S_UINT32 nHeight) override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, MoveData, pSource, nWidth, nHeight); }
     void MoveData(Array2D<T>& vSrc) override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, MoveData, vSrc); }
     void Zero(const T& zero) override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, Zero, zero); }
     void FreeMemory() override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, FreeMemory); }
     void GetWidth() override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, GetWidth); }
     void GetHeight() override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, GetHeight); }
     void GetSize(S_UINT32& nW, S_UINT32& nH) override 
                 { PYBIND11_OVERRIDE(void,  classarray2d, GetSize, nW, nH); }
};


template<typename T>
void export_Array2D(py::module &m, const std::string & typestr){
    std::string pyclass_array2D_name = std::string("Array2D") + typestr;

   py::class_<Array2D<T>>(m, pyclass_array2D_name.c_str())
        .def(py::init<>())
        .def(py::init<const S_UINT32, 
                      const S_UINT32>(),   
                      py::arg("nWidth"), 
                      py::arg("nHeight"))

        .def(py::init<const Array2D<T>>())

        .def("__copy__", [](const Array2D<T> &self) { return Array2D<T>(self); })
        .def("__deepcopy__", [](const Array2D<T> &self, py::dict) { return Array2D<T>(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("SetSize", [](Array2D<T> &obj, S_UINT32 nWidth, S_UINT32 nHeight) { 
                          return obj.SetSize(nWidth, nHeight); }, py::arg("nWidth"), py::arg("nHeight"))
        .def("SetOverlay", [](Array2D<T> &obj, S_UINT8 pBuf[], S_UINT32 nWidth, S_UINT32 nHeight) { 
                          return obj.SetOverlay(pBuf, nWidth, nHeight); }, py::arg("pBuf"), py::arg("nWidth"), py::arg("nHeight"))
        .def("MoveData", [](Array2D<T>& obj, T* pSource, S_UINT32 nWidth, S_UINT32 nHeight) { 
                          return obj.MoveData(pSource, nWidth, nHeight); }, py::arg("pSource"), py::arg("nWidth"), py::arg("nHeight"))
        .def("MoveData", [](Array2D<T>& obj, Array2D<T>& vSrc) { 
                          return obj.MoveData(vSrc); }, py::arg("vSrc"))
        .def("Zero", [](Array2D<T>& obj, const T& zero) { 
                          return obj.Zero(zero); }, py::arg("zero"))
        .def("FreeMemory", [](Array2D<T>& obj) { 
                          return obj.FreeMemory(); })
        .def("GetWidth", [](Array2D<T>& obj) { 
                          return obj.GetWidth(); })
        .def("GetHeight", [](Array2D<T>& obj) { 
                          return obj.GetHeight(); })
        .def("GetSize", [](Array2D<T>& obj, S_UINT32& nW, S_UINT32& nH) { 
                          return obj.GetSize(nW, nH); }, py::arg("nW"), py::arg("nH"))
        .def("Get", &Array2D<T>::Get, py::arg("i"), py::arg("j"))
        .def("At", &Array2D<T>::At, py::arg("i"), py::arg("j"))
        .def("Set", &Array2D<T>::Set, py::arg("i"), py::arg("j"), py::arg("obj"))
        .def("GetBuffer", (const T* (Array2D<T>::*)() const) &Array2D<T>::GetBuffer)
        .def("GetBuffer", (T* (Array2D<T>::*)()) &Array2D<T>::GetBuffer);
}

#endif