#include "../headers.hh"

#include "SDICOS/Client.h"

using namespace SDICOS;



     typedef enum
     {
         enumSopCT               = 1,    ///< CT (8-64 bit, 32 bit float)
         enumSopAIT2D            = 1<<1, ///< AIT 2D (8-64 bit, 32 bit float)
         enumSopAIT3D            = 1<<2, ///< AIT 3D (8-64 bit, 32 bit float)
         enumSopDXProcessing     = 1<<3, ///< DX for processing (8-64 bit, 32 bit float)
         enumSopDXPresentation   = 1<<4, ///< DX for presentation (8-64 bit, 32 bit float)
         enumSopDX               = (enumSopDXProcessing | enumSopDXPresentation),    ///< DX for processing and DX for presentation (8-64 bit, 32 bit float)
         enumSopQR               = 1<<5, ///< QR
         enumSopTDR              = 1<<6, ///< TDR
  
         enumSopEcho             = 1<<7, ///< C-Echo
  
         enumSopAIT2DTDR         = enumSopAIT2D | enumSopTDR,    ///< AIT 2D and TDR
         enumSopAIT3DTDR         = enumSopAIT3D | enumSopTDR,    ///< AIT 2D and TDR (8-64 bit, 32 bit float)
         enumSopCTTDR            = enumSopCT | enumSopTDR,       ///< CT and TDR (8-64 bit, 32 bit float)
         enumSopDXTDR            = enumSopDX | enumSopTDR,       ///< DX and TDR (8-64 bit, 32 bit float)
         enumSopQRTDR            = enumSopQR | enumSopTDR,       ///< DX and TDR (8-64 bit, 32 bit float)
  
         enumSopAll              = enumSopCT | enumSopAIT2D | enumSopAIT3D | enumSopDX | enumSopQR | enumSopTDR | enumSopEcho,   ///< All SOP class UID's
     }SOPCLASSUID;

void export_DCSCLIENT(py::module &m)
{
     py::enum_<Network::DcsClient::SOPCLASSUID>(m, "SOPCLASSUID")
        .value("enumSopCT", Network::DcsClient::SOPCLASSUID::enumSopCT)
        .value("enumSopAIT2D", Network::DcsClient::SOPCLASSUID::enumSopAIT2D)
        .value("enumSopAIT3D", Network::DcsClient::SOPCLASSUID::enumSopAIT3D)
        .value("enumSopDXProcessing", Network::DcsClient::SOPCLASSUID::enumSopDXProcessing)
        .value("enumSopDXPresentation", Network::DcsClient::SOPCLASSUID::enumSopDXPresentation)
        .value("enumSopDX", Network::DcsClient::SOPCLASSUID::enumSopDX)
        .value("enumSopQR", Network::DcsClient::SOPCLASSUID::enumSopQR)
        .value("enumSopTDR", Network::DcsClient::SOPCLASSUID::enumSopTDR)
        .value("enumSopEcho", Network::DcsClient::SOPCLASSUID::enumSopEcho)
        .value("enumSopAIT2DTDR", Network::DcsClient::SOPCLASSUID::enumSopAIT2DTDR)
        .value("enumSopAIT3DTDR", Network::DcsClient::SOPCLASSUID::enumSopAIT3DTDR)
        .value("enumSopCTTDR", Network::DcsClient::SOPCLASSUID::enumSopCTTDR)
        .value("enumSopDXTDR", Network::DcsClient::SOPCLASSUID::enumSopDXTDR)
        .value("enumSopQRTDR", Network::DcsClient::SOPCLASSUID::enumSopQRTDR)
        .value("enumSopAll", Network::DcsClient::SOPCLASSUID::enumSopAll)
        .export_values();

     py::class_<Network::IClient>(m, "IClient");
     py::class_<Network::DcsClient, Network::IClient>(m, "DcsClient")
        .def_property_readonly_static("SOPCLASSUID", [m](py::object) {
            return m.attr("SOPCLASSUID");
        })  
        .def(py::init<>())
        .def(py::init<const Network::DcsClient&>(), py::arg("client"))
        .def("__assign__", (Network::DcsClient& (Network::DcsClient::*)(const Network::DcsClient&)) &Network::DcsClient::operator=)
        .def("SetServerPortandIP", &Network::DcsClient::SetServerPortandIP, py::arg("nPort"), py::arg("dsIP"))
        .def("GetPort", &Network::DcsClient::GetPort)
        .def("GetServerIP", &Network::DcsClient::GetServerIP)
        .def("SetClientIP", &Network::DcsClient::SetClientIP, py::arg("dsIP"))
        .def("GetClientIP", &Network::DcsClient::GetClientIP)
        .def("SetReadTimeoutInMilliseconds", &Network::DcsClient::SetReadTimeoutInMilliseconds, py::arg("nTimeoutMilliseconds") = 1000)
        .def("GetReadTimeoutInMilliseconds", &Network::DcsClient::GetReadTimeoutInMilliseconds)
        .def("SetWriteTimeoutInMilliseconds", &Network::DcsClient::SetWriteTimeoutInMilliseconds, py::arg("nTimeoutMilliseconds")  = 1000)
        .def("GetWriteTimeoutInMilliseconds", &Network::DcsClient::GetWriteTimeoutInMilliseconds)
        .def("SetSourceApplication", &Network::DcsClient::SetSourceApplication, py::arg("aeSrc"))
        .def("GetSourceApplication", &Network::DcsClient::GetSourceApplication)
        .def("SetDestinationApplication", &Network::DcsClient::SetDestinationApplication, py::arg("aeDst"))
        .def("GetDestinationApplication", &Network::DcsClient::GetDestinationApplication)
        .def("Echo", &Network::DcsClient::Echo)
        .def("GetResult", &Network::DcsClient::GetResult)
        .def("GetErrorLog", &Network::DcsClient::GetErrorLog)
        .def("ConnectToServer", &Network::DcsClient::ConnectToServer)
        .def("DisconnectFromServer", &Network::DcsClient::DisconnectFromServer)
        .def("IsConnectedToServer", &Network::DcsClient::IsConnectedToServer)
        .def("StartDicosSession", &Network::DcsClient::StartDicosSession, py::arg("nSopClassUIDs"))
        .def("StopDicosSession", &Network::DcsClient::StopDicosSession)
        .def("DisableDataCompression", &Network::DcsClient::DisableDataCompression)
        .def("IsDataCompressionDisabled", &Network::DcsClient::IsDataCompressionDisabled);
}
