#ifndef HEADERS_FILE_H
#define HEADERS_FILE_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/cast.h>
#include <pybind11/numpy.h>
#include <map>
#include <string>
#include <iostream>


namespace py = pybind11;
void export_ERRORLOG(py::module &m);
void export_IMEMMANAGER(py::module &m);
void export_FS(py::module &m);
void export_SECTION(py::module &m);
void export_CT(py::module &m);
void export_DCSSTRING(py::module &m);
void export_MEMORYBUFFER(py::module &m);
void export_ARRAY1D_PAIR_BOOL_MEMBUFF(py::module &m);
void export_Volume(py::module &m);
void export_DicosFileListing(py::module &m);
void export_DX(py::module &m);
void export_TDR(py::module &m);
void export_Image2D(py::module &m);
void export_BITMAP(py::module &m);
void export_DCSGUID(py::module &m);
void export_SopClassUID(py::module &m);
void export_GeneralSeriesModule(py::module &m);
void export_DCSCLIENT(py::module &m);
void export_IDCSSERVER(py::module &m);
void export_DCSSERVER(py::module &m);
void export_IRECEIVECALLBACK(py::module &m);
void export_DataProcessingMultipleConnections(py::module &m);
void export_ICLIENTAUTHENTICATIONCALLBACK(py::module &m);

#endif