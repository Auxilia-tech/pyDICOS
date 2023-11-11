#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void export_tdr(py::module &);
void export_modTDR(py::module &m)
{
    export_tdr(m);
}
