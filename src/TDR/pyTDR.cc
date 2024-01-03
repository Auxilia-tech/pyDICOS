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
        .value("enumUnknownObjectOfInspectionIdType", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumUnknownObjectOfInspectionIdType)
        .value("enumText", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumText)
        .value("enumRFID", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumRFID)
        .value("enumBarcode", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumBarcode)
        .value("enumMRP", ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE::enumMRP)
        .export_values();

    py::enum_<TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA>(m, "ADDITIONAL_INSPECTION_SELECTION_CRITERIA")
        .value("enumRandom", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumRandom)
        .value("enumBehavioral", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumBehavioral)
        .value("enumAll", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumAll)
        .value("enumOwnerRisk", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumOwnerRisk)
        .value("enumFlightRisk", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumFlightRisk)
        .value("enumThreatLevel", TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA::enumThreatLevel)
        .export_values();

    py::enum_<TDRTypes::ThreatDetectionReport::ALARM_DECISION>(m, "ALARM_DECISION")
        .value("enumUnknownAlarmDecision", TDRTypes::ThreatDetectionReport::ALARM_DECISION::enumUnknownAlarmDecision)
        .value("enumAlarm", TDRTypes::ThreatDetectionReport::ALARM_DECISION::enumAlarm)
        .value("enumClear", TDRTypes::ThreatDetectionReport::ALARM_DECISION::enumClear)
        .export_values();

    py::enum_<TDRTypes::ThreatDetectionReport::ABORT_FLAG>(m, "ABORT_FLAG")
        .value("enumUnknownAbortFlag", TDRTypes::ThreatDetectionReport::ABORT_FLAG::enumUnknownAbortFlag)
        .value("enumAbort", TDRTypes::ThreatDetectionReport::ABORT_FLAG::enumAbort)
        .value("enumSuccess", TDRTypes::ThreatDetectionReport::ABORT_FLAG::enumSuccess)
        .export_values();

    py::enum_<TDR::ThreatType>(m, "ThreatType")
        .value("enumThreatTypeUnknown", TDR::ThreatType::enumThreatTypeUnknown)
        .value("enumThreatTypePerson", TDR::ThreatType::enumThreatTypePerson)
        .value("enumThreatTypeBaggage", TDR::ThreatType::enumThreatTypeBaggage)
        .export_values();

    py::enum_<TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY>(m, "THREAT_CATEGORY")
        .value("enumUnknownThreatCategory", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumUnknownThreatCategory)
        .value("enumExplosive", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumExplosive)
        .value("enumProhibitedItem", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumProhibitedItem)
        .value("enumContraband", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumContraband)
        .value("enumAnomaly", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumAnomaly)
        .value("enumLaptop", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumLaptop)
        .value("enumOther", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumOther)
        .value("enumPharmaceutical", TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY::enumPharmaceutical)
        .export_values();

    py::enum_<TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT>(m, "ABILITY_ASSESSMENT")
        .value("enumUnknownAbilityAssessment", TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT::enumUnknownAbilityAssessment)
        .value("enumNoInterference", TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT::enumNoInterference)
        .value("enumShield", TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT::enumShield)
        .export_values();

    py::enum_<TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG>(m, "ASSESSMENT_FLAG")
        .value("enumUnknownAssessmentFlag", TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG::enumUnknownAssessmentFlag)
        .value("enumHighThreat", TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG::enumHighThreat)
        .value("enumThreat", TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG::enumThreat)
        .value("enumNoThreat", TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG::enumNoThreat)
        .value("enumUnknown", TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG::enumUnknown)
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
        .def_property_readonly_static("ALARM_DECISION", [m](py::object) {
            return m.attr("ALARM_DECISION");
        }) 
        .def_property_readonly_static("ABORT_FLAG", [m](py::object) {
            return m.attr("ABORT_FLAG");
        }) 
        .def_property_readonly_static("ThreatType", [m](py::object) {
            return m.attr("ThreatType");
        }) 
        .def_property_readonly_static("THREAT_CATEGORY", [m](py::object) {
            return m.attr("THREAT_CATEGORY");
        }) 
        .def_property_readonly_static("ABILITY_ASSESSMENT", [m](py::object) {
            return m.attr("ABILITY_ASSESSMENT");
        }) 
        .def_property_readonly_static("ASSESSMENT_FLAG", [m](py::object) {
            return m.attr("ASSESSMENT_FLAG");
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


        .def("SetThreatRegionOfInterest", &TDR::SetThreatRegionOfInterest, 
                                          py::arg("PTOIdentifier"), 
                                          py::arg("ptoBase"),
                                          py::arg("ptoExtents"), 
                                          py::arg("ptoMask"), 
                                          py::arg("nRepresentation"))
        
        .def("GetThreatRegionOfInterest", [](TDR &self, const S_UINT16 PTOIdentifier, 
                                                        Point3D<float>& PTOBase, 
                                                        Point3D<float>& PTOExtents, 
                                                        Bitmap& bitmap, 
                                                        const S_UINT16 nRepresentation) {
            return std::make_tuple(self.GetThreatRegionOfInterest(PTOIdentifier, PTOBase, PTOExtents, bitmap, nRepresentation), PTOBase, PTOExtents, bitmap);
            }, py::arg("PTOIdentifier"), py::arg("PTOBase"), py::arg("PTOExtents"), py::arg("bitmap"), py::arg("nRepresentation"))
  
        
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
            }, py::arg("selectionCriteria"), py::arg("vAdditionalInspectionMethods"))

        .def("AddPotentialThreatObject", &TDR::AddPotentialThreatObject, 
                                          py::arg("PTOIdentifier"), 
                                          py::arg("threatType"),  
                                          py::arg("nNumPTORepresentations") = 1)

        .def("AddPTOAssessment", &TDR::AddPTOAssessment, 
                                  py::arg("PTOIdentifier"), 
                                  py::arg("assessmentFlag") = TDRTypes::AssessmentSequence::AssessmentItem::enumUnknown,  
                                  py::arg("threatCategory") = TDRTypes::AssessmentSequence::AssessmentItem::enumAnomaly,
                                  py::arg("ability") = TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference, 
                                  py::arg("threatDescription") = "",
                                  py::arg("assessmentProbability") = -10.f)
        
        .def("SetBaggagePTODetails", &TDR::SetBaggagePTODetails, 
                              py::arg("PTOIdentifier"), 
                              py::arg("PTOMassInGrams"),
                              py::arg("PTODensityInGramsPerCC"),
                              py::arg("nRepresentation"))

        .def("GetBaggagePTODetails", [](TDR &self, S_UINT16 PTOIdentifier, 
                                                   float& PTOMass, 
                                                   float& PTODensity, 
                                                   const S_UINT16 nRepresentation) {
            return std::make_tuple(self.GetBaggagePTODetails(PTOIdentifier, PTOMass, PTODensity, nRepresentation), PTOMass, PTODensity);
            }, py::arg("PTOIdentifier"), py::arg("PTOMass"), py::arg("PTODensity"), py::arg("nRepresentation"))

        .def("AddReferencedSopInstance", &IODCommon::AddReferencedSopInstance, 
                                          py::arg("strSopInstanceUID"), 
                                          py::arg("strSopClassUID"))

        .def("SetPTOProcessingTime", &TDR::SetPTOProcessingTime, 
                              py::arg("PTOIdentifier"), 
                              py::arg("dtStart"),
                              py::arg("dtEnd"),
                              py::arg("fTotalTimeMS"))

        .def("GetPTOProcessingTime", [](TDR &self,const S_UINT16 PTOIdentifier,
                                                  SDICOS::DcsDateTime &dtStart,
                                                  SDICOS::DcsDateTime &dtEnd,
                                                  float &fTotalTimeMS) {
            return std::make_tuple(self.GetPTOProcessingTime(PTOIdentifier, dtStart, dtEnd, fTotalTimeMS), dtStart, dtEnd);
            }, py::arg("PTOIdentifier"), py::arg("dtStart"), py::arg("dtEnd"), py::arg("fTotalTimeMS"))

        .def("AddReferencedInstance", &TDR::AddReferencedInstance, 
                              py::arg("PTOIdentifier"), 
                              py::arg("referencedSopClassUID"),
                              py::arg("referencedSopInstanceUID"),
                              py::arg("nRepresentation"))


        .def("SetOOIID", &TDR::SetOOIID, py::arg("strID"))
        .def("GetOOIID", &TDR::GetOOIID)

        .def("SetOOIIDAssigningAuthority", &TDR::SetOOIIDAssigningAuthority, py::arg("strAssigningAuthority"))
        .def("GetOOIIDAssigningAuthority", &TDR::GetOOIIDAssigningAuthority)

        .def("SetOOIIDType", &TDR::SetOOIIDType, py::arg("nType"))
        .def("GetOOIIDType", &TDR::GetOOIIDType)
        .def("SetOOIType", &IODCommon::SetOOIType, py::arg("nType"))
        .def("SetThreatBoundingPolygon", &TDR::SetThreatBoundingPolygon, py::arg("PTOIdentifier"), py::arg("controlPoints"), py::arg("nRepresentation"))
        .def("SetScanInstanceUID", &IODCommon::SetScanInstanceUID, py::arg("strScanUID"))
        .def("GetScanInstanceUID", &IODCommon::GetScanInstanceUID)
        .def("SetSeriesInstanceUID", &IODCommon::SetSeriesInstanceUID, py::arg("strUID"))
        .def("GetSeriesInstanceUID", &IODCommon::GetSeriesInstanceUID)
        .def("GenerateSopInstanceUID", &IODCommon::GenerateSopInstanceUID)
        .def("SetFrameOfReferenceUID", &FrameOfReferenceUser::SetFrameOfReferenceUID, py::arg("strFrameOfReferenceUID"))
        .def("GetFrameOfReferenceUID", &FrameOfReferenceUser::GetFrameOfReferenceUID)
        .def("GetSopInstanceUID", &IODCommon::GetSopInstanceUID)
        .def("SetBaggagePTOLocationDescription", &TDR::SetBaggagePTOLocationDescription, py::arg("PTOIdentifier"), py::arg("dsDescription"), py::arg("nRepresentation"))
        .def("SetProcessingStartTime", &TDR::SetProcessingStartTime, py::arg("PTOIdentifier"), py::arg("startTime"))
        .def("SetProcessingEndTime", &TDR::SetProcessingEndTime, py::arg("PTOIdentifier"), py::arg("endTime"))
        .def("SetScanID", &IODCommon::SetScanID, py::arg("strID"))
        .def("SetScanStartDateAndTime", &IODCommon::SetScanStartDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("GetScanStartDate", &IODCommon::GetScanStartDate)
        .def("GetScanStartTime", &IODCommon::GetScanStartTime)
        .def("SetScanType", &IODCommon::SetScanType, py::arg("nType"))
        .def("GetScanType", &IODCommon::GetScanType)
        .def("SetSeriesDateAndTime", &IODCommon::SetSeriesDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("GetSeriesDate", &IODCommon::GetSeriesDate)
        .def("GetSeriesTime", &IODCommon::GetSeriesTime)
        .def("SetSeriesAcquisitionStatus", &IODCommon::SetSeriesAcquisitionStatus, py::arg("nStatus"))
        .def("GetSeriesAcquisitionStatus", &IODCommon::GetSeriesAcquisitionStatus)
        .def("SetDeviceCalibrationDateAndTime", &IODCommon::SetDeviceCalibrationDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("SetDeviceSerialNumber", &IODCommon::SetDeviceSerialNumber, py::arg("strSerialNumber"))
        .def("SetMachineAddress", &IODCommon::SetMachineAddress, py::arg("strMachineAddress"))
        .def("SetMachineLocation", &IODCommon::SetMachineLocation, py::arg("strMachineLocation"))
        .def("SetMachineID", &IODCommon::SetMachineID, py::arg("strMachineID"))
        .def("SetDeviceManufacturer", &IODCommon::SetDeviceManufacturer, py::arg("strManufacturer"))
        .def("SetDeviceSoftwareVersion", &IODCommon::SetDeviceSoftwareVersion, py::arg("strSoftwareVersion"))
        .def("SetDeviceManufacturerModelName", &IODCommon::SetDeviceManufacturerModelName, py::arg("strModelName"))
        .def("SetSopInstanceCreationDateAndTime", &IODCommon::SetSopInstanceCreationDateAndTime, py::arg("strDate"), py::arg("strTime"));
}