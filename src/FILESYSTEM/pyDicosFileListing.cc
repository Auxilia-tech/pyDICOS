#include "../headers.hh"

#include "SDICOS/DicosFile.h"

using namespace SDICOS;

void export_DicosFileListing(py::module &m)
{
    py::class_<DicosFileListing::Series>(m, "Series")
        .def(py::init<>())
        .def(py::init<const DicosFileListing::Series&>(), py::arg("series"))
        .def("__copy__", [](const DicosFileListing::Series& self) { return DicosFileListing::Series(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__getitem__", (const DicosFileListing::SopInstance& (DicosFileListing::Series::*)(S_UINT64) const) &DicosFileListing::Series::operator[], py::arg("n"))
        .def("FreeMemory", &DicosFileListing::Series::FreeMemory)
        .def("AddFile", &DicosFileListing::Series::AddFile, py::arg("filename"), py::arg("attribManager"))
        .def("GetInstances", &DicosFileListing::Series::GetInstances, py::arg("arrayInstances"))
        .def("GetNumberOfInstances", &DicosFileListing::Series::GetNumberOfInstances)
        .def("HasCT", &DicosFileListing::Series::HasCT)
        .def("HasDX", &DicosFileListing::Series::HasDX)
        .def("HasTDR", &DicosFileListing::Series::HasTDR);

    py::class_<DicosFileListing::Scan>(m, "Scan")
        .def(py::init<>())
        .def(py::init<const DicosFileListing::Scan&>(), py::arg("scan"))
        .def("__copy__", [](const DicosFileListing::Scan& self) { return DicosFileListing::Scan(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__getitem__", (const DicosFileListing::Series& (DicosFileListing::Scan::*)(S_UINT64) const) &DicosFileListing::Scan::operator[], py::arg("n"))
        .def("AddFile", &DicosFileListing::Scan::AddFile, py::arg("filename"), py::arg("attribManager"))
        .def("GetNumberOfFiles", &DicosFileListing::Scan::GetNumberOfFiles);

    py::class_<DicosFileListing::ObjectOfInspection>(m, "ObjectOfInspection")
        .def(py::init<>())
        .def(py::init<const DicosFileListing::ObjectOfInspection&>(), py::arg("ooi"))
        .def("__copy__", [](const DicosFileListing::ObjectOfInspection& self) { return DicosFileListing::ObjectOfInspection(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__getitem__", (const DicosFileListing::Scan& (DicosFileListing::ObjectOfInspection::*)(S_UINT64) const) &DicosFileListing::ObjectOfInspection::operator[], py::arg("n"))
        .def("AddFile", &DicosFileListing::ObjectOfInspection::AddFile, py::arg("filename"), py::arg("attribManager"))
        .def("GetNumberOfScans", &DicosFileListing::ObjectOfInspection::GetNumberOfScans)
        .def("GetScans", &DicosFileListing::ObjectOfInspection::GetScans, py::arg("arrayScans"))
        .def("GetNumberOfFiles", &DicosFileListing::ObjectOfInspection::GetNumberOfFiles);
    
    py::class_<DicosFileListing::SopInstance>(m, "SopInstance")
        .def(py::init<>())
        .def(py::init<const DicosFileListing::SopInstance&>(), py::arg("instance"))
        .def("__copy__", [](const DicosFileListing::SopInstance& self) { return DicosFileListing::SopInstance(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__getitem__", (const Filename& (DicosFileListing::SopInstance::*)(S_UINT64) const) &DicosFileListing::SopInstance::operator[], py::arg("n"))
        .def("FreeMemory", &DicosFileListing::SopInstance::FreeMemory)
        .def("IsCT", &DicosFileListing::SopInstance::IsCT)
        .def("IsDX", &DicosFileListing::SopInstance::IsDX)
        .def("IsTDR", &DicosFileListing::SopInstance::IsTDR)
        .def("GetFilenames", &DicosFileListing::SopInstance::GetFilenames, py::arg("arrayFilenames"))
        .def("GetNumberOfFilenames", &DicosFileListing::SopInstance::GetNumberOfFilenames)
        .def("GetSopClassUID", &DicosFileListing::SopInstance::GetSopClassUID)
        .def("GetUID", &DicosFileListing::SopInstance::GetUID)
        .def("HasFile", &DicosFileListing::SopInstance::HasFile, py::arg("filename"))
        .def("AddFile", &DicosFileListing::SopInstance::AddFile, py::arg("filename"), py::arg("attribManager"));

    py::class_<DicosFileListing>(m, "DicosFileListing")
        .def(py::init<>())
        .def(py::init<const DicosFileListing&>(), py::arg("filelisting"))
        .def("FreeMemory", &DicosFileListing::FreeMemory)
        .def("Cancel", &DicosFileListing::Cancel)
        .def("__copy__", [](const DicosFileListing& self) { return DicosFileListing(self); })
        .def("__deepcopy__", [](const DicosFileListing& self, py::dict) { return DicosFileListing(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("FindDicosFiles", py::overload_cast<
                                            const Array1D<Filename>&, 
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
                                            )


        .def("__getitem__", (const DicosFileListing::ObjectOfInspection& (DicosFileListing::*)(S_UINT64) const) &DicosFileListing::operator[], py::arg("n"))
        .def("GetNumberOfFiles", &DicosFileListing::GetNumberOfFiles)
        .def("GetFileInfo", &DicosFileListing::GetFileInfo, py::arg("arrayFiles"))
        .def("GetSopInstanceFiles", &DicosFileListing::GetSopInstanceFiles, py::arg("vSopInstances"))
        .def("GetSopInstanceUID", &DicosFileListing::GetSopInstanceUID, py::arg("filename"), py::arg("dsSopInstanceUID"));

}
