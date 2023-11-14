//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_UTILS_H_
#define	_STRATOVAN_DICOS_UTILS_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/FileSystem.h"

#pragma push_macro("new")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SDICOS { 

class AttributeManager;

class AIT2DModule;
class AIT3DModule;
class CTModule;
class DXModule;
class QRModule;
class TDRModule;

class AIT2D;
class AIT3D;
class CT;
class DX;
class QR;
class TDR;

class Tag;
	
namespace Utils 
{
	/// \class TimeStamp
	/// \brief Structure for holding date and time.
	class TimeStamp
	{
	public:
		TimeStamp();

		/// Get the current date and time
		static void Now(TimeStamp &timeStamp);

		/// Set the current date and time
		void Now();

		S_UINT32 m_nYear;
		S_UINT32 m_nMonth;
		S_UINT32 m_nDay;

		S_UINT32 m_nHour; //0-23
		S_UINT32 m_nMinute;
		S_UINT32 m_nSecond;
		S_UINT32 m_nMilliSecond;
	};

	S_UINT64 MicroSecondsSinceProgramStart(); ///< Returns milliseconds since the program started
	S_UINT64 MilliSecondsSinceProgramStart(); ///< Returns microseconds since the program started
	
	/// \class DicosDataBase
	/// \brief Holds information about DICOS network transfer
	class DicosDataBase
	{
	public:
		DicosDataBase();
		virtual ~DicosDataBase();

		virtual void FreeMemory();

		/// Comparison operator
		bool operator==(const DicosDataBase &data)const;
		/// Comparison operator
		bool operator!=(const DicosDataBase &data)const;

		/// Set the IP of the device that sent the data 
		void SetClientIP(const DcsString &dsIP);
		/// @see SetClientIP
		const DcsString& GetClientIP()const;

		/// Set the IP of the device that received the data 
		void SetServerIP(const DcsString &dsIP);
		/// @see SetHostIP
		const DcsString& GetServerIP()const;

		/// Set the port that the host received the data
		void SetServerPort(const S_UINT32 nPort);
		/// @see SetServerPort
		S_UINT32 GetServerPort()const;

		/// Set the port that the host received the data
		void SetClientPort(const S_UINT32 nPort);
		/// @see SetClientPort
		S_UINT32 GetClientPort()const;

		/// ID for the client-host session
		void SetSessionID(const DcsString &dsID);
		/// @see SetSessionID
		DcsString GetSessionID()const;

		/// Client's application name
		void SetClientApplicationName(const DcsString &dsName);
		/// @see SetClientApplicationName
		DcsString GetClientApplicationName()const;

		/// Time stamp when data was fully received (right before invoking callback functions)
		TimeStamp& GetTimeStamp();
		/// @see GetTimeStamp
		const TimeStamp& GetTimeStamp()const;

		/// Time stamp for when receiving the data started (i.e. DcsServer started downloading)
		TimeStamp& GetTransferStartTimeStamp();
		/// @see GetTransferStartTimeStamp
		const TimeStamp& GetTransferStartTimeStamp()const;

		/// Time stamp for when data started processing(i.e.DcsServer finished downloading and started processing the downloaded data buffer)
		TimeStamp& GetProcessStartTimeStamp();
		/// @see GetProcessStartTimeStamp
		const TimeStamp& GetProcessStartTimeStamp()const;

		/// Time taken to download data
		void SetTransferTimeInMicroSeconds(const S_UINT64 nTimeMicroSec);
		/// @see SetTransferTimeInMicroSeconds
		S_UINT64 GetTransferTimeInMicroSeconds()const;

		/// Time taken after download to reach user callback function. Includes time taken to read DICOS data from message.
		/// Processing time can be reduced by:
		///	-Disabling data compression with DcsClient::DisableDataCompression or DcsHost::DisableDataCompression. This has a significant impact on speed.
		/// -Using lower level API. From Slowest to fastest: User-Level, Module-Level, Tag-Level. This may not notably reduce time.
		/// @see SDICOS::Network::DcsClient::DisableDataCompression
		/// @see SDICOS::Network::DcsHost::DisableDataCompression
		/// @see SDICOS::Network::DcsClientManager::DisableDataCompression
		void SetProcessTimeInMicroSeconds(const S_UINT64 nTimeMicroSec);
		/// @see SetProcessTimeInMicroSeconds
		S_UINT64 GetProcessTimeInMicroSeconds()const;

		/// Size of data. If pixel data is compressed, the size includes the compressed pixel data.
		void SetSizeOfData(const S_UINT64 nSize);
		/// @see SetSizeOfData
		S_UINT64 GetSizeOfData()const;
	protected:
		DcsString	m_dsClientIP;	///< IP of client that sent data
		DcsString	m_dsServerIP;	///< IP of server that received data
		S_UINT32	m_nServerPort;	///< Port that received the data
		S_UINT32	m_nClientPort;	///< Port that client used to send the data
		DcsString	m_dsSessionID;	///< Session ID unique for each client-host connection
		DcsString	m_dsClientAppName;	///< Name of client application sending the DICOS data
		TimeStamp	m_TimeStamp;	///< Time stamp for data
		S_UINT64	m_nTransferTimeMicroSec; ///< Time taken in microseconds for data to be transferred
		S_UINT64	m_nSizeOfData;	///< Size of data. If pixel data is compressed, the size includes the compressed pixel data.
		S_UINT64	m_nProcessTimeMicroSec; ///< Time taken in microseconds for data to reach user Callback function after downloading completed
		TimeStamp	m_tsTransferStart;	///< Time stamp for when receiving the data started (i.e. DcsServer started downloading)
		TimeStamp	m_tsProcessStart;	///< Time stamp for when data started processing (i.e. DcsServer finished downloading and started processing the downloaded data buffer)
	};

	/// \class DicosData
	/// \brief Structure for holding DICOS used in callback functions. Data can be moved out of this object.
	template< typename TYPE >
	class DicosData : public DicosDataBase
	{
	public:
		/// Constructor
		DicosData()		
			: DicosDataBase()
		{
			m_pdata = S_NULL;
			FreeMemory();
		}
		/// Destructor
		~DicosData()	{FreeMemory();}

		/// Comparison operator for TYPE
		bool operator==(const TYPE &type)const
		{
			if(S_NULL == m_pdata)
				return false;

			return *m_pdata == type;
		}

		/// Comparison operator for TYPE
		bool operator!=(const TYPE &type)const
		{
			return !operator==(type);
		}

		/// Comparison operator
		bool operator==(const DicosData &data)const
		{
			if(DicosDataBase::operator!=(data))
				return false;

			if(m_vpOriginal.GetSize() != data.m_vpOriginal.GetSize())
				return false;

			const std::pair<SDICOS::Filename, SDICOS::AttributeManager*> *prefThis = m_vpOriginal.GetBuffer();
			const std::pair<SDICOS::Filename, SDICOS::AttributeManager*> *pref = data.m_vpOriginal.GetBuffer();

			for(S_UINT32 n(0) ; n < m_vpOriginal.GetSize() ; ++n, ++pref, ++prefThis)
			{
				if(!IsEqual(pref, prefThis))
					return false;
			}

			if(S_NULL == m_pdata && S_NULL == data.m_pdata)
				return true;

			if(S_NULL == m_pdata || S_NULL == data.m_pdata)
				return false;

			return *m_pdata == *data.m_pdata;
		}
		
		/// Comparison operator
		bool operator!=(const DicosData &data)const
		{
			return !operator==(data);
		}

		/// Deletes original data
		void DeleteOriginalData()
		{
			std::pair<SDICOS::Filename, SDICOS::AttributeManager*> *pref = m_vpOriginal.GetBuffer();

			for(S_UINT32 n(0) ; n < m_vpOriginal.GetSize() ; ++n, ++pref)
			{
				if(S_NULL != pref->second)
					DELETE_POINTER(pref->second);
			}

			m_vpOriginal.FreeMemory();
		}

		/// Deletes internal data
		virtual void FreeMemory()
		{
			if(S_NULL != m_pdata)
				DELETE_POINTER(m_pdata);

			DeleteOriginalData();
			DicosDataBase::FreeMemory();
		}

		/// Removes data ownership from this object into the parameter. Caller gains ownership of data and is responsible for deleting it.
		/// @param pdata Gains ownership of data
		void TakeOwnership(TYPE* &pdata)
		{
			pdata = m_pdata;
			m_pdata = S_NULL;
		}	

		/// Allocates TYPE data
		///	@param pfnApiAllocator Custom allocation function if template TYPE is a base class
		/// @return Returns true if data was allocated, returns false otherwise.
		bool AllocateData(TYPE* (*pfnApiAllocator)() = S_NULL)
		{
			if(S_NULL != m_pdata)
				DELETE_POINTER(m_pdata);

			try
			{
				m_pdata = S_NULL != pfnApiAllocator ? pfnApiAllocator() : new TYPE;
			}
			catch(std::bad_alloc&)
			{
				DELETE_POINTER(m_pdata);
			}

			S_ASSERT(S_NULL != m_pdata);
			return S_NULL != m_pdata;
		}

		/// Pass ownership of original Tag-Level data
		void GiveOriginal(SDICOS::AttributeManager *&pmanagerOriginal)
		{
			DeleteOriginalData();

			m_vpOriginal.SetSize(1);
			m_vpOriginal[0].second = pmanagerOriginal;
			pmanagerOriginal = S_NULL;
		}

		/// Pass ownership of original Tag-Level data to this object
		void GiveOriginal(SDICOS::AttributeManager *&pmanagerOriginal, const SDICOS::Filename &filename)
		{
			DeleteOriginalData();

			m_vpOriginal.SetSize(1);
			m_vpOriginal[0].first = filename;
			m_vpOriginal[0].second = pmanagerOriginal;
			pmanagerOriginal = S_NULL;
		}

		/// Pass ownership of original Tag-Level data to this object
		void GiveOriginal(	SDICOS::Array1D<SDICOS::AttributeManager*> &vpmanagerOriginal)
		{
			DeleteOriginalData();

			m_vpOriginal.SetSize(vpmanagerOriginal.GetSize());

			for(S_UINT32 n(0) ; n < m_vpOriginal.GetSize() ; ++n)
			{
				m_vpOriginal[n].second = vpmanagerOriginal[n];
				vpmanagerOriginal[n] = S_NULL;
			}
		}

		/// Pass ownership of original Tag-Level data to this object
		void GiveOriginal(	SDICOS::Array1D<SDICOS::AttributeManager*> &vpmanagerOriginal, 
							const SDICOS::Array1D<SDICOS::Filename> &vfilename)
		{
			if(vpmanagerOriginal.GetSize() != vfilename.GetSize())
			{
				S_ASSERT(0);
				return;
			}

			DeleteOriginalData();

			m_vpOriginal.SetSize(vpmanagerOriginal.GetSize());

			for(S_UINT32 n(0) ; n < m_vpOriginal.GetSize() ; ++n)
			{
				m_vpOriginal[n].first = vfilename[n];
				m_vpOriginal[n].second = vpmanagerOriginal[n];
				vpmanagerOriginal[n] = S_NULL;
			}
		}

		/// Take ownership of the original Tag-Level data from this object
		void TakeOwnershipOriginal(AttributeManager *&pmanagerOriginal)
		{
			if(0 == m_vpOriginal.GetSize())
			{
				pmanagerOriginal = S_NULL;
				return;
			}

			pmanagerOriginal = m_vpOriginal[0].second;
			m_vpOriginal[0].first.Set();
			m_vpOriginal[0].second = S_NULL;
		}

		/// Take ownership of the original Tag-Level data from this object
		void TakeOwnershipOriginal(Array1D< std::pair<SDICOS::Filename, SDICOS::AttributeManager*> > &vpOriginal)
		{
			vpOriginal = m_vpOriginal;

			std::pair<SDICOS::Filename, SDICOS::AttributeManager*> *pref = m_vpOriginal.GetBuffer();

			for(S_UINT32 n(0) ; n < m_vpOriginal.GetSize() ; ++n, ++pref)
				pref->second = S_NULL;

			m_vpOriginal.FreeMemory();
		}

		/// Get pointer to original data
		const SDICOS::AttributeManager* GetOriginalData()const
		{
			if(0 == m_vpOriginal.GetSize())
				return S_NULL;

			return m_vpOriginal[0].second;
		}

		/// Get number of attribute manager holding original data
		S_UINT32 GetNumOriginalData()const
		{
			return m_vpOriginal.GetSize();
		}

		/// Get pointer to original data
		const SDICOS::AttributeManager* GetOriginalData(const S_UINT32 n)const
		{
			if(n >= m_vpOriginal.GetSize())
				return S_NULL;

			return m_vpOriginal[n].second;
		}

		/// Get original data's file name
		SDICOS::Filename GetOriginalDataFilename(const S_UINT32 n)const
		{
			if(n >= m_vpOriginal.GetSize())
				return SDICOS::Filename();

			return m_vpOriginal[n].first;
		}

		/// Returns true if data is not null
		operator bool()const			{return S_NULL != m_pdata;}

		/// Returns pointer to TYPE data
		TYPE* operator->()				{return m_pdata;}
		/// Returns pointer to TYPE data
		const TYPE* operator->()const	{return m_pdata;}

		/// Returns reference to TYPE data
		TYPE& operator*()				{return *m_pdata;}
		/// Returns reference to TYPE data
		const TYPE& operator*()const	{return *m_pdata;}
	private:	
		/// Disable copy constructor
		DicosData(DicosData &)					{S_ASSERT(0);}
		/// Disable copy operator
		DicosData& operator=(const DicosData &)	{S_ASSERT(0); return *this;}

		TYPE*		m_pdata;		///< DICOS data for callback functions

		/// Original data in Tag-Level API if not using Tag-Level API. If data comes from disk, then the file names
		/// are stored with the original data. If data comes from network transmission, then the file name is left empty.
		/// The original data excludes the pixel data to prevent duplication of potentially very large data.
		Array1D< std::pair<SDICOS::Filename, SDICOS::AttributeManager*> >	m_vpOriginal;
	};

	class SessionData
	{
	public:
		SessionData()
		{
			m_nClientPort = m_nServerPort = 0;
		}

		SessionData(const DcsString &dsClientAppName, const DcsString &dsClientIP, const S_UINT32 nClientPort,
					const DcsString &dsServerIP, const S_UINT32 nServerPort,
					const DcsString &dsSessionID)
		{
			m_dsClientAppName = dsClientAppName;
			m_dsSessionID = dsSessionID;

			m_dsClientIP = dsClientIP;
			m_nClientPort = nClientPort;

			m_dsServerIP = dsServerIP;
			m_nServerPort = nServerPort;
		}

		friend std::ostream& operator<<(std::ostream& os, const SessionData& sessionData);

		std::string ToString() const; ///< Convert to std::string

		DcsString	m_dsClientAppName;	///< Client application name

		DcsString	m_dsClientIP;	///< IP of client that sent data
		S_UINT32	m_nClientPort;	///< Port that client sent the data

		DcsString	m_dsServerIP;	///< IP of server that received data
		S_UINT32	m_nServerPort;	///< Port that received the data

		DcsString	m_dsSessionID;	///< Session ID unique for each client-host connection
	};

	class AuthenticationData : public SessionData
	{
	public:
		AuthenticationData() : SessionData() {}
		AuthenticationData(	const DcsString &dsUserName, const DcsString &dsPasscode,
							const DcsString &dsClientAppName, const DcsString &dsClientIP, const S_UINT32 nClientPort,
							const DcsString &dsServerIP, const S_UINT32 nServerPort,
							const DcsString &dsSessionID)
				: SessionData(dsClientAppName, dsClientIP, nClientPort, dsServerIP, nServerPort, dsSessionID)
		{
			m_dsUserName = dsUserName;
			m_dsPasscode = dsPasscode;
		}

		DcsString	m_dsUserName;	///< User name
		DcsString	m_dsPasscode;	///< Passcode
	};

	/// \class APIAllocators
	/// \brief Contains functions to allocate derived versions of user-level and module-level API classes
	class APIAllocators
	{
	public:

		/// Sets default values
		APIAllocators();

		/// Copy constructor
		APIAllocators(const APIAllocators &aa);

		/// Clears any allocated data
		virtual ~APIAllocators();

		APIAllocators& operator=(const APIAllocators &aa);

		/// Reset to default
		virtual void FreeMemory();

		/// Only updates allocator functions with non-null allocator functions from the passed in parameter
		/// @param apiAllocators Allocator functions to update
		virtual void UpdateAllocators(const APIAllocators &apiAllocators);

		/// Calls custom allocator if it's not null. Otherwise returns: new AIT2D
		AIT2D*	AllocateAIT2D()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new AIT3D
		AIT3D*	AllocateAIT3D()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new CT
		CT*		AllocateCT()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new DX
		DX*		AllocateDX()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new QR
		QR*		AllocateQR()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new TDR
		TDR*	AllocateTDR()const;

		/// Calls custom allocator if it's not null. Otherwise returns: new AIT2DModule
		AIT2DModule*	AllocateModuleAIT2D()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new AIT3DModule
		AIT3DModule*	AllocateModuleAIT3D()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new CTModule
		CTModule*		AllocateModuleCT()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new DXModule
		DXModule*		AllocateModuleDX()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new QRModule
		QRModule*		AllocateModuleQR()const;
		/// Calls custom allocator if it's not null. Otherwise returns: new TDRModule
		TDRModule*		AllocateModuleTDR()const;

		/// Calls custom allocator if it's not null. Otherwise returns: new AttributeManager
		AttributeManager*	AllocateAttributeManager()const;

		//////////////////////////
		//  User-Level API

		AIT2D*	(*m_pfnAllocateUserAIT2D)();	//< Custom AIT2D allocator. Defaults to null
		AIT3D*	(*m_pfnAllocateUserAIT3D)();	//< Custom AIT3D allocator. Defaults to null
		CT*		(*m_pfnAllocateUserCT)();		//< Custom CT allocator. Defaults to null
		DX*		(*m_pfnAllocateUserDX)();		//< Custom DX allocator. Defaults to null
		QR*		(*m_pfnAllocateUserQR)();		//< Custom QR allocator. Defaults to null
		TDR*	(*m_pfnAllocateUserTDR)();		//< Custom TDR allocator. Defaults to null

		////////////////////////////
		//  Module-Level API

		AIT2DModule*	(*m_pfnAllocateModuleAIT2D)();	//< Custom AIT2DModule allocator. Defaults to null
		AIT3DModule*	(*m_pfnAllocateModuleAIT3D)();	//< Custom AIT3DModule allocator. Defaults to null
		CTModule*		(*m_pfnAllocateModuleCT)();		//< Custom CTModule allocator. Defaults to null
		DXModule*		(*m_pfnAllocateModuleDX)();		//< Custom DXModule allocator. Defaults to null
		QRModule*		(*m_pfnAllocateModuleQR)();		//< Custom QRModule allocator. Defaults to null
		TDRModule*		(*m_pfnAllocateModuleTDR)();	//< Custom TDRModule allocator. Defaults to null

		/////////////////////////
		//  Tag-Level API
		AttributeManager*	(*m_pfnAllocateAttributeManager)();	//< Custom AttributeManager allocator. Defaults to null
	};

	extern const char* EnumTypeUnknownCharString; ///< return the string "unknown"
	extern const char* EmptyCharString;
	extern const wchar_t* EmptyWCharString;
	extern const char* EnumTypeUnknownCharCodeString;

	extern const Array1D<DcsString> EmptyCharStringArray1D;
	
	///
	/// Utility method to compare arrays with objects of different types.
	/// The appropriate operator== must be defined.
	///
	template<class ATTRIBUTE_0, class ATTRIBUTE_1>
	bool Compare(const Array1D<ATTRIBUTE_0>& a0, const Array1D<ATTRIBUTE_1>& a1)
	{
		if(a0.GetSize() != a1.GetSize()) {
			return false;
		}

		for(S_UINT32 i = 0; i < a0.GetSize(); ++i) {
			if(!(a0[i] == a1[i])) {
				return false;
			}
		}
		return true;
	}	

	/// Returns true if a tag is in the (0x0000, xxxx) or (0x0002, xxxx) group
	bool IsHeaderTag(const Tag &tag);
}
}

#pragma pop_macro("new")

#endif	/* _STRATOVAN_DICOS_UTILS_H_ */

