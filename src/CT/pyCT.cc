#include "../headers.hh"


 #include "SDICOS/UserCT.h"
 #include "SDICOS/ModuleCT.h"
 #include "SDICOS/Array1D.h"
 #include "SDICOS/Point3D.h"
 #include "SDICOS/TemplateCommon.h"
 #include "SDICOS/TemplateBase.h"
 #include "SDICOS/ClientManager.h"
 #include "SDICOS/MemoryPolicy.h"
 #include "SDICOS/AcquisitionContextUser.h"
 #include "SDICOS/ImageBaseUser.h"
 #include "SDICOS/XRayEquipmentUser.h"
 #include "SDICOS/FrameOfReferenceUser.h"
 
using namespace SDICOS;

PYBIND11_MAKE_OPAQUE(std::vector<CTModule*>);

class PyCT : public CT {
public:
    using CT::CT;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  CT, FreeMemory); }

    bool Read(const DicosFileListing::SopInstance& sopinstance, 
              Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, 
              IMemoryManager *pMemMgr) 
              override {PYBIND11_OVERRIDE(bool,  CT, Read, sopinstance, vErrorlogs, pMemMgr);}

    bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  CT, Read, filename, errorLog, pMemMgr);}  
    
    bool Read(MemoryFile &memfile, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  CT, Read, memfile, errorLog, pMemMgr);}  

    bool Write(const Filename &filename, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  CT, Write, filename, errorLog, nTransferSyntax);}  

    bool Write(const Filename &filenameBase, Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  CT, Write, filenameBase, vErrorlogs, nTransferSyntax);}  
  
    bool Write(MemoryFile &memfile, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  CT, Write, memfile, errorLog, nTransferSyntax);}  

    bool SendOverNetwork(const S_INT32 nPort, 
                         const DcsString &dsIP, 
                         const DcsApplicationEntity &aeSrcAppName, 
                         const DcsApplicationEntity &aeDstAppName,
                         ErrorLog &errorlog, 
                         const DcsString &dsUserID,
                         const DcsString dsPasscode)
              override {PYBIND11_OVERRIDE(bool, CT, SendOverNetwork, nPort, dsIP, aeSrcAppName, aeDstAppName, errorlog, dsUserID, dsPasscode);}  

    bool SendOverNetwork(SDICOS::Network::DcsClient &dclient, ErrorLog &errorlog)
              override {PYBIND11_OVERRIDE(bool, CT, SendOverNetwork, dclient, errorlog);}  

    S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes)
              override {PYBIND11_OVERRIDE(S_UINT32, CT, SendOverNetwork, clientManager, errorlog, vSendTimes);}  

    IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(IODCommon::MODALITY, CT, GetModality);}  

    DcsUniqueIdentifier GetSopClassUID() const
              override {PYBIND11_OVERRIDE(DcsUniqueIdentifier, CT, GetSopClassUID);}
};


void export_CT(py::module &m)
{
    py::enum_<ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE>(m, "OBJECT_OF_INSPECTION_TYPE")
        .value("enumUnknownObjectOfInspectionType", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumUnknownObjectOfInspectionType)
        .value("enumTypeBioSample", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBioSample)
        .value("enumTypeCargo", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeCargo)
        .value("enumTypeBaggage", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBaggage)
        .value("enumTypeAnimal", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeAnimal)
        .value("enumTypeOther", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeOther)
        .value("enumTypePerson", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypePerson)
        .export_values();

    py::enum_<CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS>(m, "OOI_IMAGE_CHARACTERISTICS")
        .value("enumUnknownOOIImageCharacteristics", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumUnknownOOIImageCharacteristics)
        .value("enumHighEnergy", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumHighEnergy)
        .value("enumLowEnergy", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumLowEnergy)
        .value("enumZ_Effective", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumZ_Effective)
        .value("enumBasisMaterial_1", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumBasisMaterial_1)
        .value("enumBasisMaterial_2", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumBasisMaterial_2)
        .value("enumCompton", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumCompton)
        .value("enumPhotoelectric", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumPhotoelectric)
        .value("enumDensity", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumDensity)
        .value("enumIntensity", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumIntensity)
        .value("enumMu", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumMu)
        .value("enumMultiEnergy", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumMultiEnergy)
        .export_values();

    py::enum_<CTTypes::CTImage::IMAGE_FLAVOR>(m, "IMAGE_FLAVOR")
        .value("enumUnknownImageFlavor", CTTypes::CTImage::IMAGE_FLAVOR::enumUnknownImageFlavor)
        .value("enumProjection", CTTypes::CTImage::IMAGE_FLAVOR::enumProjection)
        .value("enumVolume", CTTypes::CTImage::IMAGE_FLAVOR::enumVolume)
        .export_values();

    py::enum_<ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>(m, "PHOTOMETRIC_INTERPRETATION")
        .value("enumUnknownPhotometricInterpretation", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumUnknownPhotometricInterpretation)
        .value("enumMonochrome1", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumMonochrome1)
        .value("enumMonochrome2", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumMonochrome2)
        .value("enumPaletteColor", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumPaletteColor)
        .value("enumRGB", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumRGB)
        .value("enumYBR_Full", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Full)
        .value("enumYBR_Full_422", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Full_422)
        .value("enumYBR_Partial_422", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Partial_422)
        .value("enumYBR_Partial_420", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Partial_420)
        .value("enumYBR_ICT", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_ICT)
        .value("enumYBR_RCT", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_RCT)
        .export_values();

    py::enum_<DicosFile::TRANSFER_SYNTAX>(m, "TRANSFER_SYNTAX")
        .value("enumLittleEndianExplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicit)
        .value("enumLittleEndianExplicitExtended", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicitExtended)
        .value("enumLittleEndianImplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianImplicit)
        .value("enumLosslessJPEG", DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .value("enumLosslessRLE", DicosFile::TRANSFER_SYNTAX::enumLosslessRLE)
        .export_values();

    py::enum_<MemoryPolicy::VOLUME_MEMORY_POLICY>(m, "VOLUME_MEMORY_POLICY")
        .value("DOES_NOT_OWN_SLICES", MemoryPolicy::VOLUME_MEMORY_POLICY::DOES_NOT_OWN_SLICES)
        .value("OWNS_SLICES", MemoryPolicy::VOLUME_MEMORY_POLICY::OWNS_SLICES)
        .value("DOES_NOT_OWN_DATA", MemoryPolicy::VOLUME_MEMORY_POLICY::DOES_NOT_OWN_DATA)
        .value("OWNS_DATA", MemoryPolicy::VOLUME_MEMORY_POLICY::OWNS_DATA)
        .value("MEMORY_POLICY_UNKNOWN", MemoryPolicy::VOLUME_MEMORY_POLICY::MEMORY_POLICY_UNKNOWN)
        .export_values();
    
    py::enum_<Array3DLargeBase::ADD_SLICE_FAILURE_POLICY>(m, "ADD_SLICE_FAILURE_POLICY")
        .value("EARLY_OUT", Array3DLargeBase::ADD_SLICE_FAILURE_POLICY::EARLY_OUT)
        .value("SKIP_AND_CONTINUE", Array3DLargeBase::ADD_SLICE_FAILURE_POLICY::SKIP_AND_CONTINUE)
        .value("ADD_DEBUG_SLICE", Array3DLargeBase::ADD_SLICE_FAILURE_POLICY::ADD_DEBUG_SLICE)
        .export_values();

    py::enum_<ITERATION_DIRECTION>(m, "ITERATION_DIRECTION")
        .value("ITERATION_DIRECTION_FORWARD", ITERATION_DIRECTION::ITERATION_DIRECTION_FORWARD)
        .value("ITERATION_DIRECTION_BACKWARD", ITERATION_DIRECTION::ITERATION_DIRECTION_BACKWARD)
        .value("ITERATION_END", ITERATION_DIRECTION::ITERATION_END)
        .export_values();

    py::enum_<GeneralScanModule::SCAN_TYPE>(m, "SCAN_TYPE")
        .value("enumUnknownScanType", GeneralScanModule::enumUnknownScanType)
        .value("enumOperational", GeneralScanModule::enumOperational)
        .value("enumNonOperational", GeneralScanModule::enumNonOperational)
        .export_values();


    py::class_<CT::Iterator>(m, "Iterator")
        .def_property_readonly_static("ITERATION_DIRECTION", [m](py::object) {
            return m.attr("ITERATION_DIRECTION");
        })  
        .def(py::init<>())
        .def(py::init<const CT&, const ITERATION_DIRECTION>(), 
                      py::arg("ct"), 
                      py::arg("dir") = ITERATION_DIRECTION::ITERATION_DIRECTION_FORWARD)
        .def("__copy__", [](const CT::Iterator &self) { return CT::Iterator(self); })
        .def("__deepcopy__", [](const CT::Iterator &self, py::dict) { return CT::Iterator(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__next__", (CT::Iterator& (CT::Iterator::*)()) &CT::Iterator::operator++, py::return_value_policy::reference_internal)
        .def("deref", (const Section* (CT::Iterator::*)() const) &CT::Iterator::operator*, py::return_value_policy::reference_internal)
        .def("deref", (Section* (CT::Iterator::*)()) &CT::Iterator::operator*, py::return_value_policy::reference_internal)
        .def("GetIndex", &CT::Iterator::GetIndex);

    py::class_<IODCommon>(m, "IODCommon");
    py::class_<ScanCommon>(m, "ScanCommon");
    py::class_<AcquisitionContextUser>(m, "AcquisitionContextUser");
    py::class_<XRayEquipmentUser>(m, "XRayEquipmentUser");
    py::class_<ImageCommonUser>(m, "ImageCommonUser");
    py::class_<FrameOfReferenceUser>(m, "FrameOfReferenceUser");
    py::class_<CT>(m, "SDICOS::CT");
    py::class_<PyCT, CT, IODCommon, 
                         ScanCommon, 
                         AcquisitionContextUser, 
                         XRayEquipmentUser, 
                         ImageCommonUser, 
                         FrameOfReferenceUser>(m, "CT")
        .def(py::init<>())
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS, 
                      const CTTypes::CTImage::IMAGE_FLAVOR, 
                      const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>(), 
                       py::arg("nOOIType"), 
                       py::arg("nOOI"), 
                       py::arg("nFlavor") = CTTypes::CTImage::enumVolume, 
                       py::arg("nPI") = ImagePixelMacro::enumMonochrome2)

        .def_property_readonly_static("OBJECT_OF_INSPECTION_TYPE", [m](py::object) {
            return m.attr("OBJECT_OF_INSPECTION_TYPE");
        })  

        .def_property_readonly_static("OOI_IMAGE_CHARACTERISTICS", [m](py::object) {
            return m.attr("OOI_IMAGE_CHARACTERISTICS");
        }) 

        .def_property_readonly_static("IMAGE_FLAVOR", [m](py::object) {
            return m.attr("IMAGE_FLAVOR");
        }) 

        .def_property_readonly_static("PHOTOMETRIC_INTERPRETATION", [m](py::object) {
            return m.attr("PHOTOMETRIC_INTERPRETATION");
        })   

        .def_property_readonly_static("ADD_SLICE_FAILURE_POLICY", [m](py::object) {
            return m.attr("ADD_SLICE_FAILURE_POLICY");
        })  
        .def_property_readonly_static("VOLUME_MEMORY_POLICY", [m](py::object) {
            return m.attr("VOLUME_MEMORY_POLICY");
        })        
        .def_property_readonly_static("TRANSFER_SYNTAX", [m](py::object) {
            return m.attr("TRANSFER_SYNTAX");
        })     
        .def_property_readonly_static("SCAN_TYPE", [m](py::object) {
            return m.attr("SCAN_TYPE");
        })   
        .def("__copy__", [](const CT &self) { return CT(self); })
        .def("__deepcopy__", [](const CT &self, py::dict) { return CT(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Initialize", py::overload_cast<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                                             const CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS, 
                                             const CTTypes::CTImage::IMAGE_FLAVOR, 
                                             const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>
                           (&PyCT::Initialize), 
                           py::arg("nOOIType"), 
                           py::arg("nOOI"),
                           py::arg("nFlavor") = CTTypes::CTImage::enumVolume, 
                           py::arg("nPI") = ImagePixelMacro::enumMonochrome2)
        .def("Initialize", py::overload_cast<std::vector<CTModule*>&, 
                                             ErrorLog&, 
                                             bool>
                           (&PyCT::Initialize),
                           py::arg("vSeries"), 
                           py::arg("errorlog"), 
                           py::arg("bMoveData"))
        .def("Read", py::overload_cast<const DicosFileListing::SopInstance&, 
                                             Array1D< std::pair<Filename, ErrorLog> >&, 
                                             IMemoryManager*>
                     (&PyCT::Read), 
                     py::arg("sopinstance"), 
                     py::arg("vErrorlogs"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<const Filename&, 
                                       ErrorLog&, 
                                       IMemoryManager*>
                     (&PyCT::CT::Read),
                     py::arg("filename"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<MemoryFile&, 
                                       ErrorLog& , 
                                       IMemoryManager*>
                     (&PyCT::CT::Read),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)       

        .def("Write", py::overload_cast<const Filename&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX>
                     (&PyCT::CT::Write, py::const_), 
                     py::arg("filename"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<const Filename&, 
                                        Array1D< std::pair<Filename, ErrorLog> > &, 
                                        const DicosFile::TRANSFER_SYNTAX>
                     (&PyCT::CT::Write, py::const_),
                     py::arg("filenameBase"), 
                     py::arg("vErrorlogs"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<MemoryFile&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX>
                     (&PyCT::CT::Write, py::const_),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)

        .def("SendOverNetwork", py::overload_cast<const S_INT32, 
                                                  const DcsString&, 
                                                  const DcsApplicationEntity&,
                                                  const DcsApplicationEntity&,
                                                  ErrorLog&,
                                                  const DcsString&,
                                                  const DcsString>
                     (&PyCT::CT::SendOverNetwork), 
                     py::arg("nPort"), 
                     py::arg("dsIP"),
                     py::arg("aeSrcAppName"),
                     py::arg("aeDstAppName"), 
                     py::arg("errorlog"),
                     py::arg("dsUserID") = "",
                     py::arg("dsPasscode") = "")
        .def("SendOverNetwork", py::overload_cast<SDICOS::Network::DcsClient&, ErrorLog&>
                     (&PyCT::CT::SendOverNetwork), 
                     py::arg("dclient"), 
                     py::arg("errorlog"))
        .def("SendOverNetwork", py::overload_cast<SDICOS::Network::DcsClientManager&, ErrorLog&, std::vector< Network::DcsClientManager::ClientMetrics >&>
                     (&PyCT::CT::SendOverNetwork), 
                     py::arg("clientManager"), 
                     py::arg("errorlog"),
                     py::arg("vSendTimes"))

        .def("GetModality", py::overload_cast<>(&PyCT::CT::GetModality, py::const_))
        .def("FreeMemory", py::overload_cast<>(&PyCT::CT::FreeMemory))
        .def("GetNumberOfFilesToCreate", &CT::GetNumberOfFilesToCreate)
        .def("SetImageAcquisitionDateAndTime", &CT::SetImageAcquisitionDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("GetImageAcquisitionDate", &CT::GetImageAcquisitionDate)
        .def("GetImageAcquisitionTime", &CT::GetImageAcquisitionTime)
        .def("SetBurnedInAnnotation", &CT::SetBurnedInAnnotation, py::arg("bUsesAnnotation"))
        .def("HasBurnedInAnnotation", &CT::HasBurnedInAnnotation)
        .def("SetPhotometricInterpretation", &CT::SetPhotometricInterpretation, py::arg("nPI"))
        .def("GetPhotometricInterpretation", &CT::GetPhotometricInterpretation) 
        .def("SetImageType", &CT::SetImageType, py::arg("nOOI"), py::arg("nFlavor") = CTTypes::CTImage::enumVolume)
        .def("GetImageType", &CT::GetImageType, py::arg("nOOI"), py::arg("nFlavor")) 
        .def("GetOOIImageCharacteristics", &CT::GetOOIImageCharacteristics)
        .def("GetImageFlavor", &CT::GetImageFlavor) 
        .def("SetSDI", &CT::SetSDI)
        .def("IsSDI", &CT::IsSDI) 
        .def("SetCDI", &CT::SetCDI)
        .def("IsCDI", &CT::IsCDI) 
        .def("SetStandard", &CT::SetStandard) 
        .def("IsStandard", &CT::IsStandard) 
        .def("SetImageAcquisitionDuration", &CT::SetImageAcquisitionDuration, py::arg("nAcquisitionDuration"))
        .def("GetImageAcquisitionDuration", &CT::GetImageAcquisitionDuration) 
        .def("SetContentDateAndTime", &CT::SetContentDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("GetContentDate", &CT::GetContentDate) 
        .def("GetContentTime", &CT::GetContentTime) 
        .def("SetInstanceNumber", &CT::SetInstanceNumber, py::arg("nInstanceNumber"))
        .def("GetInstanceNumber", &CT::GetInstanceNumber) 
        .def("SetNumberOfSections", &CT::SetNumberOfSections, py::arg("nNum"))
        .def("GetNumberOfSections", &CT::GetNumberOfSections) 
        .def("GetSopClassUID", py::overload_cast<>(&PyCT::CT::GetSopClassUID, py::const_))
        .def("AddSection", (Section*(CT::*)())&PyCT::AddSection)
        .def("AddSection", (Section*(CT::*)(const S_UINT32, 
                                            const S_UINT32, 
                                            const S_UINT32, 
                                            const Volume::IMAGE_DATA_TYPE))&PyCT::AddSection, 
                                            py::arg("nWidth"), 
                                            py::arg("nHeight"), 
                                            py::arg("nDepth"), 
                                            py::arg("nDataType"), 
                                            py::return_value_policy::reference_internal)
        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT8> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)
        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT8> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection,  
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)
        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT8> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)
        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT16> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)


        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT16> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)


        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT32> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection,  
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT32> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection,  
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT64> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT64> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Array3DLarge<float> &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Volume &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY,
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection,  
                                             py::arg("vol"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT8>::Iterator &, 
                                             const Array3DLarge<S_INT8>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)   

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT8>::Iterator &, 
                                             const Array3DLarge<S_UINT8>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)      

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT16>::Iterator &, 
                                             const Array3DLarge<S_INT16>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)      

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT16>::Iterator &, 
                                             const Array3DLarge<S_UINT16>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)     

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT32>::Iterator &, 
                                             const Array3DLarge<S_INT32>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)     

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT32>::Iterator &, 
                                             const Array3DLarge<S_UINT32>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)     

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_INT64>::Iterator &, 
                                             const Array3DLarge<S_INT64>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)     

        .def("AddSection", (Section*(CT::*)(Array3DLarge<S_UINT64>::Iterator &, 
                                             const Array3DLarge<S_UINT64>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection,
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)     

        .def("AddSection", (Section*(CT::*)(Array3DLarge<float>::Iterator &, 
                                             const Array3DLarge<float>::Iterator &, 
                                             const MemoryPolicy::VOLUME_MEMORY_POLICY, 
                                             const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY))&PyCT::AddSection, 
                                             py::arg("itStart"), 
                                             py::arg("itEnd"), 
                                             py::arg("nMemPolicy") = MemoryPolicy::OWNS_SLICES, 
                                             py::arg("nFailurePolicy") = Array3DLargeBase::EARLY_OUT, 
                                             py::return_value_policy::reference_internal)
                                     
        .def("SetScanDescription", &IODCommon::SetScanDescription, py::arg("strDescription"))
        .def("GetSectionByIndex", py::overload_cast<const S_UINT32>(&PyCT::CT::GetSectionByIndex), 
                                  py::arg("nSectionIndex"), 
                                  py::return_value_policy::reference_internal)
        .def("GetSectionByIndex", py::overload_cast<const S_UINT32>(&PyCT::CT::GetSectionByIndex, py::const_), 
                                  py::arg("nSectionIndex"), 
                                  py::return_value_policy::reference_internal)

        .def("Begin", &CT::Begin)
        .def("End", &CT::End)

        .def("SetOOIID", &IODCommon::SetOOIID, py::arg("strID"))
        .def("GetOOIID", &IODCommon::GetOOIID)
        .def("SetOOIIDType", &IODCommon::SetOOIIDType, py::arg("nType"))
        .def("GetOOIIDType", &IODCommon::GetOOIIDType)
        .def("SetOOIType", &IODCommon::SetOOIType, py::arg("nType"))
        .def("GetOOIType", &IODCommon::GetOOIType)
        .def("GenerateSopInstanceUID", &IODCommon::GenerateSopInstanceUID)
        .def("GenerateScanInstanceUID", &IODCommon::GenerateScanInstanceUID)
        .def("GenerateSeriesInstanceUID", &IODCommon::GenerateSeriesInstanceUID)
        .def("SetOOIIDAssigningAuthority", &IODCommon::SetOOIIDAssigningAuthority, py::arg("strAssigningAuthority"))
        .def("GetOOIIDAssigningAuthority", &IODCommon::GetOOIIDAssigningAuthority)
        .def("SetScanID", &IODCommon::SetScanID, py::arg("strID"))
        .def("GetScanID", &IODCommon::GetScanID)
        .def("SetSeriesDateAndTime", &IODCommon::SetSeriesDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("SetSeriesAcquisitionStatus", &IODCommon::SetSeriesAcquisitionStatus, py::arg("nStatus"))
        .def("SetDeviceCalibrationDateAndTime", &IODCommon::SetDeviceCalibrationDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("SetSopInstanceCreationDateAndTime", &IODCommon::SetSopInstanceCreationDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("SetDeviceSerialNumber", &IODCommon::SetDeviceSerialNumber, py::arg("strSerialNumber"))
        .def("SetMachineAddress", &IODCommon::SetMachineAddress, py::arg("strMachineAddress"))
        .def("SetMachineLocation", &IODCommon::SetMachineLocation, py::arg("strMachineLocation"))
        .def("SetMachineID", &IODCommon::SetMachineID, py::arg("strMachineID"))
        .def("SetDeviceManufacturer", &IODCommon::SetDeviceManufacturer, py::arg("strManufacturer"))
        .def("SetDeviceSoftwareVersion", &IODCommon::SetDeviceSoftwareVersion, py::arg("strSoftwareVersion"))
        .def("SetDeviceManufacturerModelName", &IODCommon::SetDeviceManufacturerModelName, py::arg("strModelName"))
        .def("SetScanInstanceUID", &IODCommon::SetScanInstanceUID, py::arg("strScanUID"))
        .def("GetScanInstanceUID", &IODCommon::GetScanInstanceUID)
        .def("SetSeriesInstanceUID", &IODCommon::SetSeriesInstanceUID, py::arg("strUID"))
        .def("GetSeriesInstanceUID", &IODCommon::GetSeriesInstanceUID)
        .def("GetFrameOfReferenceUID", &FrameOfReferenceUser::GetFrameOfReferenceUID)
        .def("GetSopInstanceUID", &IODCommon::GetSopInstanceUID)
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
        .def("SetFrameOfReferenceUID", &FrameOfReferenceUser::SetFrameOfReferenceUID);
}