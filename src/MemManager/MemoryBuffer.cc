#include "../headers.hh"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "SDICOS/MemoryBuffer.h"

namespace py = pybind11;
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
        .def("GrowToSafe", &MemoryBuffer::GrowToSafe, py::arg("nSize"))
        .def("GetSize", &MemoryBuffer::GetSize)
        .def("FreeMemory", &MemoryBuffer::FreeMemory)
        .def("SetBuffer", [](MemoryBuffer &self, py::buffer pBuffer, size_t nSize) {
            py::buffer_info info = pBuffer.request();
            if (info.ndim != 1 || info.format != py::format_descriptor<unsigned char>::format()) {
                throw std::runtime_error("Expected a buffer of unsigned char type and one dimension");
            }
            unsigned char* new_data = new unsigned char[nSize];
            std::memcpy(new_data, info.ptr, nSize);
            self.SetBuffer(new_data, nSize);
            self.SetMemoryPolicy(MemoryBuffer::MEMORY_POLICY::enumPolicy_OwnsData);
        }, py::arg("pBuffer"), py::arg("nSize"))
        .def_static("Move", &MemoryBuffer::Move, py::arg("membuffDest"), py::arg("membuffSrc"))
        .def_buffer([](MemoryBuffer &m) -> py::buffer_info {
            auto size = m.GetSize();
            auto *data = m.GetData();
            return py::buffer_info(
                data,                           // Pointer to buffer
                sizeof(unsigned char),          // Size of one scalar
                py::format_descriptor<unsigned char>::format(), // Python struct-style format descriptor
                1,                              // Number of dimensions
                { size },                       // Buffer dimensions
                { sizeof(unsigned char) }       // Strides (in bytes) for each index
            );
        });
}

PYBIND11_MODULE(example_module, m) {
    export_MEMORYBUFFER(m);
}

