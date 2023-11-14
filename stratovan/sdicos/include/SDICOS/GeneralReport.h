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
#ifndef _STRATOVAN_DICOS_TDR_GENERAL_REPORTS_H_
#define _STRATOVAN_DICOS_TDR_GENERAL_REPORTS_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class GeneralReport
/// \brief General Report Module
/// The GeneralReport class represents the General Report Module
/// SPECREF V03 Section 12.3, Table 68
///
class GeneralReport
{
public:
	/// Default Constructor
	GeneralReport();
	
	/// Copy Constructor
	GeneralReport(const GeneralReport &generalreport);
	
	// Destructor
	~GeneralReport();

	/// Assignment operator
	GeneralReport& operator=(const GeneralReport &generalreport);
	
	/// Comparison operator
	bool operator==(const GeneralReport &generalreport)const;
	
	/// Comparison operator
	bool operator!=(const GeneralReport &generalreport)const;

	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
	
	/// Reset to default values
	void FreeMemory();
	
	///
	/// Set Instance Number : Tag (0020, 0013)
	///	@param nInstanceNumber Tag (0020, 0013), VR = IS [required]
	/// @return true/false
	///
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);

	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;

	/// @see SetInstanceNumber
	DcsString GetInstanceNumberAsString()const;

	///
	/// Set Content Date and Time
	/// @param strDate Tag (0008, 0023), VR = DA [required]
	/// @param strTime Tag (0008, 0033), VR = TM [required]
	/// @return true/false
	///
	bool SetContentDateAndTime(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetContentDateAndTime
	DcsDate GetContentDate()const;

	/// @see SetContentDateAndTime
	DcsTime GetContentTime()const;

protected:
	class ImplGeneralReport;
	ImplGeneralReport	*m_pImplGeneralReport; ///< Internal implementation
	
	ImplGeneralReport* GetImpl();
	const ImplGeneralReport* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif