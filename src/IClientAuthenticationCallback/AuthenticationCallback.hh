#ifndef DATAPROCESSING_FILE_H
#define DATAPROCESSING_FILE_H

#include "SDICOS/DICOS.h" 

using namespace SDICOS;

class AuthenticationCallbackConnectionsSpecificClientApplications : public Network::IClientAuthenticationCallback
{
protected:
   virtual bool OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const;
};

class AuthenticationCallbackConnectionsFromClientsValidUserName : public Network::IClientAuthenticationCallback
{
protected:
   virtual bool OnIsUserNameValid(const SDICOS::DcsString &dsUserName)const;
};


#endif