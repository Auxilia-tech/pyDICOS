#include "../headers.hh"

#include "SDICOS/Vector3D.h"
#include <iostream>


using namespace SDICOS;

template<typename T>
void export_VECTOR3D(py::module &m,  const std::string & typestr) {
    std::string pyclass_vect3d_name = std::string("Vector3D") + typestr;
    py::class_<Vector3D<T>>(m, pyclass_vect3d_name.c_str())
        .def(py::init<T, T, T>(), py::arg("cx") = 0, py::arg("cy") = 0, py::arg("cz") = 0)
        .def(py::init<const T *>())
        .def(py::init<const Point3D<T> &>())
        .def("__copy__", [](const Point3D<T> &self) { return Point3D<T>(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Set", &Point3D<T>::Set, py::arg("cx"), py::arg("cy"), py::arg("cz"));
}