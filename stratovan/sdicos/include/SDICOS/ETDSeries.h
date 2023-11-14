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

#include "SDICOS/GeneralSeriesModule.h"

#ifndef _STRATOVAN_DICOS_ETD_SERIES_MODULE_H_
#define _STRATOVAN_DICOS_ETD_SERIES_MODULE_H_

namespace SDICOS
{

///
/// \class ETDSeries
/// Implements ETD Series
/// SPECREF V03 Section 11.2, Table 63
///
class ETDSeries : public GeneralSeriesModule
{
public:
	/// Constructor
	ETDSeries();
	/// Copy constructor
	/// @param series Initialize to this object
	ETDSeries(const ETDSeries& series);
	/// Destructor
	~ETDSeries();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	/// @param series Object to copy
	/// @return Reference to this object
	ETDSeries& operator=(const ETDSeries& series);
	/// Comparison operator
	/// @param series Object to compare
	/// @return true/false
	bool operator==(const ETDSeries& series)const;
	/// Comparison operator
	/// @param series Object to compare
	/// @return true/false
	bool operator!=(const ETDSeries& series)const;

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager& attribManager, ErrorLog& errorlog)const;

protected:

	/// Internally set to ETD
	/// @param nMod
	/// @return true
	virtual bool SetModality(const MODALITY nMod);
};

}

#endif
