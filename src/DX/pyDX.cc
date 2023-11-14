#ifndef PYDX_FILE_H
#define PYDX_FILE_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>


#include "SDICOS/UserDX.h"
#include "SDICOS/ModuleDX.h"
 #include "SDICOS/TemplateBase.h"
 #include "SDICOS/Array1D.h"
 #include "SDICOS/Point3D.h"
 #include "SDICOS/Vector3D.h"
 #include "SDICOS/TemplateCommon.h"
 #include "SDICOS/Image2D.h"
 #include "SDICOS/ImageBaseUser.h"
 #include "SDICOS/XRayEquipmentUser.h"
 #include "SDICOS/XRayGenerationUser.h"
 #include "SDICOS/DXDetectorUser.h"
 #include "SDICOS/DXPositioningUser.h"
 #include "SDICOS/XRayFiltrationUser.h"
 #include "SDICOS/FrameOfReferenceUser.h"
 #include "SDICOS/AcquisitionContextUser.h"

namespace py = pybind11;

using namespace SDICOS;


class PyDX : public DX {
public:
    using DX::DX;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  DX, FreeMemory); }

    bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  DX, Read, filename, errorLog, pMemMgr);}  
    
    bool Read(MemoryFile &memfile, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  DX, Read, memfile, errorLog, pMemMgr);}  

    bool Write(const Filename &filename, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  DX, Write, filename, errorLog, nTransferSyntax);}  

    bool Write(MemoryFile &memfile, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  DX, Write, memfile, errorLog, nTransferSyntax);}  

    IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(IODCommon::MODALITY, DX, GetModality);}  
    
};

void export_DX(py::module &m)
{
    py::class_<ScanCommon>(m, "ScanCommon");
    py::class_<XRayEquipmentUser>(m, "XRayEquipmentUser");
    py::class_<ImageCommonUser>(m, "ImageCommonUser");
    py::class_<DXDetectorUser>(m, "DXDetectorUser");
    py::class_<DXPositioningUser>(m, "DXPositioningUser");
    py::class_<XRayGenerationUser>(m, "XRayGenerationUser");
    py::class_<XRayFiltrationUser>(m, "XRayFiltrationUser");
    py::class_<FrameOfReferenceUser>(m, "FrameOfReferenceUser");
    py::class_<AcquisitionContextUser>(m, "AcquisitionContextUser");

    py::enum_<DicosFile::TRANSFER_SYNTAX>(m, "TRANSFER_SYNTAX")
        .value("enumLittleEndianExplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicit)
        .value("enumLittleEndianExplicitExtended", DicosFile::TRANSFER_SYNTAX::enumLittleEndianExplicitExtended)
        .value("enumLittleEndianImplicit", DicosFile::TRANSFER_SYNTAX::enumLittleEndianImplicit)
        .value("enumLosslessJPEG", DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .value("enumLosslessRLE", DicosFile::TRANSFER_SYNTAX::enumLosslessRLE);

    py::enum_<DXTypes::DXSeries::PRESENTATION_INTENT_TYPE>(m, "PRESENTATION_INTENT_TYPE")
        .value("enumUnknownPresentationIntentType", DXTypes::DXSeries::enumUnknownPresentationIntentType)
        .value("enumPresentation",  DXTypes::DXSeries::enumPresentation)
        .value("enumProcessing",  DXTypes::DXSeries::enumProcessing);

    py::enum_<ImageType::PIXEL_DATA_CHARACTERISTICS>(m, "PIXEL_DATA_CHARACTERISTICS")
        .value("enumUnknownPixelDataCharacteristics",  GeneralImageModule::enumUnknownPixelDataCharacteristics)
        .value("enumOriginal",   GeneralImageModule::enumOriginal)
        .value("enumDerived",   GeneralImageModule::enumDerived);

    py::class_<PyDX, DX, ScanCommon, 
                         XRayEquipmentUser, 
                         ImageCommonUser, 
                         DXDetectorUser, 
                         DXPositioningUser, 
                         XRayGenerationUser,
                         XRayFiltrationUser,
                         FrameOfReferenceUser,
                         AcquisitionContextUser>(m, "DX")
        .def(py::init<>())
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const DXTypes::DXSeries::PRESENTATION_INTENT_TYPE, 
                      const GeneralImageModule::PIXEL_DATA_CHARACTERISTICS, 
                      const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>(), 
                       py::arg("nOOIType"), 
                       py::arg("presentationIntentType") =  DXTypes::DXSeries::enumProcessing, 
                       py::arg("pixelDataCharacteristics") = GeneralImageModule::enumOriginal, 
                       py::arg("nPI") = ImagePixelMacro::enumMonochrome2)
        .def("__copy__", [](const DX &self) { return DX(self); })
        .def("__deepcopy__", [](const DX &self, py::dict) { return DX(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Initialize", py::overload_cast<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                                             const DXTypes::DXSeries::PRESENTATION_INTENT_TYPE, 
                                             const GeneralImageModule::PIXEL_DATA_CHARACTERISTICS, 
                                             const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION>
                           (&PyDX::Initialize), 
                           py::arg("nOOIType"), 
                           py::arg("presentationIntentType"),
                           py::arg("pixelDataCharacteristics") = GeneralImageModule::enumOriginal, 
                           py::arg("nPI") = ImagePixelMacro::enumMonochrome2)
        .def("Initialize", py::overload_cast<DXModule&, 
                                             ErrorLog&, 
                                             bool>
                           (&PyDX::Initialize),
                           py::arg("dx"), 
                           py::arg("errorlog"), 
                           py::arg("bMoveData"))
        .def("Read", py::overload_cast<const Filename&, 
                                       ErrorLog&, 
                                       IMemoryManager*
                                       >
                     (&PyDX::DX::Read),
                     py::arg("filename"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)
        .def("Read", py::overload_cast<MemoryFile&, 
                                       ErrorLog& , 
                                       IMemoryManager*
                                       >
                     (&PyDX::DX::Read),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("pMemMgr") = S_NULL)       

        .def("Write", py::overload_cast<const Filename&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyDX::DX::Write, py::const_), 
                     py::arg("filename"), 
                     py::arg("errorLog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("Write", py::overload_cast<MemoryFile&, 
                                        ErrorLog&, 
                                        const DicosFile::TRANSFER_SYNTAX
                                        >
                     (&PyDX::DX::Write, py::const_),
                     py::arg("memfile"), 
                     py::arg("errorlog"),
                     py::arg("nTransferSyntax") = DicosFile::TRANSFER_SYNTAX::enumLosslessJPEG)
        .def("GetModality", py::overload_cast<>(&PyDX::DX::GetModality, py::const_))
        ;
}

#endif
