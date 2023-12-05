#ifndef EXPORT_POINT3D_FILE_H
#define EXPORT_POINT3D_FILE_H


#include "../headers.hh"
#include "SDICOS/Point3D.h"

using namespace SDICOS;


template<typename T>
void export_Point3D(py::module &m,  const std::string & typestr){

    std::string pyclass_point3d_name = std::string("Point3D") + typestr;

    py::class_<Point3D<T>>(m, pyclass_point3d_name.c_str())
        .def(py::init<>())
        .def(py::init<T, T, T>(), py::arg("cx") = 0, py::arg("cy") = 0, py::arg("cz") = 0)
        .def(py::init<const Point3D<T>&>())
        .def("Set", &Point3D<T>::Set, py::arg("cx"), py::arg("cy"), py::arg("cz")) 
        .def("__copy__", [](const Point3D<T> &self) { return Point3D<T>(self); })
        .def("__deepcopy__", [](const Point3D<T> &self, py::dict) { return Point3D<T>(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def_readwrite("x", &Point3D<T>::x)
        .def_readwrite("y", &Point3D<T>::y)
        .def_readwrite("z", &Point3D<T>::z);
}

#endif