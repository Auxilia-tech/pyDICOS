#include "headers.hh"

PYBIND11_MODULE(pyDICOS, m)
{
   export_FS(m);
   export_CT(m);
   //export_DX(m);
   //export_TDR(m);
}