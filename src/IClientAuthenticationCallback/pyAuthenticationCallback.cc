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






class PyAuthenticationCallbackClientsPresentValidUserNamePasscode : public AuthenticationCallbackClientsPresentValidUserNamePasscode {
public:
   using AuthenticationCallbackClientsPresentValidUserNamePasscode::AuthenticationCallbackClientsPresentValidUserNamePasscode;
   bool OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad) const override { 
      PYBIND11_OVERRIDE(bool,  AuthenticationCallbackClientsPresentValidUserNamePasscode, OnAuthenticateUserNameAndPasscode, ad); 
    }
};


class PyPublicAuthenticationCallbackClientsPresentValidUserNamePasscode : public AuthenticationCallbackClientsPresentValidUserNamePasscode {
public:
   using AuthenticationCallbackClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode;
};


void export_AuthenticationCallbackClientsPresentValidUserNamePasscode(py::module &m)
{
   py::class_<AuthenticationCallbackClientsPresentValidUserNamePasscode, Network::IClientAuthenticationCallback>(m, "SDICOS::AuthenticationCallbackClientsPresentValidUserNamePasscode");
   py::class_<PyAuthenticationCallbackClientsPresentValidUserNamePasscode, AuthenticationCallbackClientsPresentValidUserNamePasscode, Network::IClientAuthenticationCallback>(m, "AuthenticationCallbackClientsPresentValidUserNamePasscode")
      .def(py::init<>())
      .def("OnAuthenticateUserNameAndPasscode", py::overload_cast<const SDICOS::Utils::AuthenticationData &>
            (&PyPublicAuthenticationCallbackClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode, py::const_),
            py::arg("ad"));
                                                                                                                                                             
}




class PyAuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode : public AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode {
public:
   using AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode;
   bool OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad) const override { 
      PYBIND11_OVERRIDE(bool, AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode, OnAuthenticateUserNameAndPasscode, ad); 
    }
    bool OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad) const override { 
      PYBIND11_OVERRIDE(bool, AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode, OnAuthenticateClientApplicationName, ad); 
    }
};


class PyPublicAuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode : public AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode {
public:
   using AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode;
   using AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateClientApplicationName;
};


void export_AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode(py::module &m)
{
   py::class_<AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode, Network::IClientAuthenticationCallback>(m, "SDICOS::AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode");
   py::class_<PyAuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode, AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode, Network::IClientAuthenticationCallback>(m, "AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode")
      .def(py::init<>())
      .def("OnAuthenticateUserNameAndPasscode", py::overload_cast<const SDICOS::Utils::AuthenticationData &>
            (&PyPublicAuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode, py::const_),
            py::arg("ad"))

      .def("OnAuthenticateClientApplicationName", py::overload_cast<const SDICOS::Utils::AuthenticationData&>
            (&PyPublicAuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateClientApplicationName, py::const_),
            py::arg("ad"));
                                                                                                                                                             
}