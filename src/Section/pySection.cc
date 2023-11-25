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

class PySection : public Section {
public:
    using Section::Section;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  Section, FreeMemory); }
};

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


void export_SECTION(py::module &m)
{
    py::class_<SectionCommon>(m, "SectionCommon");
    py::class_<Section>(m, "SDICOS::Section")
        .def(py::init<>())
        .def("SetFocalSpotSizeInMM", &PySection::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"));
    py::class_<PySection, Section, SectionCommon>(m, "Section")
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("sectionId"))
        .def("__copy__", [](const Section &self) { return Section(self); })
        .def("__deepcopy__", [](const Section &self, py::dict) { return Section(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
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
        .def("SetFocalSpotSizeInMM", &PySection::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"))
        .def("GetFocalSpotSize", py::overload_cast<>(&Section::GetFocalSpotSize, py::const_))
        .def("GetFocalSpotSize", py::overload_cast<float&, float&>(&Section::GetFocalSpotSize, py::const_), py::arg("fSmallSize"),  py::arg("fLargeSize"))
        .def("HasOneFocalSpotSize", &Section::HasOneFocalSpotSize)
        .def("SetFocalSpotSizesInMM", &Section::SetFocalSpotSizesInMM, py::arg("fSmallSize"), py::arg("fLargeSize"))
        .def("GetFocalSpotSmallSize", &Section::GetFocalSpotSmallSize)
        .def("GetFocalSpotLargeSize", &Section::GetFocalSpotLargeSize)
        .def("HasTwoFocalSpotSizes", &Section::HasTwoFocalSpotSizes)
        .def("SetKVP", &Section::SetKVP, py::arg("fKVP"))
        .def("GetKVP", &Section::GetKVP)
        .def("ApplyRescaleToImage", &Section::ApplyRescaleToImage)
        .def("FreeMemory", &PySection::FreeMemory);
}
