#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
void export_modCT(py::module &);
void export_modDX(py::module &);
void export_modTDR(py::module &);

PYBIND11_MODULE(pyDICOS, m)
{
   export_modCT(m);
   export_modDX(m);
   export_modTDR(m);
}