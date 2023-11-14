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
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_IHOST_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_IHOST_H_

namespace SDICOS
{
namespace Network
{
/// \class IDcsServer
/// \brief Interface class for DICOS server
class IDcsServer
{
public:

	/// Enumerations that define the result of a client connection
	typedef enum
	{
		enumResultUnknown,

		enumResultNone,			///< No result
		enumResultBusy,			///< Still processing

		enumResultSuccess,		///< Command completed successfully
		enumResultFailed,		///< Command completed failed
		enumResultCancelled,	///< Command completed canceled
		enumResultAborted,		///< Command completed with A-Abort

		enumResultRejectedDestinationApplicationName,	///< Invalid destination application name in A-Associate-RQ
		enumResultRejectedSourceApplicationName,		///< Invalid source application name in A-Associate-RQ
		enumResultRejectedUnsupportedUserType,			///< Unsupported user type in A-Associate-RQ
		enumResultRejectedUserTypeMismatch,				///< User type from A-Associate-RQ does not match the expected CLIENT_ACCESS_REQUIREMENT
		enumResultRejectedInvalidUserData,				///< User name or user name and passcode from A-Associate-RQ is invalid
		enumResultRejectedUnsupportedApplicationContextName,	///< Application Context Name from A-Associate-RQ is not supported (Must be latest DICOS version)

		enumResultAbortedExpectedData,	///< Expected data only PDV's after receiving a C-Store-RQ marked as not the last fragment
		enumResultAbortedUnknownPDU,	///< Received an unknown or unsupported PDU
		enumResultAbortedUnknownPDV,	///< Received an unknown or unsupported PDV
		enumResultAbortCastFailed,		///< Pointer casting failed

		enumResultFailedToReceiveCompleteData,	///< Connection ended before all data was received (Last PDV must be marked as 'last fragment')
	}RESULT;

	/// Enumeration for preferred API callback
	typedef enum
	{
		enumMethodTagAPI,		///< Always uses OnReceiveDicosFile(AttributeManager &manager)
		enumMethodModuleAPI,	///< Always uses modality specific OnReceiveDicosFile() for known modalities
		enumMethodUserAPI,		///< [Default] Always uses user-level API specific OnReceiveDicosFile() for known modalities
	}RETRIEVE_METHOD;
};

}// namespace Network
}// namespace SDICOS

#endif