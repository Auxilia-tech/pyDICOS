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


void export_ICLIENTAUTHENTIFICATIONCALLBACK(py::module &m)
{
   py::class_<Network::IClientAuthenticationCallback>(m, "IClientAuthenticationCallback")
      .def("AuthenticateUserName", &Network::IClientAuthenticationCallback::AuthenticateUserName, py::arg("ad"))
      .def("AuthenticateUserNameAndPasscode", &Network::IClientAuthenticationCallback::AuthenticateUserNameAndPasscode, py::arg("ad"))
      .def("AuthenticateClientApplicationName", &Network::IClientAuthenticationCallback::AuthenticateClientApplicationName, py::arg("ad"))
      .def("ConnectedToClient", &Network::IClientAuthenticationCallback::ConnectedToClient, py::arg("sd"))
      .def("DisconnectedFromClient", &Network::IClientAuthenticationCallback::DisconnectedFromClient, py::arg("sd"))
      .def("DicosConnectionStarted", &Network::IClientAuthenticationCallback::DicosConnectionStarted, py::arg("sd"))
      .def("DicosConnectionStopped", &Network::IClientAuthenticationCallback::DicosConnectionStopped, py::arg("sd"));
}
