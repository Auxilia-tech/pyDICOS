#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void export_modG4digit_hits(py::module &);
void export_modG4event(py::module &);
void export_modG4geometry(py::module &);
void export_modG4global(py::module &);
void export_modG4graphics_reps(py::module &);
void export_modG4intercoms(py::module &);
void export_modG4interface(py::module &);
void export_modG4materials(py::module &);
void export_modG4particles(py::module &);
void export_modG4physics_list(py::module &);
void export_modG4processes(py::module &);
void export_modG4run(py::module &);
void export_modG4tasking(py::module &);
void export_modG4track(py::module &);
void export_modG4tracking(py::module &);
void export_modG4visualization(py::module &);
void export_modG4persistency(py::module &);
void export_modG4analysis(py::module &);

PYBIND11_MODULE(pyDICOS, m)
{
   export_modG4global(m);
   export_modG4intercoms(m);
   export_modG4graphics_reps(m);
   export_modG4digit_hits(m);
   export_modG4materials(m);
   export_modG4geometry(m);
   export_modG4particles(m);
   export_modG4processes(m);
   export_modG4track(m);
   export_modG4tracking(m);
   export_modG4event(m);
   export_modG4run(m);
   export_modG4tasking(m);
   export_modG4physics_list(m);
   export_modG4interface(m);
   export_modG4visualization(m);
   export_modG4persistency(m);
   export_modG4analysis(m);

}