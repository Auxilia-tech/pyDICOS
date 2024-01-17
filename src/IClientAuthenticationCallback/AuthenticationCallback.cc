#include "AuthenticationCallback.hh"

bool AuthenticationCallbackConnectionsSpecificClientApplications::OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const
{
    return  ad.m_dsClientAppName == SDICOS::DcsString("ClientAppA") ||  //Allow connection from client with application name "ClientAppA"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppB") ||  //Allow connection from client with application name "ClientAppB"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppC") ||  //Allow connection from client with application name "ClientAppC"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppD");        //Allow connection from client with application name "ClientAppD"
}