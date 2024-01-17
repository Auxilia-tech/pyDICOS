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