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

    py::enum_<TDRTypes::ThreatDetectionReport::ABORT_REASON>(m, "ABORT_REASON")
        .value("enumUnknownTDRType", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumUnknownAbortReason)
        .value("enumOversizeBag", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumOversizeBag)
        .value("enumClippedBag", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumClippedBag)
        .value("enumIncompleteScan", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumIncompleteScan)
        .value("enumFailedRecon", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumFailedRecon)
        .value("enumTimeout", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumTimeout)
        .value("enumNotReviewed", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumNotReviewed)
        .value("enumUnknownDataType", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumUnknownDataType)
        .value("enumUserInterrupt", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumUserInterrupt)
        .value("enumOutOfBounds", TDRTypes::ThreatDetectionReport::ABORT_REASON::enumOutOfBounds)
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

    py::enum_<TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA>(m, "ADDITIONAL_INSPECTION_SELECTION_CRITERIA")
        .value("enumRandom", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumRandom)
        .value("enumBehavioral", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumBehavioral)
        .value("enumAll", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumAll)
        .value("enumOwnerRisk", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumOwnerRisk)
        .value("enumFlightRisk", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumFlightRisk)
        .value("enumThreatLevel", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumThreatLevel)
        .export_values();


    py::class_<TDR::AdditionalInspectionData>(m, "TDR::AdditionalInspectionData")
        .def(py::init<>())
        .def(py::init<const TDR::AdditionalInspectionData&>())
        .def("__copy__", [](const TDR::AdditionalInspectionData &self) { return TDR::AdditionalInspectionData(self); })
        .def("__deepcopy__", [](const TDR::AdditionalInspectionData &self, py::dict) { return TDR::AdditionalInspectionData(self); })
        .def(py::self == py::self)
        .def(py::self != py::self);

    py::class_<TDR>(m, "SDICOS::TDR");
    py::class_<PyTDR, TDR, IODCommon, FrameOfReferenceUser>(m, "TDR")
        .def_property_readonly_static("OBJECT_OF_INSPECTION_ID_TYPE", [m](py::object) {
            return m.attr("OBJECT_OF_INSPECTION_ID_TYPE");
        }) 
        .def_property_readonly_static("OBJECT_OF_INSPECTION_GENDER", [m](py::object) {
            return m.attr("OBJECT_OF_INSPECTION_GENDER");
        }) 
        .def_property_readonly_static("TDR_TYPE", [m](py::object) {
            return m.attr("TDR_TYPE");
        }) 
        .def_property_readonly_static("OBJECT_OF_INSPECTION_GENDER", [m](py::object) {
            return m.attr("OBJECT_OF_INSPECTION_GENDER");
        }) 
        .def_property_readonly_static("ABORT_REASON", [m](py::object) {
            return m.attr("ABORT_REASON");
        }) 
        .def_property_readonly_static("ADDITIONAL_INSPECTION_SELECTION_CRITERIA", [m](py::object) {
            return m.attr("ADDITIONAL_INSPECTION_SELECTION_CRITERIA");
        }) 
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
        .def("GetATRInfo", [](TDR &self, DcsLongString& atrManufacturer, DcsLongString& atrVersion, Array1D<DcsLongString>& atrParameters) {
            return std::make_tuple(self.GetATRInfo(atrManufacturer, atrVersion, atrParameters), atrManufacturer, atrVersion, atrParameters);
            }, py::arg("atrManufacturer"), py::arg("atrVersion"),  py::arg("atrParameters"))       
        .def("SetOperatorTDR", &TDR::SetOperatorTDR, py::arg("operatorId"), py::arg("IdIssuer"), py::arg("operatorFullName"), py::arg("IdType"))
        
        .def("GetOperatorTDR", [](TDR &self, DcsLongString& operatorId, DcsLongString& IdIssuer, DcsPersonName& operatorFullName, IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE& IdType) {
            return std::make_tuple(self.GetOperatorTDR(operatorId, IdIssuer, operatorFullName, IdType), operatorId, IdIssuer, operatorFullName, IdType);
            }, py::arg("operatorId"), py::arg("IdIssuer"), py::arg("operatorFullName"), py::arg("IdType"))
        
        .def("SetImageScaleRepresentation", &TDR::SetImageScaleRepresentation, py::arg("imageScale"))
        .def("GetImageScaleRepresentation", &TDR::GetImageScaleRepresentation)
        
        .def("SetAlarmDecision", &TDR::SetAlarmDecision, py::arg("alarmDecision"))
        .def("GetAlarmDecision", &TDR::GetAlarmDecision)
        .def("SetAlarmDecisionDateTime", &TDR::SetAlarmDecisionDateTime, py::arg("alarmDecisionDate"), py::arg("alarmDecisionTime"))
        
        .def("GetAlarmDecisionDateTime", [](TDR &self, DcsDate& alarmDecisionDate, DcsTime& alarmDecisionTime) {
            return std::make_tuple(self.GetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime), alarmDecisionDate, alarmDecisionTime);
            }, py::arg("alarmDecisionDate"), py::arg("alarmDecisionTime"))

        .def("SetAbortFlag", &TDR::SetAbortFlag, 
                              py::arg("abortFlag"), 
                              py::arg("abortReason") = TDRTypes::ThreatDetectionReport::enumUnknownAbortReason)
        
        .def("GetAbortFlag", [](TDR &self,TDRTypes::ThreatDetectionReport::ABORT_FLAG& abortFlag, TDRTypes::ThreatDetectionReport::ABORT_REASON& abortReason) {
            return std::make_tuple(self.GetAbortFlag(abortFlag, abortReason), abortFlag, abortReason);
            }, py::arg("abortFlag"), py::arg("abortReason"))
        .def("GetAbortFlag", [](TDR &self) {return self.GetAbortFlag();})
        
        .def("GetAbortReason", &TDR::GetAbortReason)
        .def("GetNumberOfObjects", [](TDR &self, S_UINT16& numPotentialThreatObjects, S_UINT16& numAlarmObjects) {
            return std::make_tuple(self.GetNumberOfObjects(numPotentialThreatObjects, numAlarmObjects), numPotentialThreatObjects, numAlarmObjects);
            }, py::arg("abortFlag"), py::arg("abortReason"))
        .def("GetNumPTOs", &TDR::GetNumPTOs)
        .def("GetNumAlarmObjects", &TDR::GetNumAlarmObjects)
        
        .def("SetTotalProcessingTimeInMS", &TDR::SetTotalProcessingTimeInMS, py::arg("processingTime"))
        .def("GetTotalProcessingTimeInMS", &TDR::GetTotalProcessingTimeInMS)
        
        .def("SetAdditionalInspectionCriteria", py::overload_cast<const bool, 
                                                                  const TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA,
                                                                  const DcsShortString&, 
                                                                  const DcsLongString&>
                           (&TDR::SetAdditionalInspectionCriteria), 
                           py::arg("additionalInspectionPerformed ") = false, 
                           py::arg("selectionCriteria") = TDRTypes::AdditionalInspectionSelectionCriteria::enumUnknownAdditionalInspectionSelectionCriteria,
                           py::arg("additionalInspectionMethod") = "",
                           py::arg("inspectionMethodDescription") = "")
        .def("SetAdditionalInspectionCriteria", py::overload_cast<const bool, 
                                                                  const TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA, 
                                                                  const Array1D<TDR::AdditionalInspectionData> &>
                           (&TDR::SetAdditionalInspectionCriteria),
                           py::arg("additionalInspectionPerformed"), 
                           py::arg("selectionCriteria"), 
                           py::arg("vAdditionalInspectionMethods")) 

        .def("GetAdditionalInspectionCriteria", [](TDR &self, TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA& selectionCriteria,
                                                              DcsShortString& additionalInspectionMethod,
                                                              DcsLongString& inspectionMethodDescription) {
            return std::make_tuple(self.GetAdditionalInspectionCriteria(selectionCriteria, additionalInspectionMethod, inspectionMethodDescription), selectionCriteria, additionalInspectionMethod, inspectionMethodDescription);
            }, py::arg("selectionCriteria"), py::arg("additionalInspectionMethod"), py::arg("inspectionMethodDescription"))
        
        .def("GetAdditionalInspectionCriteria", [](TDR &self, TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA& selectionCriteria,
                                                              Array1D<TDR::AdditionalInspectionData>& vAdditionalInspectionMethods) {
            return std::make_tuple(self.GetAdditionalInspectionCriteria(selectionCriteria, vAdditionalInspectionMethods), selectionCriteria, vAdditionalInspectionMethods);
            }, py::arg("selectionCriteria"), py::arg("vAdditionalInspectionMethods"));
}
