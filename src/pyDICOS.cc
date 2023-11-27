#include "headers.hh"
#include "Vector3D/pyVector3D.hh"

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
   export_VECTOR3D<char>(m, "char");
   export_VECTOR3D<int>(m, "int");
   //export_DX(m);
   //export_TDR(m);
}