#include "headers.hh"

PYBIND11_MODULE(pyDICOS, m)
{
   export_IMEMMANAGER(m);
   export_ERRORLOG(m);
   export_FS(m);
   export_CT(m);
   export_DCSSTRING(m);
   export_MEMORYBUFFER(m);
   export_ARRAY1D(m);
   //export_ARRAY1D<std::pair<bool, MemoryBuffer>>(m, "Array1DPairBoolMemBuff");
   //export_DX(m);
   //export_TDR(m);
}