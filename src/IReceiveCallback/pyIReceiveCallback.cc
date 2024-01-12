#include "../headers.hh"

#include "SDICOS/IReceiveCallback.h"

using namespace SDICOS;

void export_IRECEIVECALLBACK(py::module &m)
{
     py::class_<Network::IReceiveCallback>(m, "IReceiveCallback");
        .def("ServerReady", &Network::IReceiveCallback::ServerReady)
        .def("ReceiveDicosFileError", &Network::IReceiveCallback::ReceiveDicosFileError, py::arg("errorlog"), py::arg("sessionsdata"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<CT>, ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ct")
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<DX>, ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("dx"), 
                                  py::arg("errorlog"))
         .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<TDR>, ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("tdr"), 
                                  py::arg("errorlog"))
         .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<S_UINT8>, ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("echo"), 
                                  py::arg("errorlog"));
}
