#include "headers.hh"
#include "Vector3D/pyVector3D.hh"
#include "Array3DLarge/Array3DLarge.hh"
#include "Array2D/pyArray2D.hh"
#include "Array1D/pyArray1D.hh"

PYBIND11_MODULE(pyDICOS, m)
{
   export_IMEMMANAGER(m);
   export_ERRORLOG(m);
   export_FS(m);
   export_SECTION(m);
   export_CT(m);
   export_DCSSTRING(m);
   export_MEMORYBUFFER(m);
   export_Array1D<S_UINT16>(m, "S_UINT16");
   export_Array1D<std::pair<bool, MemoryBuffer>>(m, "PairBoolMemBuff");
   export_Array2D<float>(m, "float");
   export_Array1DArray2D<float>(m, "float");
   export_Array1DArray2D<S_UINT16>(m, "S_UINT16");
   //export_Array1DArray2DPointer<S_UINT16>(m, "S_UINT16");
   //export_Array1D<Array2D<float>*>(m, "Array1DArray2DFloat");
   export_Array2D<S_UINT16>(m, "S_UINT16");
   export_VECTOR3D<float>(m, "float");
   export_Volume(m);
   export_Array3DLarge<S_UINT16>(m, "S_UINT16");
   //export_DX(m);
   //export_TDR(m);
}