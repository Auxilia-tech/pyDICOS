#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <map>

#include "SDICOS/DICOS.h"
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


namespace py = pybind11;

using namespace SDICOS;

PYBIND11_MAKE_OPAQUE(std::vector<CTModule*>);

class PySection : public Section {
public:
    using Section::Section;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  Section, FreeMemory); }
};

float GetFocalSpotSizeFloat(const Section &self) {
    return self.GetFocalSpotSize();
}

void GetFocalSpotSizePair(const Section &self, float &fSmallSize, float &fLargeSize) {
    self.GetFocalSpotSize(fSmallSize, fLargeSize);
}


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

    IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(IODCommon::MODALITY, CT, GetModality);}  

    DcsUniqueIdentifier GetSopClassUID() const
              override {PYBIND11_OVERRIDE(DcsUniqueIdentifier, CT, GetSopClassUID);}
    
};


void export_ct(py::module &m)
{
    py::class_<SectionCommon>(m, "SectionCommon");
    py::class_<PySection, Section, SectionCommon>(m, "Section")
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("sectionId"))
        .def("__copy__", [](const Section &self) { return Section(self); })
        .def("__deepcopy__", [](const Section &self, py::dict) { return Section(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("SetImagePixelPresentation", &Section::SetImagePixelPresentation)
        .def("SetImagePixelPresentation", &Section::SetImagePixelPresentation, py::arg("nPresentation"))
        .def("GetImagePixelPresentation", &Section::GetImagePixelPresentation)
        .def("SetImageVolumeBasedCalculationTechnique", &Section::SetImageVolumeBasedCalculationTechnique, py::arg("nTechnique"))
        .def("GetImageVolumeBasedCalculationTechnique", &Section::GetImageVolumeBasedCalculationTechnique)
        .def("SetImageVolumetricProperties", &Section::SetImageVolumetricProperties,  py::arg("nProperties"))
        .def("GetImageVolumetricProperties", &Section::GetImageVolumetricProperties)
        .def("SetRescaleSlope", &Section::SetRescaleSlope,  py::arg("fSlope"))
        .def("GetRescaleSlope", &Section::GetRescaleSlope)
        .def("SetRescaleIntercept", &Section::SetRescaleIntercept,  py::arg("fIntercept"))
        .def("GetRescaleIntercept", &Section::GetRescaleIntercept)
        .def("SetRescaleType", &Section::SetRescaleType, py::arg("strType"))
        .def("GetRescaleType", &Section::GetRescaleType, py::return_value_policy::reference)
        .def("SetFilterMaterial", &Section::SetFilterMaterial,  py::arg("nFilterMaterial"))
        .def("GetFilterMaterial", &Section::GetFilterMaterial)
        .def("SetFilterMaterials", &Section::SetFilterMaterials,  py::arg("vFilterMaterial"))
        .def("GetFilterMaterials", &Section::GetFilterMaterials)
        .def("SetFilterType", &Section::SetFilterType,  py::arg("nFilterType"))
        .def("GetFilterType", &Section::GetFilterType)
        .def("SetFocalSpotSizeInMM", &Section::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"))
        .def("GetFocalSpotSize", &GetFocalSpotSizeFloat, "Get the focal spot size")
        .def("HasOneFocalSpotSize", &Section::HasOneFocalSpotSize)
        .def("SetFocalSpotSizesInMM", &Section::SetFocalSpotSizesInMM, py::arg("fSmallSize"), py::arg("fLargeSize"))
        .def("GetFocalSpotSize", &GetFocalSpotSizePair, "Get the focal spot size as a pair of small and large sizes")
        .def("GetFocalSpotSmallSize", &Section::GetFocalSpotSmallSize)
        .def("GetFocalSpotLargeSize", &Section::GetFocalSpotLargeSize)
        .def("HasTwoFocalSpotSizes", &Section::HasTwoFocalSpotSizes)
        .def("SetKVP", &Section::SetKVP, py::arg("fKVP"))
        .def("GetKVP", &Section::GetKVP)
        .def("ApplyRescaleToImage", &Section::ApplyRescaleToImage)
        .def("FreeMemory", &PySection::FreeMemory);

    py::enum_<ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE>(m, "OBJECT_OF_INSPECTION_TYPE")
        .value("enumUnknownObjectOfInspectionType", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumUnknownObjectOfInspectionType)
        .value("enumTypeBioSample", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBioSample)
        .value("enumTypeCargo", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeCargo)
        .value("enumTypeBaggage", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeBaggage)
        .value("enumTypeAnimal", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeAnimal)
        .value("enumTypeOther", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypeOther)
        .value("enumTypePerson", ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE::enumTypePerson);

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
        .value("enumMultiEnergy", CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS::enumMultiEnergy);

    py::enum_<CTTypes::CTImage::IMAGE_FLAVOR>(m, "IMAGE_FLAVOR")
        .value("enumUnknownImageFlavor", CTTypes::CTImage::IMAGE_FLAVOR::enumUnknownImageFlavor)
        .value("enumProjection", CTTypes::CTImage::IMAGE_FLAVOR::enumProjection)
        .value("enumVolume", CTTypes::CTImage::IMAGE_FLAVOR::enumVolume);  

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
        .value("enumYBR_RCT", ImagePixelMacro::PHOTOMETRIC_INTERPRETATION::enumYBR_RCT);  

    py::enum_<DicosFile::TRANSFER_SYNTAX>(m, "TRANSFER_SYNTAX")
        .value("enumLittleEndianExplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicit)
        .value("enumLittleEndianExplicitExtended", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicitExtended)
        .value("enumLittleEndianImplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianImplicit)
        .value("enumLosslessJPEG", DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .value("enumLosslessRLE", DicosFile::TRANSFER_SYNTAX::enumLosslessRLE);


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
                                             IMemoryManager*
                                      >
                     (&PyCT::Read), 
                     py::arg("sopinstance"), 
                     py::arg("vErrorlogs"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<const Filename&, 
                                       ErrorLog&, 
                                       IMemoryManager*
                                       >
                     (&PyCT::CT::Read),
                     py::arg("filename"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<MemoryFile&, 
                                       ErrorLog& , 
                                       IMemoryManager*
                                       >
                     (&PyCT::CT::Read),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)       

        .def("Write", py::overload_cast<const Filename&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_), 
                     py::arg("filename"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<const Filename&, 
                                        Array1D< std::pair<Filename, ErrorLog> > &, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_),
                     py::arg("filenameBase"), 
                     py::arg("vErrorlogs"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<MemoryFile&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyCT::CT::Write, py::const_),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("GetModality", py::overload_cast<>(&PyCT::CT::GetModality, py::const_))
        .def("GetNumberOfFilesToCreate", &CT::GetNumberOfFilesToCreate)
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
        ;
}

#endif // MY_HEADER_FILE_H