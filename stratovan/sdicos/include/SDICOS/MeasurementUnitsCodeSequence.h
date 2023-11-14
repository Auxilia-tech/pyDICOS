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
#ifndef _STRATOVAN_DICOS_MEASUREMENT_UNITS_CODE_SEQUENCE_H_
#define _STRATOVAN_DICOS_MEASUREMENT_UNITS_CODE_SEQUENCE_H_

#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class MeasurementUnitsCodeSequence
/// \brief Implements a specialized Code Sequence with Context ID = 82
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = 82
/// Code Scheme Designator = UCUM
class MeasurementUnitsCodeSequence : public CodeSequence
{
public:

	/// Constructor
	MeasurementUnitsCodeSequence();
	/// Copy constructor
	MeasurementUnitsCodeSequence(const MeasurementUnitsCodeSequence &cs);
	/// Destructor
	~MeasurementUnitsCodeSequence();

	virtual void FreeMemory();

	/// Copy operator
	MeasurementUnitsCodeSequence& operator=(const MeasurementUnitsCodeSequence &cs);
	/// Comparison operator
	bool operator==(const MeasurementUnitsCodeSequence &cs)const;
	/// Comparison operator
	bool operator!=(const MeasurementUnitsCodeSequence &cs)const;
	/// Comparison operator
	bool operator==(const CodeSequence &cs)const;
	/// Comparison operator
	bool operator!=(const CodeSequence &cs)const;
private:
	/// Code Scheme Designator set to "UCUM" : Tag (0008, 0102), VR = SH [required]
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);		

	/// Context Identifier set to 82 : Tag (0008, 010F), VR = CS [optional]
	virtual bool SetContextID(const DcsCodeString &strContextID);
};

}//namespace SDICOS

#endif