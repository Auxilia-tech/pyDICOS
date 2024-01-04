#include "headers.hh"
#include "Vector3D/pyVector3D.hh"
#include "Array3DLarge/Array3DLarge.hh"
#include "Array2D/pyArray2D.hh"
#include "Array1D/pyArray1D.hh"
#include "Point3D/pyPoint3D.hh"
#include "SDICOS/ErrorLog.h"
#include "SDICOS/FileSystem.h"

PYBIND11_MODULE(pyDICOS, m)
{
   export_IMEMMANAGER(m);
   export_ERRORLOG(m);
   export_FS(m);
   export_DicosFileListing(m);
   export_SECTION(m);
   export_CT(m);
   export_DCSSTRING(m);
   export_MEMORYBUFFER(m);
   export_Array1D<S_UINT16>(m, "S_UINT16");
   export_Array1D<S_INT16>(m, "S_INT16");
   export_Array1D<S_UINT8>(m, "S_UINT8");
   export_Array1D<S_INT8>(m, "S_INT8");
   export_Array1D<float>(m, "float");

   export_Array1DPoint3D<float>(m, "float");
   export_Array1DDcsLongString(m);
   export_Array1DArray2D<float>(m, "float");
   export_Array1DArray2D<S_UINT16>(m, "S_UINT16");
   export_CustomArray1DDcsLongString(m);

   export_Array2D<S_UINT8>(m, "S_UINT8");
   export_Array2D<S_UINT16>(m, "S_UINT16");
   export_Array2D<S_UINT32>(m, "S_UINT32");
   export_Array2D<S_UINT64>(m, "S_UINT64");
   export_Array2D<S_INT8>(m, "S_INT8");
   export_Array2D<S_INT16>(m, "S_INT16");
   export_Array2D<S_INT32>(m, "S_INT32");
   export_Array2D<S_INT64>(m, "S_INT64");
   export_Array2D<float>(m, "float");

   export_Point3D<float>(m, "float");
   export_Point3D<S_UINT16>(m, "S_UINT16");
   export_Point3D<S_INT16>(m, "S_INT16");
   export_Point3D<S_UINT8>(m, "S_UINT8");
   export_Point3D<S_INT8>(m, "S_INT8");

   export_VECTOR3D<float>(m, "float");
   export_VECTOR3D<S_UINT16>(m, "S_UINT16");
   export_VECTOR3D<S_INT16>(m, "S_INT16");
   export_VECTOR3D<S_UINT8>(m, "S_UINT8");
   export_VECTOR3D<S_INT8>(m, "S_INT8");

   export_Volume(m);

   export_Array3DLarge<float>(m, "float");
   export_Array3DLarge<S_UINT16>(m, "S_UINT16");
   export_Array3DLarge<S_INT16>(m, "S_INT16");
   export_Array3DLarge<S_UINT8>(m, "S_UINT8");
   export_Array3DLarge<S_INT8>(m, "S_INT8");
   
   export_DX(m);
   export_TDR(m);
   export_Image2D(m);
   export_BITMAP(m);
   export_DCSGUID(m);
   export_SopClassUID(m);

   export_GeneralSeriesModule(m);
}