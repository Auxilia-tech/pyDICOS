#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

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
#include <map>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<SDICOS::CTModule*>);


class PySection : public SDICOS::Section {
public:
    using SDICOS::Section::Section;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  SDICOS::Section, FreeMemory, ); }
};

float GetFocalSpotSizeFloat(const SDICOS::Section &self) {
    return self.GetFocalSpotSize();
}

void GetFocalSpotSizePair(const SDICOS::Section &self, float &fSmallSize, float &fLargeSize) {
    self.GetFocalSpotSize(fSmallSize, fLargeSize);
}


class PyCT : public SDICOS::CT {
public:
    using SDICOS::CT::CT;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  SDICOS::CT, FreeMemory); }

    bool Read(const SDICOS::DicosFileListing::SopInstance& sopinstance, 
              SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> > &vErrorlogs, 
              SDICOS::IMemoryManager *pMemMgr) 
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Read, sopinstance, vErrorlogs, pMemMgr);}

    bool Read(const SDICOS::Filename &filename, SDICOS::ErrorLog& errorLog, SDICOS::IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Read, filename, errorLog, pMemMgr);}  
    
    bool Read(SDICOS::MemoryFile &memfile, SDICOS::ErrorLog& errorLog, SDICOS::IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Read, memfile, errorLog, pMemMgr);}  

    bool Write(const SDICOS::Filename &filename, SDICOS::ErrorLog& errorLog, const SDICOS::DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Write, filename, errorLog, nTransferSyntax);}  

    bool Write(const SDICOS::Filename &filenameBase, SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> > &vErrorlogs, const SDICOS::DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Write, filenameBase, vErrorlogs, nTransferSyntax);}  
  
    bool Write(SDICOS::MemoryFile &memfile, SDICOS::ErrorLog& errorLog, const SDICOS::DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  SDICOS::CT, Write, memfile, errorLog, nTransferSyntax);}  

    SDICOS::IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(SDICOS::IODCommon::MODALITY, SDICOS::CT, GetModality);}  

    SDICOS::DcsUniqueIdentifier GetSopClassUID() const
              override {PYBIND11_OVERRIDE(SDICOS::DcsUniqueIdentifier, SDICOS::CT, GetSopClassUID);}  
};


PYBIND11_MODULE(CT, m) {
    py::class_<PySection, SDICOS::Section, SDICOS::SectionCommon>(m, "Section")
        .def(py::init<>())
        .def(py::init<const SDICOS::S_UINT32>(), py::arg("sectionId"))
        .def("__copy__", [](const SDICOS::Section &self) { return SDICOS::Section(self); })
        .def("__deepcopy__", [](const SDICOS::Section &self, py::dict) { return SDICOS::Section(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("SetImagePixelPresentation", &SDICOS::Section::SetImagePixelPresentation)
        .def("SetImagePixelPresentation", &SDICOS::Section::SetImagePixelPresentation, py::arg("nPresentation"))
        .def("GetImagePixelPresentation", &SDICOS::Section::GetImagePixelPresentation)
        .def("SetImageVolumeBasedCalculationTechnique", &SDICOS::Section::SetImageVolumeBasedCalculationTechnique, py::arg("nTechnique"))
        .def("GetImageVolumeBasedCalculationTechnique", &SDICOS::Section::GetImageVolumeBasedCalculationTechnique)
        .def("SetImageVolumetricProperties", &SDICOS::Section::SetImageVolumetricProperties,  py::arg("nProperties"))
        .def("GetImageVolumetricProperties", &SDICOS::Section::GetImageVolumetricProperties)
        .def("SetRescaleSlope", &SDICOS::Section::SetRescaleSlope,  py::arg("fSlope"))
        .def("GetRescaleSlope", &SDICOS::Section::GetRescaleSlope)
        .def("SetRescaleIntercept", &SDICOS::Section::SetRescaleIntercept,  py::arg("fIntercept"))
        .def("GetRescaleIntercept", &SDICOS::Section::GetRescaleIntercept)
        .def("SetRescaleType", &SDICOS::Section::SetRescaleType, py::arg("strType"))
        .def("GetRescaleType", &SDICOS::Section::GetRescaleType, py::return_value_policy::reference)
        .def("SetFilterMaterial", &SDICOS::Section::SetFilterMaterial,  py::arg("nFilterMaterial"))
        .def("GetFilterMaterial", &SDICOS::Section::GetFilterMaterial)
        .def("SetFilterMaterials", &SDICOS::Section::SetFilterMaterials,  py::arg("vFilterMaterial"))
        .def("GetFilterMaterials", &SDICOS::Section::GetFilterMaterials)
        .def("SetFilterType", &SDICOS::Section::SetFilterType,  py::arg("nFilterType"))
        .def("GetFilterType", &SDICOS::Section::GetFilterType)
        .def("SetFocalSpotSizeInMM", &SDICOS::Section::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"))
        .def("GetFocalSpotSize", &GetFocalSpotSizeFloat, "Get the focal spot size")
        .def("HasOneFocalSpotSize", &SDICOS::Section::HasOneFocalSpotSize)
        .def("SetFocalSpotSizesInMM", &SDICOS::Section::SetFocalSpotSizesInMM, py::arg("fSmallSize"), py::arg("fLargeSize"))
        .def("GetFocalSpotSize", &GetFocalSpotSizePair, "Get the focal spot size as a pair of small and large sizes")
        .def("GetFocalSpotSmallSize", &SDICOS::Section::GetFocalSpotSmallSize)
        .def("GetFocalSpotLargeSize", &SDICOS::Section::GetFocalSpotLargeSize)
        .def("HasTwoFocalSpotSizes", &SDICOS::Section::HasTwoFocalSpotSizes)
        .def("SetKVP", &SDICOS::Section::SetKVP, py::arg("fKVP"))
        .def("GetKVP", &SDICOS::Section::GetKVP)
        .def("ApplyRescaleToImage", &SDICOS::Section::ApplyRescaleToImage)
        .def("FreeMemory", &PySection::FreeMemory);

    py::enum_<SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE>(m, "OBJECT_OF_INSPECTION_TYPE")
        .value("enumUnknownObjectOfInspectionType", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumUnknownObjectOfInspectionType)
        .value("enumTypeBioSample", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBioSample)
        .value("enumTypeCargo", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeCargo)
        .value("enumTypeBaggage", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBaggage)
        .value("enumTypeAnimal", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeAnimal)
        .value("enumTypeOther", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeOther)
        .value("enumTypePerson", SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypePerson);

    py::enum_<SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS>(m, "OOI_IMAGE_CHARACTERISTICS")
        .value("enumUnknownOOIImageCharacteristics", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumUnknownOOIImageCharacteristics)
        .value("enumHighEnergy", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumHighEnergy)
        .value("enumLowEnergy", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumLowEnergy)
        .value("enumZ_Effective", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumZ_Effective)
        .value("enumBasisMaterial_1", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumBasisMaterial_1)
        .value("enumBasisMaterial_2", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumBasisMaterial_2)
        .value("enumCompton", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumCompton)
        .value("enumPhotoelectric", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumPhotoelectric)
        .value("enumDensity", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumDensity)
        .value("enumIntensity", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumIntensity)
        .value("enumMu", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumMu)
        .value("enumMultiEnergy", SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumMultiEnergy);

    py::enum_<SDICOS::CTTypes::CTImage::IMAGE_FLAVOR>(m, "IMAGE_FLAVOR")
        .value("enumUnknownImageFlavor", SDICOS::CTTypes::CTImage::IMAGE_FLAVOR::enumUnknownImageFlavor)
        .value("enumProjection", SDICOS::CTTypes::CTImage::IMAGE_FLAVOR::enumProjection)
        .value("enumVolume", SDICOS::CTTypes::CTImage::IMAGE_FLAVOR::enumVolume);  

    py::enum_<SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>(m, "PHOTOMETRIC_INTERPRETATION")
        .value("enumUnknownPhotometricInterpretation", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumUnknownPhotometricInterpretation)
        .value("enumMonochrome1", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumMonochrome1)
        .value("enumMonochrome2", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumMonochrome2)
        .value("enumPaletteColor", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumPaletteColor)
        .value("enumRGB", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumRGB)
        .value("enumYBR_Full", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Full)
        .value("enumYBR_Full_422", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Full_422)
        .value("enumYBR_Partial_422", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Partial_422)
        .value("enumYBR_Partial_420", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_Partial_420)
        .value("enumYBR_ICT", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_ICT)
        .value("enumYBR_RCT", SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_RCT);  

    py::enum_<SDICOS::DicosFile::TRANSFER_SYNTAX>(m, "TRANSFER_SYNTAX")
        .value("enumLittleEndianExplicit", SDICOS::DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicit)
        .value("enumLittleEndianExplicitExtended", SDICOS::DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicitExtended)
        .value("enumLittleEndianImplicit", SDICOS::DicosFile::TRANSFER_SYNTAX::enumLittleEndianImplicit)
        .value("enumLosslessJPEG", SDICOS::DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .value("enumLosslessRLE", SDICOS::DicosFile::TRANSFER_SYNTAX::enumLosslessRLE);

    py::class_<PyCT, SDICOS::CT, SDICOS::IODCommon, 
                                 SDICOS::ScanCommon, 
                                 SDICOS::AcquisitionContextUser, 
                                 SDICOS::XRayEquipmentUser, 
                                 SDICOS::ImageCommonUser, 
                                 SDICOS::FrameOfReferenceUser>(m, "CT")
        .def(py::init<>())
        .def(py::init<const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS, 
                      const SDICOS::CTTypes::CTImage::IMAGE_FLAVOR, 
                      const SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>(), 
                       py::arg("nOOIType"), 
                       py::arg("nOOI"), 
                       py::arg("nFlavor") = SDICOS::CTTypes::CTImage::enumVolume, 
                       py::arg("nPI") = SDICOS::ImagePixelMacro::enumMonochrome2)
        .def("__copy__", [](const SDICOS::CT &self) { return SDICOS::CT(self); })
        .def("__deepcopy__", [](const SDICOS::CT &self, py::dict) { return SDICOS::CT(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Initialize", py::overload_cast<const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                                             const SDICOS::CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS, 
                                             const SDICOS::CTTypes::CTImage::IMAGE_FLAVOR, 
                                             const SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>
                           (&PyCT::Initialize), 
                           py::arg("nOOIType"), 
                           py::arg("nOOI"),
                           py::arg("nFlavor") = SDICOS::CTTypes::CTImage::enumVolume, 
                           py::arg("nPI") = SDICOS::ImagePixelMacro::enumMonochrome2)
        .def("Initialize", py::overload_cast<std::vector<SDICOS::CTModule*>&, 
                                             SDICOS::ErrorLog&, 
                                             bool>
                           (&PyCT::Initialize),
                           py::arg("vSeries"), 
                           py::arg("errorlog"), 
                           py::arg("bMoveData"))
        .def("Read", py::overload_cast<const SDICOS::DicosFileListing::SopInstance&, 
                                             SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> >&, 
                                             SDICOS::IMemoryManager*
                                      >
                     (&PyCT::Read), 
                     py::arg("sopinstance"), 
                     py::arg("vErrorlogs"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<const SDICOS::Filename&, 
                                       SDICOS::ErrorLog&, 
                                       SDICOS::IMemoryManager*
                                       >
                     (&PyCT::CT::Read),
                     py::arg("filename"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<SDICOS::MemoryFile&, 
                                       SDICOS::ErrorLog& , 
                                       SDICOS::IMemoryManager*
                                       >
                     (&PyCT::CT::Read),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)       

        .def("Write", py::overload_cast<const SDICOS::Filename&, 
                                        SDICOS::ErrorLog&, 
                                        const SDICOS::DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_), 
                     py::arg("filename"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = SDICOS::DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<const SDICOS::Filename&, 
                                        SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> > &, 
                                        const SDICOS::DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_),
                     py::arg("filenameBase"), 
                     py::arg("vErrorlogs"),
                     py::arg("nTransferSyntax") = SDICOS::DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<SDICOS::MemoryFile&, 
                                        SDICOS::ErrorLog&, 
                                        const SDICOS::DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("nTransferSyntax") = SDICOS::DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("GetModality", py::overload_cast<>(&PyCT::CT::GetModality, py::const_))
        .def("GetNumberOfFilesToCreate", &SDICOS::CT::GetNumberOfFilesToCreate)
        .def("SetBurnedInAnnotation", &SDICOS::CT::SetBurnedInAnnotation, py::arg("bUsesAnnotation"))
        .def("HasBurnedInAnnotation", &SDICOS::CT::HasBurnedInAnnotation)
        .def("SetPhotometricInterpretation", &SDICOS::CT::SetPhotometricInterpretation, py::arg("nPI"))
        .def("GetPhotometricInterpretation", &SDICOS::CT::GetPhotometricInterpretation) 
        .def("SetImageType", &SDICOS::CT::SetImageType, py::arg("nOOI"), py::arg("nFlavor") = SDICOS::CTTypes::CTImage::enumVolume)
        .def("GetImageType", &SDICOS::CT::GetImageType, py::arg("nOOI"), py::arg("nFlavor")) 
        .def("GetOOIImageCharacteristics", &SDICOS::CT::GetOOIImageCharacteristics)
        .def("GetImageFlavor", &SDICOS::CT::GetImageFlavor) 
        .def("SetSDI", &SDICOS::CT::SetSDI)
        .def("IsSDI", &SDICOS::CT::IsSDI) 
        .def("SetCDI", &SDICOS::CT::SetCDI)
        .def("IsCDI", &SDICOS::CT::IsCDI) 
        .def("SetStandard", &SDICOS::CT::SetStandard) 
        .def("IsStandard", &SDICOS::CT::IsStandard) 
        .def("SetImageAcquisitionDuration", &SDICOS::CT::SetImageAcquisitionDuration, py::arg("nAcquisitionDuration"))
        .def("GetImageAcquisitionDuration", &SDICOS::CT::GetImageAcquisitionDuration) 
        .def("SetContentDateAndTime", &SDICOS::CT::SetContentDateAndTime, py::arg("strDate"), py::arg("strTime"))
        .def("GetContentDate", &SDICOS::CT::GetContentDate) 
        .def("GetContentTime", &SDICOS::CT::GetContentTime) 
        .def("SetInstanceNumber", &SDICOS::CT::SetInstanceNumber, py::arg("nInstanceNumber"))
        .def("GetInstanceNumber", &SDICOS::CT::GetInstanceNumber) 
        .def("SetNumberOfSections", &SDICOS::CT::SetNumberOfSections, py::arg("nNum"))
        .def("GetNumberOfSections", &SDICOS::CT::GetNumberOfSections) 
        .def("GetSopClassUID", py::overload_cast<>(&PyCT::CT::GetSopClassUID, py::const_))

        ;
}