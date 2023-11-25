#include "../headers.hh"

#include "SDICOS/String.h"

using namespace SDICOS;

void export_DCSSTRING(py::module &m)
{
    py::class_<DcsString>(m, "DcsString")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsString&>(), py::arg("str"))
        .def("Get", py::overload_cast<>(&DcsString::Get, py::const_))
        .def("Get", py::overload_cast<char&, const S_UINT32>(&DcsString::Get, py::const_), 
                     py::arg("str"), 
                     py::arg("nIndex"))
        .def("Get", py::overload_cast<wchar_t&, const S_UINT32>(&DcsString::Get, py::const_), 
                     py::arg("str"), 
                     py::arg("nIndex"));

     py::class_<DcsLongString, DcsString>(m, "DcsLongString")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsLongString&>(), py::arg("dcslongstring"));
}
