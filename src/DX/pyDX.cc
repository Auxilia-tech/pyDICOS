#include "../headers.hh"

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
 #include "SDICOS/GeneralImageModule.h"

namespace py = pybind11;
using namespace SDICOS;

PYBIND11_MAKE_OPAQUE(std::vector<DXModule*>);


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

    bool Validate(ErrorLog& errorlog) const
              override {PYBIND11_OVERRIDE(bool, DX, Validate, errorlog);}
    
};

void export_DX(py::module &m)
{
    py::enum_<DXTypes::DXSeries::PRESENTATION_INTENT_TYPE>(m, "PRESENTATION_INTENT_TYPE")
        .value("enumUnknownPresentationIntentType", DXTypes::DXSeries::enumUnknownPresentationIntentType)
        .value("enumPresentation", DXTypes::DXSeries::enumPresentation)
        .value("enumProcessing", DXTypes::DXSeries::enumProcessing)
        .export_values();

    py::enum_<ImageType::PIXEL_DATA_CHARACTERISTICS>(m, "PIXEL_DATA_CHARACTERISTICS")
        .value("enumUnknownPixelDataCharacteristics",  GeneralImageModule::enumUnknownPixelDataCharacteristics)
        .value("enumOriginal", GeneralImageModule::enumOriginal)
        .value("enumDerived", GeneralImageModule::enumDerived)
        .export_values();

    py::enum_<GeneralImageModule::PRESENTATION_LUT_SHAPE>(m, "PRESENTATION_LUT_SHAPE")
        .value("enumUnknownPresentationLutShape",  GeneralImageModule::PRESENTATION_LUT_SHAPE::enumUnknownPresentationLutShape)
        .value("enumIdentity", GeneralImageModule::PRESENTATION_LUT_SHAPE::enumIdentity)
        .value("enumInverse", GeneralImageModule::PRESENTATION_LUT_SHAPE::enumInverse)
        .export_values();

    py::class_<DXDetectorUser>(m, "DXDetectorUser");
    py::class_<DXPositioningUser>(m, "DXPositioningUser");
    py::class_<XRayGenerationUser>(m, "XRayGenerationUser");
    py::class_<XRayFiltrationUser>(m, "XRayFiltrationUser");
    py::class_<DX>(m, "SDICOS::DX");
    py::class_<PyDX, DX, ScanCommon, 
                         XRayEquipmentUser, 
                         ImageCommonUser, 
                         DXDetectorUser, 
                         DXPositioningUser, 
                         XRayGenerationUser,
                         XRayFiltrationUser,
                         FrameOfReferenceUser,
                         AcquisitionContextUser>(m, "DX")
        .def_property_readonly_static("PRESENTATION_INTENT_TYPE", [m](py::object) {
            return m.attr("PRESENTATION_INTENT_TYPE");
        }) 
        .def_property_readonly_static("PIXEL_DATA_CHARACTERISTICS", [m](py::object) {
            return m.attr("PIXEL_DATA_CHARACTERISTICS");
        })   
        .def_property_readonly_static("PRESENTATION_LUT_SHAPE", [m](py::object) {
            return m.attr("PRESENTATION_LUT_SHAPE");
        }) 
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
        .def("Validate", py::overload_cast<ErrorLog&>(&PyDX::DX::Validate, py::const_), py::arg("errorlog"))
        .def("GetXRayData", py::overload_cast<>(&DX::GetXRayData),
                                  py::return_value_policy::reference_internal)
        .def("GetXRayData", py::overload_cast<>(&DX::GetXRayData, py::const_),  
                                  py::return_value_policy::reference_internal)
        .def("SetKVP", &XRayGenerationUser::SetKVP, py::arg("fKVP"))
        .def("SetImagePosition", py::overload_cast<const float, const float, const float>(&XRayGenerationUser::SetImagePosition), 
                                 py::arg("fX"), py::arg("fY"), py::arg("fZ"))
        .def("SetImagePosition", py::overload_cast<const Point3D<float>& >(&XRayGenerationUser::SetImagePosition), py::arg("pos"))  
        .def("SetImageOrientation", py::overload_cast<const float, 
                                                      const float, 
                                                      const float, 
                                                      const float, 
                                                      const float, 
                                                      const float>(&XRayGenerationUser::SetImageOrientation), 
                                    py::arg("fDirectionCosinesRowX"), 
                                    py::arg("fDirectionCosinesRowY"), 
                                    py::arg("fDirectionCosinesRowZ"), 
                                    py::arg("fDirectionCosinesColumnX"), 
                                    py::arg("fDirectionCosinesColumnY"), 
                                    py::arg("fDirectionCosinesColumnZ"))
        .def("SetImageOrientation", py::overload_cast<const Vector3D<float>&, 
                                                      const Vector3D<float>& >(&XRayGenerationUser::SetImageOrientation), 
                                    py::arg("ptRowOrientation"), py::arg("ptColumnOrientation"))
        .def("SetXRayTubeCurrent", &XRayGenerationUser::SetXRayTubeCurrent, py::arg("fCurrent"))
        .def("SetWindowCenterAndWidth", py::overload_cast<const Array1D<float> &, 
                                                          const Array1D<float> &>(&DX::SetWindowCenterAndWidth), 
                                        py::arg("arrayCenter"), py::arg("arrayWidth"))
        .def("SetWindowCenterAndWidth", py::overload_cast<const float, const float>(&DX::SetWindowCenterAndWidth), 
                                        py::arg("fCenter"), py::arg("fWidth"))
        .def("GetWindowCenterAndWidth", [](DX &self, Array1D<float> &arrayCenter, Array1D<float> &arrayWidth) {
            return std::make_tuple(self.GetWindowCenterAndWidth(arrayCenter, arrayWidth), arrayCenter, arrayWidth);
        }, py::arg("arrayCenter"), py::arg("arrayWidth"))
        .def("GetWindowCenterAndWidth", [](DX &self, float &fCenter, float &fWidth) {
            return std::make_tuple(self.GetWindowCenterAndWidth(fCenter, fWidth), fCenter, fWidth);
        }, py::arg("fCenter"), py::arg("fWidth"))
        .def("SetWindowCenterAndWidthExplanation", 
             py::overload_cast<const Array1D<DcsLongString> &>(&DX::SetWindowCenterAndWidthExplanation), py::arg("strExplanation"))
        .def("SetWindowCenterAndWidthExplanation", 
             py::overload_cast<const DcsLongString&>(&DX::SetWindowCenterAndWidthExplanation), py::arg("strExplanation"))
        .def("SetLUTData", 
             py::overload_cast<const Array1D<S_UINT16>&, 
                               const S_UINT16, 
                               const S_UINT16>(&DX::SetLUTData), 
                               py::arg("lutData"), 
                               py::arg("nFirstValueMapped"), 
                               py::arg("nBitsPerEntry") = 16)
        .def("SetLUTData", 
             py::overload_cast<const Array1D<S_INT16>&, 
                               const S_UINT16, 
                               const S_UINT16>(&DX::SetLUTData), 
                               py::arg("lutData"), 
                               py::arg("nFirstValueMapped"), 
                               py::arg("nBitsPerEntry") = 16)
        .def("SetLUTData", 
             py::overload_cast<const Array1D<S_UINT16>&, 
                               const S_INT16, 
                               const S_UINT16>(&DX::SetLUTData), 
                               py::arg("lutData"), 
                               py::arg("nFirstValueMapped"), 
                               py::arg("nBitsPerEntry") = 16)
        .def("SetLUTData", 
             py::overload_cast<const Array1D<S_INT16>&, 
                               const S_INT16, 
                               const S_UINT16>(&DX::SetLUTData), 
                               py::arg("lutData"), 
                               py::arg("nFirstValueMapped"), 
                               py::arg("nBitsPerEntry") = 16)

        .def("GetLUTData", py::overload_cast<Array1D<S_UINT16>&>(&DX::GetLUTData, py::const_), py::arg("lutData"))
        .def("GetLUTData", py::overload_cast<Array1D<S_INT16>&>(&DX::GetLUTData), py::arg("lutData"))
        .def("GetRedLUT",(Array1D<S_UINT8>& (DX::*)())&DX::GetRedLUT, py::return_value_policy::reference)
        .def("GetRedLUT",(const Array1D<S_UINT8>& (DX::*)() const)&DX::GetRedLUT, py::return_value_policy::reference)
        .def("GetGreenLUT",(Array1D<S_UINT8>& (DX::*)())&DX::GetGreenLUT, py::return_value_policy::reference)
        .def("GetGreenLUT",(const Array1D<S_UINT8>& (DX::*)() const)&DX::GetGreenLUT, py::return_value_policy::reference)
        .def("GetBlueLUT",(Array1D<S_UINT8>& (DX::*)())&DX::GetBlueLUT, py::return_value_policy::reference)
        .def("GetBlueLUT",(const Array1D<S_UINT8>& (DX::*)() const)&DX::GetBlueLUT, py::return_value_policy::reference)
        .def("SetPresentationLUTShape", &DX::SetPresentationLUTShape, py::arg("nLutShape"))
        .def("GetPresentationLUTShape", &DX::GetPresentationLUTShape);
}
