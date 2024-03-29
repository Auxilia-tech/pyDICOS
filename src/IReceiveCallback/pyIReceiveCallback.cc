#include "../headers.hh"
#include "SDICOS/IReceiveCallback.h"
#include "DataProcessing.hh"

using namespace SDICOS;
using namespace Network;


class PyIReceiveCallback : public IReceiveCallback {
public:
   using IReceiveCallback::IReceiveCallback;
    void  OnServerReady() override { PYBIND11_OVERRIDE(void,  IReceiveCallback,  OnServerReady); }
    void  OnReceiveDicosFileError(const ErrorLog & errolog, const Utils::SessionData & sessiondata) 
                                 override { PYBIND11_OVERRIDE_PURE(void, IReceiveCallback,  OnReceiveDicosFileError, errolog, sessiondata); }
    
};

class PyPublicIReceiveCallback : public IReceiveCallback {
public:
   using IReceiveCallback::OnServerReady;
   using IReceiveCallback::OnReceiveDicosFileError;
    
};

void export_IRECEIVECALLBACK(py::module &m)
{
     py::class_<Network::IReceiveCallback>(m, "Network::IReceiveCallback");
     py::class_<PyIReceiveCallback, Network::IReceiveCallback>(m, "IReceiveCallback")
        .def("ServerReady", &Network::IReceiveCallback::ServerReady)
        .def("ReceiveDicosFileError", &Network::IReceiveCallback::ReceiveDicosFileError, py::arg("errorlog"), py::arg("sessionsdata"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<AttributeManager>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("manager"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<CTModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ct"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<DXModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("dx"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<AIT2DModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ait2d"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<AIT3DModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ait3d"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<QRModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("qr"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<TDRModule>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("tdr"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<CT>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ct"),
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<DX>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("dx"), 
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<AIT2D>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ait"), 
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<AIT3D>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("ait"), 
                                  py::arg("errorlog"))
        .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<QR>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("qr"), 
                                  py::arg("errorlog"))
         .def("ReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<TDR>&, const ErrorLog&>(&Network::IReceiveCallback::ReceiveDicosFile), 
                                  py::arg("tdr"), 
                                  py::arg("errorlog"))
       
         .def("RecieveDicosEcho", &Network::IReceiveCallback::RecieveDicosEcho, py::arg("echo"), py::arg("errorlog"))
         .def("BeginSession", &Network::IReceiveCallback::BeginSession, py::arg("sessionsdata"))
         .def("EndSession", &Network::IReceiveCallback::EndSession, py::arg("sessionsdata"))
         .def("Connected", &Network::IReceiveCallback::Connected, py::arg("sessionsdata"))
         .def("Disconnected", &Network::IReceiveCallback::Disconnected, py::arg("sessionsdata"))

         .def("OnServerReady", &PyPublicIReceiveCallback::OnServerReady);
}