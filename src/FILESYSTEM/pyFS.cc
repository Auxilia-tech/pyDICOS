#include "../headers.hh"

#include "SDICOS/FileSystem.h"

using namespace SDICOS;

void export_FS(py::module &m)
{
    py::class_<Folder>(m, "SDICOS::Folder")
        .def(py::init<const std::string&>(), py::arg("strFolder") = "")
        .def(py::init<const Folder&, const std::string&>(), py::arg("folderParent"), py::arg("strSubFolder"))
        .def("Set", &Folder::Set, py::arg("strFolder") = "")
        .def("GetDrive", &Folder::GetDrive)
        .def("GetDirectory", &Folder::GetDirectory)
        .def("GetFullFolder", &Folder::GetFullFolder)
        .def("GetParentFolder", &Folder::GetParentFolder, py::arg("folder"))
        .def("GetSubFolder", &Folder::GetSubFolder)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("GetCurrentWorkingFolder", &Folder::GetCurrentWorkingFolder)
        .def("SetCurrentWorkingFolder", &Folder::SetCurrentWorkingFolder)
        .def(" GetLastError", &Folder:: GetLastError);

    py::class_<Folder>(m, "Folder");
    py::class_<Filename>(m, "SDICOS::Filename");
    py::class_<Filename, Folder>(m, "Filename")
        .def(py::init<const char*>(), py::arg("strFullPath"));
}
