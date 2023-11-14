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
#ifndef _STRATOVAN_DICOS_FRAME_CONTENT_MACRO_H_
#define _STRATOVAN_DICOS_FRAME_CONTENT_MACRO_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
///
/// \class FrameContentMacro
/// \brief Implements Frame Content Macro, a required single item sequence (0020, 9111)
/// SPECREF V03 Section 14.14.2, Table 112
///
class FrameContentMacro
{
public:
	/// Constructor
	FrameContentMacro();
	/// Copy constructor
	FrameContentMacro(const FrameContentMacro &framecontentmacro);
	/// Destructor
	virtual ~FrameContentMacro();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	FrameContentMacro& operator=(const FrameContentMacro &framecontentmacro);
	/// Comparison operator
	bool operator==(const FrameContentMacro &framecontentmacro)const;
	/// Comparison operator
	bool operator!=(const FrameContentMacro &framecontentmacro)const;

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

	/// Set Frame Acquisition Number : Tag (0020, 9156), VR = US [optional]
	bool SetFrameAcquisitionNumber(const S_UINT16 nAcquisitionNumber);
	/// @see SetFrameAcquisitionNumber
	S_UINT16 GetFrameAcquisitionNumber()const;
	/// Delete Frame Acquisition Number
	void DeleteFrameAcquisitionNumber();

	/// Set Frame Reference Date And Time : Tag (0018, 9151),  VR = DT [required if Frame Type's, (0008, 9007), value 1 is "ORIGINAL"]
	bool SetFrameReferenceDateAndTime(const DcsDateTime &strDateTime);
	/// @see SetFrameReferenceDateAndTime
	DcsDateTime GetFrameReferenceDateAndTime()const;
	/// Delete Frame Reference Date And Time 
	void DeleteFrameReferenceDateAndTime();

	/// Set Frame Acquisition Date And Time : Tag (0018, 9074), VR = DT [required if Frame Type's, (0008, 9007), value 1 is "ORIGINAL"]
	bool SetFrameAcquisitionDateAndTime(const DcsDateTime &strDateTime);
	/// @see SetFrameAcquisitionDateAndTime
	DcsDateTime GetFrameAcquisitionDateAndTime()const;
	/// Delete Frame Acquisition Date And Time
	void DeleteFrameAcquisitionDateAndTime();

	/// Set Frame Acquisition Duration in millisecond : Tag (0018, 9220), VR = FD [required if Frame Type's, (0008, 9007), value 1 is "ORIGINAL"]
	bool SetFrameAcquisitionDurationInMS(const double fDuration);
	/// @see SetFrameAcquisitionDurationInMS
	double GetFrameAcquisitionDuration()const;
	/// Delete Frame Acquisition Duration
	void DeleteFrameAcquisitionDuration();

	/// Set Dimension Index Value : Tag (0020, 9157), VR = UL [required if Dimension Index Sequence (0020, 9222) has items]
	/// Stores the values of the indices from Dimension Index Sequence (0020, 9222)
	bool SetDimensionIndexValue(const Array1D<S_UINT32> &arrayIndexValues);
	/// @see SetDimensionIndexValue
	bool GetDimensionIndexValue(Array1D<S_UINT32> &arrayIndexValues)const;
	/// @see SetDimensionIndexValue
	Array1D<S_UINT32>& GetDimensionIndexValue();
	/// @see SetDimensionIndexValue
	const Array1D<S_UINT32>& GetDimensionIndexValue()const;
	/// Delete Dimension Index Value
	void DeleteDimensionIndexValue();

	/// Set Temporal Position Index (First frame has index equal to 1) : Tag (0020, 9128), VR = UL [optional]
	bool SetTemporalPositionIndex(const S_UINT32 nIndex);
	/// @see SetTemporalPositionIndex
	S_UINT32 GetTemporalPositionIndex()const;
	/// Delete Temporal Position Index
	void DeleteTemporalPositionIndex();

	/// Set Stack ID : Tag (0020, 9056), VR = SH [optional]
	/// Identifies a group or stack of frames
	bool SetStackID(const DcsShortString &strID);
	/// @see SetStackID
	DcsString GetStackID()const;
	/// Delete Stack ID
	void DeleteStackID();

	/// Set In-Stack Position Number (First frame in stack has position equal to 1) : Tag (0020, 9057), VR = UL [required if Stack ID (0020, 9056) is set]
	bool SetInStackPositionNumber(const S_UINT32 nPositionNumber);
	/// @see SetInStackPositionNumber
	S_UINT32 GetInStackPositionNumber()const;
	/// DeleteIn-Stack Position Number
	void DeleteInStackPositionNumber();

	/// Set Frame Comments : Tag (0020, 9158), VR = LT [optional]
	bool SetFrameComments(const DcsLongString &strComments);
	/// @see SetFrameComments
	DcsString GetFrameComments()const;
	/// Delete Frame Comments
	void DeleteFrameComments();

	/// Set Frame Label : Tag (0020, 9453), VR = LO [optional]
	bool SetFrameLabel(const DcsLongString &strLabel);
	/// @see SetFrameLabel
	DcsString GetFrameLabel()const;
	/// Delete Frame Label
	void DeleteFrameLabel();

protected:
	class ImplFrameContentMacro;
	ImplFrameContentMacro	*m_pImplFrameContentMacro; ///< Internal implementation
};

}//namespace SDICOS

#endif
