#include "../headers.hh"
#include "SDICOS/IClientAuthentication.h"
#include "AuthenticationCallback.hh"

using namespace SDICOS;
using namespace Network;


class PyAuthenticationCallbackConnectionsSpecificClientApplications : public AuthenticationCallbackConnectionsSpecificClientApplications {
public:
   using AuthenticationCallbackConnectionsSpecificClientApplications::AuthenticationCallbackConnectionsSpecificClientApplications;
   bool OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad) const override { 
      PYBIND11_OVERRIDE(bool,  AuthenticationCallbackConnectionsSpecificClientApplications, OnAuthenticateClientApplicationName, ad); 
    }
};


class PyPublicAuthenticationCallbackConnectionsSpecificClientApplications : public AuthenticationCallbackConnectionsSpecificClientApplications {
public:
   using AuthenticationCallbackConnectionsSpecificClientApplications::OnAuthenticateClientApplicationName;
};


void export_AuthenticationCallbackConnectionsSpecificClientApplications(py::module &m)
{
   py::class_<AuthenticationCallbackConnectionsSpecificClientApplications, Network::IClientAuthenticationCallback>(m, "SDICOS::AuthenticationCallbackConnectsSpecificClientApps");
   py::class_<PyAuthenticationCallbackConnectionsSpecificClientApplications, AuthenticationCallbackConnectionsSpecificClientApplications, Network::IClientAuthenticationCallback>(m, "AuthenticationCallbackConnectsSpecificClientApps")
      .def(py::init<>())
      .def("OnAuthenticateClientApplicationName", py::overload_cast<const SDICOS::Utils::AuthenticationData&>
            (&PyPublicAuthenticationCallbackConnectionsSpecificClientApplications::OnAuthenticateClientApplicationName, py::const_),
            py::arg("ad"));
                                                                                                                                                             
}



class PyAuthenticationCallbackConnectionsFromClientsValidUserName : public AuthenticationCallbackConnectionsFromClientsValidUserName {
public:
   using AuthenticationCallbackConnectionsFromClientsValidUserName::AuthenticationCallbackConnectionsFromClientsValidUserName;
   bool OnIsUserNameValid(const SDICOS::DcsString &dsUserName) const override { 
      PYBIND11_OVERRIDE(bool,  AuthenticationCallbackConnectionsFromClientsValidUserName, OnIsUserNameValid, dsUserName); 
    }
};


class PyPublicAuthenticationCallbackConnectionsFromClientsValidUserName : public AuthenticationCallbackConnectionsFromClientsValidUserName {
public:
   using AuthenticationCallbackConnectionsFromClientsValidUserName::OnIsUserNameValid;
};


void export_AuthenticationCallbackConnectionsFromClientsValidUserName(py::module &m)
{
   py::class_<AuthenticationCallbackConnectionsFromClientsValidUserName, Network::IClientAuthenticationCallback>(m, "SDICOS::AuthenticationCallbackConnectionsFromClientsValidUserName");
   py::class_<PyAuthenticationCallbackConnectionsFromClientsValidUserName, AuthenticationCallbackConnectionsFromClientsValidUserName, Network::IClientAuthenticationCallback>(m, "AuthenticationCallbackConnectionsFromClientsValidUserName")
      .def(py::init<>())
      .def("OnIsUserNameValid", py::overload_cast<const SDICOS::DcsString&>
            (&PyPublicAuthenticationCallbackConnectionsFromClientsValidUserName::OnIsUserNameValid, py::const_),
            py::arg("dsUserName"));
                                                                                                                                                             
}