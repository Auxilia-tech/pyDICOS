#ifndef HEADERS_FILE_H
#define HEADERS_FILE_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <map>
#include <string>
#include <iostream>

namespace py = pybind11;
void export_FS(py::module &);
void export_CT(py::module &);
//void export_DX(py::module &);
//void export_TDR(py::module &);

#endif