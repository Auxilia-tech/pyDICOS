#include "../headers.hh"

#include "SDICOS/GeneralSeriesModule.h"

using namespace SDICOS;

void export_GeneralSeriesModule(py::module &m)
{
    py::enum_<GeneralSeriesModule::MODALITY>(m, "MODALITY")
        .value("enumUnknownModality", GeneralSeriesModule::MODALITY::enumUnknownModality)
        .value("enumCT", GeneralSeriesModule::MODALITY::enumCT)
        .value("enumTDR", GeneralSeriesModule::MODALITY::enumTDR)
        .value("enumAIT", GeneralSeriesModule::MODALITY::enumAIT)
        .value("enumAIT2D", GeneralSeriesModule::MODALITY::enumAIT2D)
        .value("enumAIT3D", GeneralSeriesModule::MODALITY::enumAIT3D)
        .value("enumQR", GeneralSeriesModule::MODALITY::enumQR)
        .value("enumHDAIT", GeneralSeriesModule::MODALITY::enumHDAIT)
        .value("enumWAIT", GeneralSeriesModule::MODALITY::enumWAIT)
        .value("enumETD", GeneralSeriesModule::MODALITY::enumETD)
        .value("enumDPC", GeneralSeriesModule::MODALITY::enumDPC)
        .value("enumXRD", GeneralSeriesModule::MODALITY::enumXRD)
        .export_values();


    py::enum_<GeneralSeriesModule::ACQUISITION_STATUS>(m, "ACQUISITION_STATUS")
        .value("enumUnknownAcquisitionStatus", GeneralSeriesModule::ACQUISITION_STATUS::enumUnknownAcquisitionStatus)
        .value("enumSuccessful", GeneralSeriesModule::ACQUISITION_STATUS::enumSuccessful)
        .value("enumJam", GeneralSeriesModule::ACQUISITION_STATUS::enumJam)
        .value("enumOversize", GeneralSeriesModule::ACQUISITION_STATUS::enumOversize)
        .value("enumSlip", GeneralSeriesModule::ACQUISITION_STATUS::enumSlip)
        .value("enumIncomplete", GeneralSeriesModule::ACQUISITION_STATUS::enumIncomplete)
        .value("enumCut", GeneralSeriesModule::ACQUISITION_STATUS::enumCut)
        .value("enumMerged", GeneralSeriesModule::ACQUISITION_STATUS::enumMerged)
        .value("enumStitched", GeneralSeriesModule::ACQUISITION_STATUS::enumStitched)
        .export_values();

    py::enum_<GeneralSeriesModule::TEST_ARTICLE_TYPE>(m, "TEST_ARTICLE_TYPE")
        .value("enumUnknownTestArticleType", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumUnknownTestArticleType)
        .value("enumNIST_FAT", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumNIST_FAT)
        .value("enumNIST_SAT", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumNIST_SAT)
        .value("enumOTK", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumOTK)
        .value("enumCTIQ", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumCTIQ)
        .value("enumCalibration", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumCalibration)
        .value("enumGIQ", GeneralSeriesModule::TEST_ARTICLE_TYPE::enumGIQ)
        .export_values();

    py::class_<GeneralSeriesModule>(m, "GeneralSeriesModule")
        .def_property_readonly_static("MODALITY", [m](py::object) {
            return m.attr("MODALITY");
        }) 
        .def_property_readonly_static("ACQUISITION_STATUS", [m](py::object) {
            return m.attr("ACQUISITION_STATUS");
        }) 
        .def_property_readonly_static("TEST_ARTICLE_TYPE", [m](py::object) {
            return m.attr("TEST_ARTICLE_TYPE");
        }) 
        .def(py::init<>())
        .def(py::init<const GeneralSeriesModule&>(), py::arg("generalseriesmodule"))
        .def("__copy__", [](const GeneralSeriesModule &self) { return GeneralSeriesModule(self); })
        .def("__deepcopy__", [](const GeneralSeriesModule &self, py::dict) { return GeneralSeriesModule(self); })
        .def(py::self == py::self)
        .def(py::self != py::self);
}
