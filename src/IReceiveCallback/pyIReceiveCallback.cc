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



class PyDataProcessing : public DataProcessing {
public:
   using DataProcessing::DataProcessing;
   void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFileError, errorlog, sessiondata); 
   }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, manager, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, ct, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, dx, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr,  const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosFile, tdr, errorlog); 
    }

   void OnReceiveDicosEcho(const SDICOS::Utils::SessionData& sessiondata,  const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessing, OnReceiveDicosEcho, sessiondata, errorlog); 
    }
};


class PyPublicDataProcessing : public DataProcessing {
public:
   using DataProcessing::OnReceiveDicosFileError;
   using DataProcessing::OnReceiveDicosFile;
    
};


void export_DataProcessing(py::module &m)
{
   py::class_<PyDataProcessing, Network::IReceiveCallback>(m, "DataProcessing")
      .def("OnReceiveDicosFileError", py::overload_cast<const SDICOS::ErrorLog&, const SDICOS::Utils::SessionData&>
                                      (&PyPublicDataProcessing::OnReceiveDicosFileError),
                                      py::arg("errorlog"), 
                                      py::arg("sessiondata"));
}