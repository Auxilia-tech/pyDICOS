//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
///
/// Permission to use, copy, modify, and distribute this software and its
/// documentation without a signed licensing agreement, is hereby granted,
/// provided that this copyright notice, this paragraph and the following two
/// paragraphs appear in all copies, modifications, and distributions.
///
/// IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
/// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
/// ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
/// STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
/// TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
/// SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
/// PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
/// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS UNLESS DIRECTED BY THE
/// U.S. GOVERNMENT'S TRANSPORTATION SECURITY ADMINISTRATION (TSA).
///
//////////////////////////////////////////////////////////////////////////////
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_ICLIENT_AUTHENTICATION_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_ICLIENT_AUTHENTICATION_H_

#include "SDICOS/Utils.h"

namespace SDICOS
{
namespace Network
{

/// \class IClientAuthenticationCallback
/// \brief	Callback interface for user name and passcode authentication. Functions called when a connecting client
///			presents a required user name and/or passcode.  All functions are asynchronous as they are called from a
///			separate thread.
class IClientAuthenticationCallback
{
public:

	/// Called when the server must authenticate a user name
	bool AuthenticateUserName(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Called when the server must authenticate a user name and passcode
	bool AuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Called when the server must authenticate the client's application name
	bool AuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Called when a client connects to a server (TCP/IP connection, not a DICOS session)
	void ConnectedToClient(const SDICOS::Utils::SessionData &sd);
	/// Called when a client disconnects from a server (TCP/IP connection, not a DICOS session)
	void DisconnectedFromClient(const SDICOS::Utils::SessionData &sd);

	/// Called after client authentication
	void DicosConnectionStarted(const SDICOS::Utils::SessionData &sd);
	/// Called when the DICOS session ends
	void DicosConnectionStopped(const SDICOS::Utils::SessionData &sd);
protected:

	/// Override to authenticate user name. Return true if the user name is accepted. Return false if user name is rejected.
	/// An accepted user name allows the client to connect to the server and process received data. A rejected user name
	///	prevents the client from connecting to the server.
	/// If not overridden, function passes calls to OnAuthenticateUserNameAndPasscode with an empty passcode
	virtual bool OnAuthenticateUserName(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Override to authenticate user name. Return true if the user name and passcode is accepted. Return false if user name 
	/// and passcode is rejected. An accepted user name and passcode allows the client to connect to the server and 
	/// process received data. A rejected user name and passcode prevents the client from connecting to the server.
	virtual bool OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Override to authenticate the client's application name
	/// Length Restriction: 16 characters maximum for application name
	virtual bool OnAuthenticateClientApplicationName(const SDICOS::Utils::AuthenticationData &ad)const;

	/// Override to receive notification when a client has connected with the server (TCP/IP connection)
	virtual void OnConnectedToClient(const SDICOS::Utils::SessionData &sd);
	/// Override to receive notification when a client has disconnected from the server (TCP/IP connection)
	virtual void OnDisconnectedFromClient(const SDICOS::Utils::SessionData &sd);

	/// Override to receive notification when a client has started a DICOS connection
	virtual void OnDicosConnectionStarted(const SDICOS::Utils::SessionData &sd);
	/// Override to receive notification when a client has stopped a DICOS connection
	virtual void OnDicosConnectionStopped(const SDICOS::Utils::SessionData &sd);
};

}// namespace Network
}// namespace SDICOS

#endif