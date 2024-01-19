#include "../headers.hh"
#include <pybind11/numpy.h>

#include "SDICOS/MemoryBuffer.h"

using namespace SDICOS;

void export_MEMORYBUFFER(py::module &m)
{
    py::enum_<MemoryBuffer::MEMORY_POLICY>(m, "MEMORY_POLICY")
        .value("enumPolicy_DoesNotOwnData", MemoryBuffer::MEMORY_POLICY::enumPolicy_DoesNotOwnData)
        .value("enumPolicy_OwnsData", MemoryBuffer::MEMORY_POLICY::enumPolicy_OwnsData);

    py::class_<MemoryBuffer>(m, "MemoryBuffer", py::buffer_protocol())
        .def(py::init<>())
        .def(py::init<const MemoryBuffer&>(), py::arg("obj"))
        .def("__copy__", [](const MemoryBuffer &self) { return MemoryBuffer(self); })
        .def("__deepcopy__", [](const MemoryBuffer &self, py::dict) { return MemoryBuffer(self); })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("SetMemoryPolicy", &MemoryBuffer::SetMemoryPolicy, py::arg("nPolicy"))
        .def("GetMemoryPolicy", &MemoryBuffer::GetMemoryPolicy)
        .def("OwnsData", &MemoryBuffer::OwnsData)
        .def("GrowTo", &MemoryBuffer::GrowTo, py::arg("nSize"))
        .def("GetSize", &MemoryBuffer::GetSize)
        .def("GetData", py::overload_cast<>(&MemoryBuffer::GetData))
        .def("GetData", py::overload_cast<>(&MemoryBuffer::GetData, py::const_));
}
