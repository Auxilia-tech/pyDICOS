#include "../headers.hh"

#include "SDICOS/SopClassUID.h"

using namespace SDICOS;

void export_SopClassUID(py::module &m)
{
    m.def("GetCT", &SOPClassUID::GetCT);
    m.def("GetCTRaw", &SOPClassUID::GetCTRaw);
    m.def("GetCTCorrected", &SOPClassUID::GetCTCorrected);
    m.def("GetDXProcessing", &SOPClassUID::GetDXProcessing);
}
