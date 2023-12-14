#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "../headers.hh"

#include "SDICOS/UserTDR.h"
 #include "SDICOS/DicosFile.h"
 #include "SDICOS/SopClassUID.h"
 #include "SDICOS/TemplateBase.h"
 #include "SDICOS/ModuleTDR.h"
 #include "SDICOS/FrameOfReferenceUser.h"

namespace py = pybind11;

using namespace SDICOS;


class PyTDR : public TDR {
public:
    using TDR::TDR;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  TDR, FreeMemory); }

    bool Write(const Filename &filename, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  TDR, Write, filename, errorLog, nTransferSyntax);}  

    bool Write(MemoryBuffer &memorybuffer, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  TDR, Write, memorybuffer, errorLog, nTransferSyntax);}  

    bool Write(MemoryFile &memfile, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  TDR, Write, memfile, errorLog, nTransferSyntax);}  

    bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  TDR, Read, filename, errorLog, pMemMgr);}  
    
    bool Read(MemoryFile &memfile, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  TDR, Read, memfile, errorLog, pMemMgr);}  

    IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(IODCommon::MODALITY, TDR, GetModality);}  
    
};

void export_TDR(py::module &m)
{
    py::enum_<TDRTypes::ThreatDetectionReport::TDR_TYPE>(m, "TDR_TYPE")
        .value("enumUnknownTDRType", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumUnknownTDRType)
        .value("enumMachine", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumMachine)
        .value("enumOperator", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumOperator)
        .value("enumGroundTruth", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumGroundTruth)
        .value("enumAggregate", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumAggregate)
        .value("enumModAggregate", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumModAggregate)
        .value("enumUndefined", TDRTypes::ThreatDetectionReport::TDR_TYPE::enumUndefined)
        .export_values();

    py::enum_<ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER>(m, "OBJECT_OF_INSPECTION_GENDER")
        .value("enumUnknownObjectOfInspectionGender", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER::enumUnknownObjectOfInspectionGender)
        .value("enumGenderMale", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER::enumGenderMale)
        .value("enumGenderFemale", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER::enumGenderFemale)
        .value("enumGenderOther", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER::enumGenderOther)
        .value("enumGenderUnknown", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER::enumGenderUnknown)
        .export_values();

    py::enum_<ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE>(m, "OBJECT_OF_INSPECTION_ID_TYPE")
        .value("enumUnknownObjectOfInspectionType", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumUnknownObjectOfInspectionIdType)
        .value("enumTypeBioSample", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumText)
        .value("enumTypeCargo", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumRFID)
        .value("enumTypeBaggage", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumBarcode)
        .value("enumTypeAnimal", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumMRP)
        .export_values();

    py::class_<TDR>(m, "SDICOS::TDR");
    py::class_<PyTDR, TDR, IODCommon, FrameOfReferenceUser>(m, "TDR")
        .def(py::init<>())
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreatDetectionReport::TDR_TYPE, 
                      const S_INT32>(), 
                      py::arg("OOIType"), 
                      py::arg("tdrType"), 
                      py::arg("instanceNumber"))
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreatDetectionReport::TDR_TYPE, 
                      const S_INT32, 
                      const DcsDate&, 
                      const DcsTime&>(), 
                       py::arg("OOIType"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"), 
                       py::arg("contentCreationDate"), 
                       py::arg("contentCreationTime"))
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER, 
                      const TDRTypes::ThreatDetectionReport::TDR_TYPE, 
                      const S_INT32, 
                      const DcsDate&, 
                      const DcsTime&>(), 
                       py::arg("gender"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"), 
                       py::arg("contentCreationDate"), 
                       py::arg("contentCreationTime"))
        .def(py::init<const DcsLongString&, 
                      const ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE&,
                      const DcsLongString&,
                      const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreatDetectionReport::TDR_TYPE, 
                      const S_INT32>(), 
                       py::arg("OOIIdentifier"), 
                       py::arg("IdType"), 
                       py::arg("OOIIdentifierIssuer"), 
                       py::arg("OOIType"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"))
        .def("__copy__", [](const TDR &self) { return TDR(self); })
        .def("__deepcopy__", [](const TDR &self, py::dict) { return TDR(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Initialize", py::overload_cast<const TDRModule&, 
                                             ErrorLog&, 
                                             const bool>
                           (&PyTDR::Initialize), 
                           py::arg("tdr"), 
                           py::arg("errorlog"),
                           py::arg("bMoveData") = false)
        .def("Initialize", py::overload_cast<const DcsLongString&, 
                                             const ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE&,
                                             const DcsLongString&,
                                             const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                                             const TDRTypes::ThreatDetectionReport::TDR_TYPE, 
                                             const S_INT32>
                           (&PyTDR::Initialize),
                           py::arg("OOIIdentifier"), 
                           py::arg("IdType"), 
                           py::arg("OOIIdentifierIssuer"), 
                           py::arg("OOIType"), 
                           py::arg("tdrType"), 
                           py::arg("instanceNumber"))    
        .def("Write", py::overload_cast<const Filename&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyTDR::TDR::Write, py::const_), 
                     py::arg("filename"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = DicosFile::enumLosslessJPEG)
        .def("Write", py::overload_cast<MemoryBuffer&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyTDR::TDR::Write, py::const_), 
                     py::arg("memorybuffer"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = DicosFile::enumLosslessJPEG)
        .def("Write", py::overload_cast<MemoryFile&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyTDR::TDR::Write, py::const_),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("nTransferSyntax") = DicosFile::enumLosslessJPEG)
        .def("Read", py::overload_cast<const Filename&, 
                                       ErrorLog&, 
                                       IMemoryManager*
                                       >
                     (&PyTDR::TDR::Read),
                     py::arg("filename"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<MemoryFile&, 
                                       ErrorLog& , 
                                       IMemoryManager*
                                       >
                     (&PyTDR::TDR::Read),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)   
        .def("GetModality", py::overload_cast<>(&PyTDR::TDR::GetModality, py::const_))
        .def("SetInstanceNumber", &TDR::SetInstanceNumber, py::arg("nInstanceNumber"))
        .def("GetInstanceNumber", &TDR::GetInstanceNumber)
        .def("SetContentDateAndTime", &TDR::SetContentDateAndTime, py::arg("contentCreationDate"), py::arg("contentCreationTime"))
        .def("GetContentDate", &TDR::GetContentDate)
        .def("GetContentTime", &TDR::GetContentTime)
        .def("SetTDRType", &TDR::SetTDRType, py::arg("tdrType"))
        .def("GetTDRType", &TDR::GetTDRType)
        .def("SetTDRTypeATR", &TDR::SetTDRTypeATR, py::arg("atrManufacturer"), 
                                                   py::arg("atrVersion"), 
                                                   py::arg("atrParameters") = Array1D<DcsLongString>())
        .def("GetATRInfo", [](TDR &self, DcsLongString& atrManufacturer, 
                                        DcsLongString& atrVersion, 
                                        Array1D<DcsLongString>& atrParameters) {
            return std::make_tuple(self.GetATRInfo(atrManufacturer, 
                                                    atrVersion, 
                                                    atrParameters), 
                                                    atrManufacturer, 
                                                    atrVersion, 
                                                    atrParameters);
                                        }, 
            py::arg("atrManufacturer"), py::arg("atrVersion"), py::arg("atrParameters"));
   
}
