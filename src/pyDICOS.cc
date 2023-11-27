#include "headers.hh"
#include "Vector3D/pyVector3D.hh"
#include "Array3DLarge/Array3DLarge.hh"

PYBIND11_MODULE(pyDICOS, m)
{
   export_IMEMMANAGER(m);
   export_ERRORLOG(m);
   export_FS(m);
   export_SECTION(m);
   export_CT(m);
   export_DCSSTRING(m);
   export_MEMORYBUFFER(m);
   export_ARRAY1D(m);
   export_VECTOR3D<float>(m, "float");
   export_Volume(m);
   export_Array3DLarge<S_UINT16>(m, "S_UINT16");
   //export_DX(m);
   //export_TDR(m);
}