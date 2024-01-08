#include "../headers.hh"

#include "SDICOS/Client.h"

using namespace SDICOS;


void export_DCSCLIENT(py::module &m)
{
     py::class_<Network::IClient>(m, "IClient");
     py::class_<Network::DcsClient, Network::IClient>(m, "DcsClient")
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
        .def("IsConnectedToServer", &Network::DcsClient::IsConnectedToServer);
}