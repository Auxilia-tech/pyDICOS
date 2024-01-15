#include "../headers.hh"

#include "SDICOS/Host.h"

using namespace SDICOS;

void export_DCSSERVER(py::module &m)
{
   py::class_<Network::IDcsServer>(m, "IDcsServer");
   py::class_<Network::DcsServer, Network::IDcsServer>(m, "DcsServer")
      .def(py::init<>())
      .def("SetReadTimeoutInMilliseconds", &Network::DcsServer::SetReadTimeoutInMilliseconds, py::arg("nTimeoutMilliseconds") = 1000)
      .def("GetReadTimeoutInMilliseconds", &Network::DcsServer::GetReadTimeoutInMilliseconds)
      .def("SetWriteTimeoutInMilliseconds", &Network::DcsServer::SetWriteTimeoutInMilliseconds, py::arg("nTimeoutMilliseconds")  = 1000)
      .def("GetWriteTimeoutInMilliseconds", &Network::DcsServer::GetWriteTimeoutInMilliseconds)
      .def("SetIP", &Network::DcsServer::SetIP, py::arg("ds"))
      .def("GetIP", &Network::DcsServer::GetIP)
      .def("SetPort", &Network::DcsServer::SetPort, py::arg("nPort"))
      .def("GetPort", &Network::DcsServer::GetPort)
      .def("SetApplicationName", &Network::DcsServer::SetApplicationName, py::arg("ae"))
      .def("GetApplicationName", &Network::DcsServer::GetApplicationName)
      .def("RequireApplicationNames", &Network::DcsServer::RequireApplicationNames)
      .def("IgnoreApplicationNames", &Network::DcsServer::IgnoreApplicationNames)
      .def("IsConnectionFromApplicationEnabled", &Network::DcsServer::IsConnectionFromApplicationEnabled, py::arg("ae"))
      .def("SetSslCertificate", py::overload_cast<const DcsString&, const DcsString&, const DcsString&, ErrorLog&>(&Network::DcsServer::SetSslCertificate), 
                                  py::arg("dsFilenamePFX"), 
                                  py::arg("dsPassword"),
                                  py::arg("dsCN"),
                                  py::arg("errorlog"))
      .def("SetSslCertificate", py::overload_cast<const DcsString&, const DcsString&, ErrorLog&>(&Network::DcsServer::SetSslCertificate), 
                                  py::arg("dsFilenamePFX"), 
                                  py::arg("dsPassword"),
                                  py::arg("errorlog"))
      .def("IsUsingSsl", &Network::DcsServer::IsUsingSsl)
      .def("SetTLSClientCertificateRequired", &Network::DcsServer::SetTLSClientCertificateRequired, py::arg("bRequired"))
      .def("IsTLSClientCertificateRequired", &Network::DcsServer::IsTLSClientCertificateRequired)
      .def("SetSslAllowedCiphers", &Network::DcsServer::SetSslAllowedCiphers, py::arg("dsAllowedCiphers"))
      .def("GetSslAllowedCiphers", &Network::DcsServer::GetSslAllowedCiphers)
      .def("GetTlsCipherSuite", &Network::DcsServer::GetTlsCipherSuite)
      .def("AllowAllCients", &Network::DcsServer::AllowAllCients)
      .def("RequireUserNameFromClient", &Network::DcsServer::RequireUserNameFromClient)
      .def("RequireUserNameAndPasscodeFromClient", &Network::DcsServer::RequireUserNameAndPasscodeFromClient)
      .def("IsValidUserNameAndPasscode", &Network::DcsServer::IsValidUserNameAndPasscode, py::arg("dsUserName"), py::arg("dsPasscode"))
      .def("IsValidUserName", &Network::DcsServer::IsValidUserName, py::arg("dsUserName"))
      .def("DisableDataCompression", &Network::DcsServer::DisableDataCompression)
      .def("IsDataCompressionDisabled", &Network::DcsServer::IsDataCompressionDisabled)
      .def("StartListening", &Network::DcsServer::StartListening, py::arg("icallback"), py::arg("pIClientVerificationCallback") = S_NULL, py::arg("nPreferAPI"), py::arg("bProcessDataOnSessionEnd") = false)
      .def("UpdateCallback", py::overload_cast<Network::IReceiveCallback&>(&Network::DcsServer::UpdateCallback), 
                                  py::arg("icallback"))
      .def("UpdateCallback", py::overload_cast<const Network::IDcsServer::RETRIEVE_METHOD>(&Network::DcsServer::UpdateCallback), 
                                  py::arg("nPreferAPI"))
      .def("StopListening", &Network::DcsServer::StopListening)
      .def("IsBusy", &Network::DcsServer::IsBusy)
      .def("IsIdle", &Network::DcsServer::IsIdle)
      .def("IsActivelyAcceptingConnections", &Network::DcsServer::IsActivelyAcceptingConnections)
      .def("WaitForThreadToComplete", &Network::DcsServer::WaitForThreadToComplete)
      .def("TerminateConnectionWithDevice", &Network::DcsServer::TerminateConnectionWithDevice, py::arg("dsIP"))
      .def("GetConnectedDevices", &Network::DcsServer::GetConnectedDevices, py::arg("vClientIPs"))
      .def("GetConnectedDevicesWithActiveDicosSessions", &Network::DcsServer:: GetConnectedDevicesWithActiveDicosSessions, py::arg("vClientIPs"))
      .def("IncludeSopClassUID", &Network::DcsServer::IncludeSopClassUID, py::arg("uidSopClassUID"))
      .def("ResetIncludedSopClassUIDs", &Network::DcsServer::ResetIncludedSopClassUIDs)
      .def("GetListOfSupportedSopClassUIDs", &Network::DcsServer::GetListOfSupportedSopClassUIDs, py::arg("vSopClassUIDs"))
      .def("SetCustomAllocators", &Network::DcsServer::SetCustomAllocators, py::arg("apiAllocators"))
      .def("GetErrorLog", &Network::DcsServer::GetErrorLog, py::arg("dsErrorLog"));

      
      
}
