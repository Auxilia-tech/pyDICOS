#include "../headers.hh"

#include "SDICOS/IClientAuthentication.h"

using namespace SDICOS;
using namespace Network;


class PyIClientAuthenticationCallback : public IClientAuthenticationCallback {
public:
   using IClientAuthenticationCallback::IClientAuthenticationCallback;
   bool  OnAuthenticateUserName(const Utils::AuthenticationData &ad) const
                                 override { PYBIND11_OVERRIDE(bool,  IClientAuthenticationCallback,  OnAuthenticateUserName, ad); }
   bool  OnAuthenticateUserNameAndPasscode(const Utils::AuthenticationData &ad) const
                                 override { PYBIND11_OVERRIDE(bool,  IClientAuthenticationCallback,  OnAuthenticateUserNameAndPasscode, ad); }
   bool  OnAuthenticateClientApplicationName(const Utils::AuthenticationData &ad) const
                                 override { PYBIND11_OVERRIDE(bool,  IClientAuthenticationCallback,  OnAuthenticateClientApplicationName, ad); }  
   void  OnConnectedToClient(const Utils::SessionData &sd) 
                                 override { PYBIND11_OVERRIDE(void,  IClientAuthenticationCallback,  OnConnectedToClient, sd); }                               
   void  OnDisconnectedFromClient(const Utils::SessionData &sd) 
                                 override { PYBIND11_OVERRIDE(void,  IClientAuthenticationCallback,  OnDisconnectedFromClient, sd); }
   void  OnDicosConnectionStarted(const Utils::SessionData &sd) 
                                 override { PYBIND11_OVERRIDE(void,  IClientAuthenticationCallback,  OnDicosConnectionStarted, sd); }
   void  OnDicosConnectionStopped(const Utils::SessionData &sd) 
                                 override { PYBIND11_OVERRIDE(void,  IClientAuthenticationCallback,  OnDicosConnectionStopped, sd); }


};



class PyPublicIClientAuthenticationCallback: public IClientAuthenticationCallback {
public:
   using IClientAuthenticationCallback::OnAuthenticateUserName;
   using IClientAuthenticationCallback::OnAuthenticateUserNameAndPasscode;
   using IClientAuthenticationCallback::OnAuthenticateClientApplicationName;
   using IClientAuthenticationCallback::OnConnectedToClient;
   using IClientAuthenticationCallback::OnDisconnectedFromClient;
   using IClientAuthenticationCallback::OnDicosConnectionStarted;
   using IClientAuthenticationCallback::OnDicosConnectionStopped;
    
};


void export_ICLIENTAUTHENTICATIONCALLBACK(py::module &m)
{
   py::class_<Network::IClientAuthenticationCallback>(m, "IClientAuthenticationCallback")
      .def("AuthenticateUserName", &Network::IClientAuthenticationCallback::AuthenticateUserName, py::arg("ad"))
      .def("AuthenticateUserNameAndPasscode", &Network::IClientAuthenticationCallback::AuthenticateUserNameAndPasscode, py::arg("ad"))
      .def("AuthenticateClientApplicationName", &Network::IClientAuthenticationCallback::AuthenticateClientApplicationName, py::arg("ad"))
      .def("ConnectedToClient", &Network::IClientAuthenticationCallback::ConnectedToClient, py::arg("sd"))
      .def("DisconnectedFromClient", &Network::IClientAuthenticationCallback::DisconnectedFromClient, py::arg("sd"))
      .def("DicosConnectionStarted", &Network::IClientAuthenticationCallback::DicosConnectionStarted, py::arg("sd"))
      .def("DicosConnectionStopped", &Network::IClientAuthenticationCallback::DicosConnectionStopped, py::arg("sd"))

      .def("OnAuthenticateUserName", py::overload_cast<const Utils::AuthenticationData &>
                                     (&PyPublicIClientAuthenticationCallback::OnAuthenticateUserName, py::const_),
                                     py::arg("ad"))
      .def("OnAuthenticateUserNameAndPasscode", py::overload_cast<const Utils::AuthenticationData &>
                                     (&PyPublicIClientAuthenticationCallback::OnAuthenticateUserNameAndPasscode, py::const_),
                                     py::arg("ad"))
      .def("OnAuthenticateClientApplicationName", py::overload_cast<const Utils::AuthenticationData &>
                                     (&PyPublicIClientAuthenticationCallback::OnAuthenticateClientApplicationName, py::const_),
                                     py::arg("ad"))
      .def("OnConnectedToClient", py::overload_cast<const Utils::SessionData &>
                                     (&PyPublicIClientAuthenticationCallback::OnConnectedToClient),
                                     py::arg("sd"))
      .def("OnDisconnectedFromClient", py::overload_cast<const Utils::SessionData &>
                                     (&PyPublicIClientAuthenticationCallback::OnDisconnectedFromClient),
                                     py::arg("sd"))
      .def("OnDicosConnectionStarted", py::overload_cast<const Utils::SessionData &>
                                     (&PyPublicIClientAuthenticationCallback::OnDicosConnectionStarted),
                                     py::arg("sd")) 
      .def("OnDicosConnectionStopped", py::overload_cast<const Utils::SessionData &>
                                     (&PyPublicIClientAuthenticationCallback::OnDicosConnectionStopped),
                                     py::arg("sd")); 

}
 