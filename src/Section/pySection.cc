#include "../headers.hh"


 #include "SDICOS/UserCT.h"
 #include "SDICOS/ModuleCT.h"
 #include "SDICOS/Array1D.h"
 #include "SDICOS/Point3D.h"
 #include "SDICOS/Vector3D.h"
 #include "SDICOS/TemplateCommon.h"
 #include "SDICOS/TemplateBase.h"
 #include "SDICOS/ClientManager.h"
 #include "SDICOS/MemoryPolicy.h"
 #include "SDICOS/AcquisitionContextUser.h"
 #include "SDICOS/ImageBaseUser.h"
 #include "SDICOS/XRayEquipmentUser.h"
 #include "SDICOS/FrameOfReferenceUser.h"
 #include "SDICOS/CTXRayDetails.h"
 
using namespace SDICOS;

PYBIND11_MAKE_OPAQUE(std::vector<CTModule*>);

class PySection : public Section {
public:
    using Section::Section;
    void FreeMemory() override { PYBIND11_OVERRIDE(void,  Section, FreeMemory); }
};

void export_SECTION(py::module &m)
{
    py::enum_<CTTypes::CTXRayDetails::FILTER_MATERIAL>(m, "FILTER_MATERIAL")
        .value(" enumUnknownFilterMaterial", CTTypes::CTXRayDetails::FILTER_MATERIAL:: enumUnknownFilterMaterial)
        .value("enumMolybdenum", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumMolybdenum)
        .value("enumAluminum", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumAluminum)
        .value("enumCopper", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumCopper)
        .value("enumRhodium", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumRhodium)
        .value("enumNiobium", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumNiobium)
        .value("enumEuropium", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumEuropium)
        .value("enumLead", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumLead)
        .value("enumMixed", CTTypes::CTXRayDetails::FILTER_MATERIAL::enumMixed)
        .export_values();

    py::class_<SectionCommon>(m, "SectionCommon");
    py::class_<Section>(m, "SDICOS::Section")
        .def(py::init<>())
        .def("SetFocalSpotSizeInMM", &Section::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"))
        .def("GetFocalSpotSize", py::overload_cast<>(&Section::GetFocalSpotSize, py::const_))
        .def("GetFocalSpotSize", py::overload_cast<float&, float&>(&Section::GetFocalSpotSize, py::const_), py::arg("fSmallSize"),  py::arg("fLargeSize"))
        .def("SetPlaneOrientation", &SectionCommon::SetPlaneOrientation, py::arg("ptRowOrientation"), py::arg("ptColumnOrientation"))
        .def("GetRowOrientation", &SectionCommon::GetRowOrientation)
        .def("GetColumnOrientation", &SectionCommon::GetColumnOrientation)
        .def("SetSlicingDirection", &SectionCommon::SetSlicingDirection, py::arg("bPositive"))
        .def("SetKVP", &Section::SetKVP, py::arg("fKVP"))
        .def("SetRescaleType", &Section::SetRescaleType, py::arg("strType"))
        .def("GetRescaleType", &Section::GetRescaleType)
        .def("GetKVP", &Section::GetKVP)
        .def("GetPixelData", py::overload_cast<>(&SectionCommon::GetPixelData), py::return_value_policy::reference_internal)
        .def("GetPixelData", py::overload_cast<>(&SectionCommon::GetPixelData, py::const_), py::return_value_policy::reference_internal)
        .def("GetPixelDataType", &SectionCommon::GetPixelDataType)
        .def("SetFilterMaterial", &Section::SetFilterMaterial,  py::arg("nFilterMaterial"))
        .def("GetFilterMaterial", &Section::GetFilterMaterial)
        .def("SetPositionInMM", py::overload_cast<const float, const float, const float>(&SectionCommon::SetPositionInMM), 
                                py::arg("fX"), py::arg("fY"), py::arg("fZ"))
        .def("SetPositionInMM", py::overload_cast<const Point3D<float> &>(&SectionCommon::SetPositionInMM), 
                                py::arg("pt"))
        .def("SetSpacingInMM", &SectionCommon::SetSpacingInMM, py::arg("fColumn"), py::arg("fRow"), py::arg("fSlice"))
        .def("SetSliceThickness", &SectionCommon::SetSliceThickness, py::arg("fSliceThickness"))
        .def("GetWidth",  &SectionCommon:: GetWidth)
        .def("GetHeight",  &SectionCommon:: GetHeight)
        .def("GetDepth",  &SectionCommon:: GetDepth)
        .def("GetSliceThickness", &SectionCommon::GetSliceThickness)
        .def("GetSpacingInMM", &SectionCommon::GetSpacingInMM)
        .def("GetPositionInMM", &SectionCommon::GetPositionInMM)
        .def("GetXPosition", &SectionCommon::GetXPosition)
        .def("GetYPosition", &SectionCommon::GetYPosition)
        .def("GetZPosition", &SectionCommon::GetZPosition)
        .def("GetRowSpacing", &SectionCommon::GetRowSpacing)
        .def("GetColumnSpacing", &SectionCommon::GetColumnSpacing)
        .def("GetSliceSpacing", &SectionCommon::GetSliceSpacing)
        .def("IsSlicingDirection", &SectionCommon::IsSlicingDirection)
        .def("IsOppositeSlicingDirection", &SectionCommon::IsOppositeSlicingDirection);

   
    py::class_<PySection, Section, SectionCommon>(m, "Section")
        .def(py::init<>())
        .def(py::init<const S_UINT32>(), py::arg("sectionId"))
        .def_property_readonly_static("FILTER_MATERIAL", [m](py::object) {
            return m.attr("FILTER_MATERIAL");
        })  
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
        .def("GetPixelDataType", &SectionCommon::GetPixelDataType)
        .def("SetFocalSpotSizeInMM", &Section::SetFocalSpotSizeInMM,  py::arg("fNominalDimension"))
        .def("SetPlaneOrientation", &SectionCommon::SetPlaneOrientation, py::arg("ptRowOrientation"), py::arg("ptColumnOrientation"))
        .def("SetPositionInMM", py::overload_cast<const float, const float, const float>(&SectionCommon::SetPositionInMM), 
                                py::arg("fX"), py::arg("fY"), py::arg("fZ"))
        .def("SetPositionInMM", py::overload_cast<const Point3D<float> &>(&SectionCommon::SetPositionInMM), 
                                py::arg("pt"))
        .def("SetSpacingInMM", &SectionCommon::SetSpacingInMM, py::arg("fColumn"), py::arg("fRow"), py::arg("fSlice"))
        .def("SetSliceThickness", &SectionCommon::SetSliceThickness, py::arg("fSliceThickness"))
        .def("GetRowOrientation", &SectionCommon::GetRowOrientation)
        .def("GetColumnOrientation", &SectionCommon::GetColumnOrientation)
        .def("SetSlicingDirection", &SectionCommon::SetSlicingDirection, py::arg("bPositive"))
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
        .def("FreeMemory", &PySection::FreeMemory)
        .def("GetWidth",  &SectionCommon::GetWidth)
        .def("GetHeight",  &SectionCommon::GetHeight)
        .def("GetDepth",  &SectionCommon::GetDepth)
        .def("GetSliceThickness", &SectionCommon::GetSliceThickness)
        .def("GetSpacingInMM", &SectionCommon::GetSpacingInMM)
        .def("GetPositionInMM", &SectionCommon::GetPositionInMM)
        .def("GetXPosition", &SectionCommon::GetXPosition)
        .def("GetYPosition", &SectionCommon::GetYPosition)
        .def("GetZPosition", &SectionCommon::GetZPosition)
        .def("GetRowSpacing", &SectionCommon::GetRowSpacing)
        .def("GetColumnSpacing", &SectionCommon::GetColumnSpacing)
        .def("GetSliceSpacing", &SectionCommon::GetSliceSpacing)
        .def("IsSlicingDirection", &SectionCommon::IsSlicingDirection)
        .def("IsOppositeSlicingDirection", &SectionCommon::IsOppositeSlicingDirection);
}
