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
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_IRECEIVE_CALLBACK_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_IRECEIVE_CALLBACK_H_

#include "SDICOS/ErrorLog.h"
#include "SDICOS/Utils.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ModuleCT.h"
#include "SDICOS/ModuleAIT2D.h"
#include "SDICOS/ModuleAIT3D.h"
#include "SDICOS/ModuleDX.h"
#include "SDICOS/ModuleQR.h"
#include "SDICOS/ModuleTDR.h"

namespace SDICOS
{

class AIT2D;
class AIT3D;
class CT;
class DX;
class QR;
class TDR;

namespace Network
{

/// \class IReceiveCallback
/// \brief	Interface for callback functions used by DcsClient and DcsServer. Each function is a blocking call for the next DICOS data
///			to be processed. Once an OnReceive function exits, the next DICOS data can be received by this callback interface.
class IReceiveCallback
{
public:

	/// Called when the server is ready to receive client connections
	void ServerReady();

	/// Called after a client session completes
	void ReceiveDicosFileError(const ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata); 

	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<AttributeManager> &manager, const SDICOS::ErrorLog&errorlog);

	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<CTModule> &ct, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<DXModule> &dx, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<AIT2DModule> &ait2d, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<AIT3DModule> &ait3d, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<QRModule> &qr, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<TDRModule> &tdr, const SDICOS::ErrorLog&errorlog);

	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog&errorlog);
	/// Called after retrieving all DICOS files from C-Store
	void ReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog&errorlog);

	/// Called after receiving a C-Echo
	void RecieveDicosEcho(SDICOS::Utils::DicosData<S_UINT8>	&echo, const SDICOS::ErrorLog&errorlog);

	/// Called when DICOS session starts
	void BeginSession(const SDICOS::Utils::SessionData &sessiondata);

	/// Called when DICOS session ends
	void EndSession(const SDICOS::Utils::SessionData &sessiondata);

	/// Called when a TCP/IP connection is established
	void Connected(const SDICOS::Utils::SessionData &sessiondata);

	/// Called when a TCP/IP connection is terminated
	void Disconnected(const SDICOS::Utils::SessionData &sessiondata);
protected:

	/// Override for callback when the server is ready to receive client connections
	virtual void OnServerReady();

	/// [Error] Override for callback function when errors occur and client session completes
	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata) = 0;

	/// [Tag-Level API or Unknown Data] Override for callback function when data is received.
	/// This function is also called if the preferred API cannot be used due to an unknown SOP class UID found in the DICOS data.
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog) = 0;

	/// [Module-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CTModule> &ct, const SDICOS::ErrorLog&errorlog);
	/// [Module-Level API] Override for callback function when data is received 
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DXModule> &dx, const SDICOS::ErrorLog&errorlog);
	/// [Module-Level API] Override for callback function when data is received 
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2DModule> &ait2d, const SDICOS::ErrorLog&errorlog);
	/// [Module-Level API] Override for callback function when data is received 
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3DModule> &ait3d, const SDICOS::ErrorLog&errorlog);
	/// [Module-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QRModule> &qr, const SDICOS::ErrorLog&errorlog);
	/// [Module-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDRModule> &tdr, const SDICOS::ErrorLog&errorlog);

	/// [User-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog&errorlog);
	/// [User-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog&errorlog);
	/// [User-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog&errorlog);
	/// [User-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog&errorlog);
	/// [User-Level API] Override for callback function when data is received
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog&errorlog);
	/// [User-Level API] Override for callback function when data is received 
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog&errorlog);

	/// Override for callback when a C-Echo is received
	/// @param sessiondata Holds all client-server related data
	/// @param errorlog Error log
	virtual void OnReceiveDicosEcho(const SDICOS::Utils::SessionData &sessiondata, const SDICOS::ErrorLog &errorlog);

	/// Called when DICOS session starts after authentication passes
	virtual void OnBeginSession(const SDICOS::Utils::SessionData &sessiondata);

	/// Called when DICOS session ends
	virtual void OnEndSession(const SDICOS::Utils::SessionData &sessiondata);

	/// Override for callback when a TCP/IP connection is established
	/// @param sessiondata Holds all client-server related data
	virtual void OnConnected(const SDICOS::Utils::SessionData &sessiondata);

	/// Override for callback when a TCP/IP connection is terminated
	/// @param sessiondata Holds all client-server related data
	virtual void OnDisconnected(const SDICOS::Utils::SessionData &sessiondata);
};

}// namespace Network
}// namespace SDICOS

#endif