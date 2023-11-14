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
#ifndef _STRATOVAN_DICOS_AIT_BODY_ZONES_H_
#define _STRATOVAN_DICOS_AIT_BODY_ZONES_H_

#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class AitBodyZones
/// Implements a specialized Code Sequence with Context ID = "DCS2"
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = "DCS2"
/// Code Scheme Designator = "TSA"
class AitBodyZones : public CodeSequence
{
public:

	/// Constructor
	AitBodyZones();
	/// Copy constructor
	AitBodyZones(const AitBodyZones &aitbodyzones);
	/// Destructor
	~AitBodyZones();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	AitBodyZones& operator=(const AitBodyZones &aitbodyzones);
	/// Comparison operator
	bool operator==(const AitBodyZones &aitbodyzones)const;
	/// Comparison operator
	bool operator!=(const AitBodyZones &aitbodyzones)const;

	/// Comparison operator
	bool operator==(const CodeSequence &cs)const;
	/// Comparison operator
	bool operator!=(const CodeSequence &cs)const;

private:

	///
	/// Code Scheme Designator : Tag (0008, 0102), VR = SH [required]
	/// Set to "TSA"
	///
	virtual bool SetSchemeDesignator(const DcsShortString& strSchemeDesignator);		

	///
	/// Context Identifier : Tag (0008, 010F), VR = CS [optional]
	/// Set to "DCS2"
	///
	virtual bool SetContextID(const DcsCodeString& strContextID);
};

}//namespace SDICOS

#endif
