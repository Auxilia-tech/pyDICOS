#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define EXPORT_G4HEADER(header, mod)   \
   void export_##header(py::module &); \
   export_##header(mod)

void export_modCT(py::module &m)
{
    EXPORT_G4HEADER(CT, m);
}
