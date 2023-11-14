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
#ifndef _STRATOVAN_DICOS_QR_SERIES_H_
#define _STRATOVAN_DICOS_QR_SERIES_H_

#include "SDICOS/GeneralSeriesModule.h"

namespace SDICOS
{
namespace QRTypes
{

///
/// \class QRSeries
/// Implements QR Series
/// SPECREF V03 Section 10.3.1, Table 60
///
class QRSeries : public GeneralSeriesModule
{
public:
	/// Constructor
	QRSeries();
	/// Copy constructor
	QRSeries(const QRSeries &qrseries);
	/// Destructor
	~QRSeries();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	QRSeries& operator=(const QRSeries &qrseries);
	/// Comparison operator
	bool operator==(const QRSeries &qrseries)const;
	/// Comparison operator
	bool operator!=(const QRSeries &qrseries)const;

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

protected:

	/// Internally set to QR
	virtual bool SetModality(const MODALITY);
};

}//namespace QRTypes
}//namespace SDICOS

#endif