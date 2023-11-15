#include "../headers.hh"

#include "CustomMemManager.hh"

class PyCustomMemoryManager : public CustomMemoryManager {
public:
    using CustomMemoryManager::CustomMemoryManager;
    bool OnAllocate(MemoryBuffer &mbAllocate, const S_UINT64 nSizeInBytesToAllocate) override { 
        PYBIND11_OVERRIDE(bool,  CustomMemoryManager, OnAllocate, mbAllocate, nSizeInBytesToAllocate); 
    }
    bool OnDeallocate(MemoryBuffer &mbDeallocate) override { 
        PYBIND11_OVERRIDE(bool,  CustomMemoryManager, OnDeallocate, mbDeallocate); 
    }
    MemoryBuffer::MEMORY_POLICY OnGetSliceMemoryPolicy() const override {
        PYBIND11_OVERRIDE( MemoryBuffer::MEMORY_POLICY,  CustomMemoryManager, OnGetSliceMemoryPolicy);
    }
};

void export_IMEMMANAGER(py::module &m)
{
    py::class_<IMemoryManager>(m, "IMemoryManager");
    py::class_<CustomMemoryManager>(m, "SDICOS::CustomMemoryManager");
    py::class_<PyCustomMemoryManager, CustomMemoryManager, IMemoryManager>(m, "CustomMemoryManager")
        .def(py::init<const S_UINT64, const S_UINT32>(), py::arg("m_nBufferSizeInBytes"), py::arg("nNumBuffersToAllocated"))
        .def("Allocate", py::overload_cast<MemoryBuffer&, const S_UINT64>
                     (&PyCustomMemoryManager::CustomMemoryManager::OnAllocate),
                     py::arg("mbAllocate"), 
                     py::arg("nSizeInBytesToAllocate"))
        .def("OnDeallocate", py::overload_cast<MemoryBuffer&>
                     (&PyCustomMemoryManager::CustomMemoryManager::OnDeallocate),
                     py::arg("mbDeallocate"))
        .def("OnGetSliceMemoryPolicy", py::overload_cast<>
                     (&PyCustomMemoryManager::CustomMemoryManager::OnGetSliceMemoryPolicy,  py::const_));
}
