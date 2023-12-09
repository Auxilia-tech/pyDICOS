#ifndef HEADERS_FILE_H
#define HEADERS_FILE_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/cast.h>
#include <map>
#include <string>
#include <iostream>


namespace py = pybind11;
void export_ERRORLOG(py::module &);
void export_IMEMMANAGER(py::module &);
void export_FS(py::module &);
void export_SECTION(py::module &);
void export_CT(py::module &);
void export_DCSSTRING(py::module &);
void export_MEMORYBUFFER(py::module &);
void export_ARRAY1D_PAIR_BOOL_MEMBUFF(py::module &m);
void export_Volume(py::module &m);
void export_DicosFileListing(py::module &m);
void export_DX(py::module &);
void export_TDR(py::module &);
void export_Image2D(py::module &);

#endif