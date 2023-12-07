#include "../headers.hh"

#include "SDICOS/DicosFile.h"

using namespace SDICOS;

void export_DicosFileListing(py::module &m)
{
    py::class_<DicosFileListing>(m, "DicosFileListing")
        .def(py::init<>())
        .def(py::init<const DicosFileListing&>(), py::arg("filelisting"))
        .def("FreeMemory", &DicosFileListing::FreeMemory)
        .def("Cancel", &DicosFileListing::Cancel)
        .def("__copy__", [](const DicosFileListing& self) { return DicosFileListing(self); })
        .def("__deepcopy__", [](const DicosFileListing& self, py::dict) { return DicosFileListing(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("FindDicosFiles", py::overload_cast<const Array1D<Filename>&, 
                                           Array1D<std::pair<Filename, ErrorLog> >&,
                                           const std::set<std::string>&,
                                           const bool,
                                           const bool,
                                           PFN_PROGRESS_CALLBACK, 
                                           void *>
                                           (&DicosFileListing::FindDicosFiles),  
                                           py::arg("arrayFilenames"), 
                                           py::arg("arrayErrorLog"), 
                                           py::arg("setIncludeFileExtensions") = std::set<std::string>(),
                                           py::arg("bExcludeDicosVerification") = false,
                                           py::arg("bFromOpticalDrive") = false,
                                           py::arg("pfnProgress") = NULL,
                                           py::arg("pHint") = NULL
                                            )
        .def("FindDicosFiles", py::overload_cast<
                                           const Folder&, 
                                           const bool ,
                                           Array1D<std::pair<Filename, ErrorLog> >&,
                                            const std::set<std::string> &,
                                           const bool,
                                           const bool,
                                           PFN_PROGRESS_CALLBACK, 
                                           void *>
                                           (&DicosFileListing::FindDicosFiles),  
                                           py::arg("folder"), 
                                           py::arg("bSearchSubfolders"), 
                                           py::arg("arrayErrorLog"), 
                                           py::arg("setIncludeFileExtensions") = std::set<std::string>(),
                                           py::arg("bExcludeDicosVerification") = false,
                                           py::arg("bFromOpticalDrive") = false,
                                           py::arg("pfnProgress") = NULL,
                                           py::arg("pHint") = NULL
                                            );

}
