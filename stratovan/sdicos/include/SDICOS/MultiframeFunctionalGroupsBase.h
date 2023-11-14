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
#ifndef _STRATOVAN_DICOS_MULTIFRAME_FUNCTIONAL_GROUPS_BASE_H_
#define _STRATOVAN_DICOS_MULTIFRAME_FUNCTIONAL_GROUPS_BASE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class MultiframeFunctionalGroupsBase
/// Implements a base for Multiframe Functional Groups Module
/// SPECREF V03 Section 14.17, Table 123
///
///	-Does not include the following attributes, which are to be implemented by deriving classes:
///		1. Shared Functional Groups Sequence : Tag (5200, 9229), VR = SQ [required (Type 2), can be empty]
///		2. Per-Frame Functional Groups Sequence : Tag (5200, 9230), VR = SQ [required]
/// 
class MultiframeFunctionalGroupsBase
{
public:
	/// Constructor
	MultiframeFunctionalGroupsBase();
	/// Copy constructor
	MultiframeFunctionalGroupsBase(const MultiframeFunctionalGroupsBase &mfg);
	/// Destructor
	virtual ~MultiframeFunctionalGroupsBase();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	MultiframeFunctionalGroupsBase& operator=(const MultiframeFunctionalGroupsBase &mfg);
	/// Comparison operator
	bool operator==(const MultiframeFunctionalGroupsBase &mfg)const;
	/// Comparison operator
	bool operator!=(const MultiframeFunctionalGroupsBase &mfg)const;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Instance Number : Tag (0020, 0013), VR = IS [required]
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);
	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;
	/// @see SetInstanceNumber
	DcsString GetInstanceNumberAsString()const;

	/// Content Date and Time
	/// @param strDate Content Date : Tag (0008, 0023), VR = DA [required]
	/// @param strTime Content Time : Tag (0008, 0033), VR = TM [required]
	bool SetContentDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetContentDateAndTime
	DcsDate GetContentDate()const;
	/// @see SetContentDateAndTime
	DcsTime GetContentTime()const;

	/// Number of Frames : Tag (0028, 0008), VR = US [required]
	bool SetNumberOfFrames(const S_UINT32 nNumFrames);
	/// @see SetNumberOfFrames
	S_UINT32 GetNumberOfFrames()const;

	/// Concatenation UID : Tag (0020, 9161), VR = UI [required if a group of multiframe image SOP instances is part of a concatenation]
	bool SetConcatenationUID(const DcsUniqueIdentifier &strID);
	/// @see SetConcatenationUID
	DcsString GetConcatenationUID()const;
	/// Delete Concatenation UID
	void DeleteConcatenationUID();

	/// Concatenation Frame Offset Number (Zero offset indicates first frame) : Tag (0020, 9228), VR = UL [required if Concatenation UID (0020, 9161) is set]
	/// @return returns 0xFFFFFFFF if the offset is not set
	bool SetConcatenationFrameOffsetNumber(const S_UINT32 nFrameOffsetNumber);
	/// @see SetConcatenationFrameOffsetNumber
	S_UINT32 GetConcatenationFrameOffsetNumber()const;
	/// @see SetConcatenationFrameOffsetNumber
	void DeleteConcatenationFrameOffsetNumber();

	/// Representative Frame Number (First frame has a value of 1) : Tag (0028, 6010), VR = US [optional]
	bool SetRepresentativeFrameNumber(const S_UINT16 nRepresentativeFrameNumber);
	/// @see SetRepresentativeFrameNumber
	S_UINT16 GetRepresentativeFrameNumber()const;
	/// Delete Representative Frame Number
	void DeleteRepresentativeFrameNumber();
	
	/// SOP Instance UID of Concatenation Source : Tag (0020, 0242), VR = UI [required if Concatenation UID (0020, 9161) is set]
	bool SetSopInstanceUidOfConcatenationSource(const DcsUniqueIdentifier &strID);
	/// @see SetSopInstanceUidOfConcatenationSource
	DcsString GetSopInstanceUidOfConcatenationSource()const;
	/// Delete SOP Instance UID of Concatenation Source
	void DeleteSopInstanceUidOfConcatenationSource();

	/// In-concatenation Number : Tag (0020, 9162), VR = US [required if Concatenation UID (0020, 9161) is set]
	/// The first instance in a concatenation (i.e. the instance with the lowest Frame Offset Number (0020, 9228)) has a value of 1
	bool SetInconcatenationNumber(const S_UINT16 nInconcatenationNumber);
	/// @see SetInconcatenationNumber
	S_UINT16 GetInconcatenationNumber()const;
	/// Delete In-concatenation Number
	void DeleteInconcatenationNumber();

	/// In-concatenation Total Number : Tag (0020, 9163), VR = US [optional]
	/// Number of SOP instances with the same Concatenation UID (0020, 9161)
	bool SetInconcatenationTotalNumber(const S_UINT16 nInconcatenationTotalNumber);
	/// @see SetInconcatenationTotalNumber
	S_UINT16 GetInconcatenationTotalNumber()const;
	/// Delete In-concatenation Total Number
	void DeleteInconcatenationTotalNumber();

protected:
	class ImplMultiframeFunctionalGroupsBase;
	ImplMultiframeFunctionalGroupsBase	*m_pImplMultiframeFunctionalGroupsBase; ///< Internal implementation
};

}//namespace SDICOS

#endif
