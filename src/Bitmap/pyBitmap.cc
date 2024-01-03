#include "../headers.hh"

#include "SDICOS/Bitmap.h"

using namespace SDICOS;


void export_BITMAP(py::module &m)
{
    py::class_<Bitmap>(m, "Bitmap")
        .def(py::init<>())
        .def(py::init<const S_UINT64>(), py::arg("numBits"))
        .def(py::init<const S_UINT64, const S_UINT64, const S_UINT64>(), py::arg("xDim"), py::arg("yDim"), py::arg("zDim"))
        .def("__copy__", [](const Bitmap &self) { return Bitmap(self); })
        .def("__deepcopy__", [](const Bitmap &self, py::dict) { return Bitmap(self); })
        .def("__assign__", (Bitmap& (Bitmap::*)(const Bitmap&)) &Bitmap::operator=)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("Compare", &Bitmap::Compare, py::arg("rhs"), py::arg("iNumBytesToCompare"))
        .def("GetBitmap", py::overload_cast<>(&Bitmap::GetBitmap))
        .def("GetBitmap", py::overload_cast<>(&Bitmap::GetBitmap, py::const_))
        .def("SetBitmapData", py::overload_cast<MemoryBuffer&, const bool>(&Bitmap::SetBitmapData), py::arg("mb"), py::arg("move") = false)
        .def("SetBitmapData", py::overload_cast<const MemoryBuffer&>(&Bitmap::SetBitmapData), py::arg("mb"))
        
        .def("SetBit", py::overload_cast<const S_UINT64, bool>(&Bitmap::SetBit), py::arg("bitIndex"),  py::arg("bit"))
        .def("SetBit", py::overload_cast<const S_UINT64, const S_UINT64, const S_UINT64, bool>(&Bitmap::SetBit), 
                                         py::arg("x"),  py::arg("y"),  py::arg("z"), py::arg("bit"))

        .def("GetBit", py::overload_cast<const S_UINT64, bool&>(&Bitmap::GetBit, py::const_), py::arg("bitIndex"),  py::arg("bit"))
        .def("GetBit", py::overload_cast<const S_UINT64, const S_UINT64, const S_UINT64, bool&>(&Bitmap::GetBit, py::const_), 
                                         py::arg("x"),  py::arg("y"),  py::arg("z"), py::arg("bit"))
        .def("GetBit", py::overload_cast<const S_UINT64>(&Bitmap::GetBit, py::const_), py::arg("bitIndex"))
        .def("GetBit", py::overload_cast<const S_UINT64, const S_UINT64, const S_UINT64>(&Bitmap::GetBit, py::const_), 
                                         py::arg("x"),  py::arg("y"),  py::arg("z"))
        .def("GetSize", py::overload_cast<>(&Bitmap::GetSize, py::const_))
        .def("SetDims", &Bitmap::SetDims, py::arg("x"), py::arg("y"), py::arg("z"), py::arg("bAllocateEvenNumberOfBytes") = false)   
        .def("GetDims", [](Bitmap &self, S_UINT32& x, S_UINT32& y, S_UINT32& z) { 
                           return std::make_tuple(self.GetDims(x, y, z), x, y, z);}, 
                           py::arg("x"), py::arg("y"), py::arg("z"))
        .def("GetDims", [](Bitmap &self, S_UINT64& x, S_UINT64& y, S_UINT64& z) { 
                           return std::make_tuple(self.GetDims(x, y, z), x, y, z);}, 
                           py::arg("x"), py::arg("y"), py::arg("z"))
        .def("GetNumBits", &Bitmap::GetNumBits) 
        .def("GetWidth", &Bitmap::GetWidth) 
        .def("GetHeight", &Bitmap::GetHeight)
        .def("GetDepth", &Bitmap::GetDepth);

}

