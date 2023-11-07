#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
void export_modCT(py::module &);


PYBIND11_MODULE(pyDICOS, m)
{
   export_modCT(m);
}