#include "../headers.hh"

#include "SDICOS/ErrorLog.h"

using namespace SDICOS;

void export_ERRORLOG(py::module &m)
{
    py::enum_<Redirect::REDIRECT_LOG_TYPE>(m, "REDIRECT_LOG_TYPE")
        .value("enumRedirect_Warning", Redirect::REDIRECT_LOG_TYPE::enumRedirect_Warning)
        .value("enumRedirect_Error", Redirect::REDIRECT_LOG_TYPE::enumRedirect_Error);

    py::class_<ErrorLog>(m, "ErrorLog")
        .def(py::init<>())
        .def(py::init<const ErrorLog&>(), py::arg("errorlog"))
        .def("FreeMemory", &ErrorLog::FreeMemory)
        .def_static("SetErrorLogRedirect", &ErrorLog::SetErrorLogRedirect, "Set the redirect function")
        .def_static("HasRedirect", &ErrorLog::HasRedirect)
        .def("IgnoreErrorLogRedirect", &ErrorLog::IgnoreErrorLogRedirect)
        .def("UseErrorLogRedirect", &ErrorLog::UseErrorLogRedirect);
}
