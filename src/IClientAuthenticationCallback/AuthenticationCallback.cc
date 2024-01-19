#include "AuthenticationCallback.hh"

bool AuthenticationCallbackConnectionsSpecificClientApplications::OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const
{
    return  ad.m_dsClientAppName == SDICOS::DcsString("ClientAppA") ||  //Allow connection from client with application name "ClientAppA"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppB") ||  //Allow connection from client with application name "ClientAppB"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppC") ||  //Allow connection from client with application name "ClientAppC"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppD");        //Allow connection from client with application name "ClientAppD"
}

bool AuthenticationCallbackConnectionsFromClientsValidUserName::OnIsUserNameValid(const SDICOS::DcsString &dsUserName)const
{
    return  dsUserName == SDICOS::DcsString("UserA") || //Allow clients with the user name "UserA"
            dsUserName == SDICOS::DcsString("UserB") || //Allow clients with the user name "UserB"
            dsUserName == SDICOS::DcsString("UserC");   //Allow clients with the user name "UserC"
}


bool AuthenticationCallbackClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const
{
 return (ad.m_dsUserName == SDICOS::DcsString("UserA") && ad.m_dsPasscode == SDICOS::DcsString("Pass0A")) ||
        (ad.m_dsUserName == SDICOS::DcsString("UserB") && ad.m_dsPasscode == SDICOS::DcsString("Pass0B")) ||
        (ad.m_dsUserName == SDICOS::DcsString("UserC") && ad.m_dsPasscode == SDICOS::DcsString("Pass0C"));
}


bool AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const
{
 return (ad.m_dsUserName == SDICOS::DcsString("UserA") && ad.m_dsPasscode == SDICOS::DcsString("Pass0A")) ||
        (ad.m_dsUserName == SDICOS::DcsString("UserB") && ad.m_dsPasscode == SDICOS::DcsString("Pass0B")) ||
        (ad.m_dsUserName == SDICOS::DcsString("UserC") && ad.m_dsPasscode == SDICOS::DcsString("Pass0C"));
}

bool AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode::OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const
{
    return  ad.m_dsClientAppName == SDICOS::DcsString("ClientAppA") ||  //Allow connection from client with application name "ClientAppA"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppB") ||  //Allow connection from client with application name "ClientAppB"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppC") ||  //Allow connection from client with application name "ClientAppC"
            ad.m_dsClientAppName == SDICOS::DcsString("ClientAppD");    //Allow connection from client with application name "ClientAppD"

}

