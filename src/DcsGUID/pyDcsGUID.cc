#include "../headers.hh"

#include "SDICOS/ToolsLight.h"

using namespace SDICOS;


void export_DCSGUID(py::module &m)
{
    py::class_<DcsGUID>(m, "DcsGUID")
        .def(py::init<>())
        .def("__eq__", (bool (DcsGUID::*)(const DcsGUID &)) &DcsGUID::operator==)
        .def("Generate", &DcsGUID::Generate)
        .def("Set", py::overload_cast<const std::string &>(&DcsGUID::Set), py::arg("str"))
        .def("Set", py::overload_cast<const DcsString &>(&DcsGUID::Set), py::arg("str"))
        .def("AsString", &DcsGUID::AsString)
        .def("AsString", &DcsGUID::AsDecimalString)  
        .def("GenerateAsString", &DcsGUID::GenerateAsString)
        .def("GenerateAsDecimalString", &DcsGUID::GenerateAsDecimalString);
}
