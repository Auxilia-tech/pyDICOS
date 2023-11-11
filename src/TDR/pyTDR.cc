#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

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

    bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  TDR, Read, filename, errorLog, pMemMgr);}  
    
    bool Read(MemoryFile &memfile, ErrorLog& errorLog, IMemoryManager *pMemMgr)
              override {PYBIND11_OVERRIDE(bool,  TDR, Read, memfile, errorLog, pMemMgr);}  

    bool Write(MemoryBuffer &memorybuffer, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  TDR, Write, filename, errorLog, nTransferSyntax);}  

    bool Write(MemoryFile &memfile, ErrorLog& errorLog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax) const
              override {PYBIND11_OVERRIDE(bool,  TDR, Write, memfile, errorLog, nTransferSyntax);}  

    IODCommon::MODALITY GetModality() const
              override {PYBIND11_OVERRIDE(IODCommon::MODALITY, TDR, GetModality);}  
    
};

void export_tdr(py::module &m)
{
    py::class_<IODCommon>(m, "IODCommon");
    py::class_<FrameOfReferenceUser>(m, "FrameOfReferenceUser");

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

    py::class_<PyTDR, TDR, IODCommon, 
                         FrameOfReferenceUser
                         >(m, "TDR")
        .def(py::init<>())
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreadDetectionReport::TDR_TYPE, 
                      const S_INT32>(), 
                       py::arg("OOIType"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"))
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreadDetectionReport::TDR_TYPE, 
                      const S_INT32, 
                      const DcsDate&, 
                      const DcsTime&>(), 
                       py::arg("OOIType"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"), 
                       py::arg("contentCreationDate"), 
                       py::arg("contentCreationTime"))
        .def(py::init<const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER, 
                      const TDRTypes::ThreadDetectionReport::TDR_TYPE, 
                      const S_INT32, 
                      const DcsDate&, 
                      const DcsTime&>(), 
                       py::arg("gender"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"), 
                       py::arg("contentCreationDate"), 
                       py::arg("contentCreationTime"))
        .def(py::init<const DcsLongString&, 
                      const ObjectOfInspectionModule::IDinfo::OBJECT_OF_INSPECTION_ID_TYPE&,
                      const DcsLongString&,
                      const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE, 
                      const TDRTypes::ThreadDetectionReport::TDR_TYPE, 
                      const S_INT32>(), 
                       py::arg("OOIIdentifier"), 
                       py::arg("IdType"), 
                       py::arg("OOIIdentifierIssuer"), 
                       py::arg("OOIType"), 
                       py::arg("tdrType"), 
                       py::arg("instanceNumber"))
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
