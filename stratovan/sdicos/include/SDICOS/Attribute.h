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
#ifndef _STRATOVAN_DICOS_ATTRIBUTE_H_
#define _STRATOVAN_DICOS_ATTRIBUTE_H_

#include <iostream>

#include "SDICOS/IFile.h"
#include "SDICOS/String.h"
#include "SDICOS/Types.h"
#include "SDICOS/Array2D.h"
#include "SDICOS/Array3DLarge.h"
#include "SDICOS/Tag.h"
#include "SDICOS/ErrorLog.h"
#include "SDICOS/IMemoryManager.h"

namespace SDICOS
{

class AttributeManager;
class Volume;

///
/// \class AttributeCommon
/// The AttributeCommon class implements data common to all DICOS attributes.
/// Tag, representation, multiplicity, and ID.
///
class AttributeCommon
{
public:
	///
	/// Default constructor.
	/// Tag is (0xFFFF, 0xFFFF)
	/// Multiplicity is 0, ID is 0
	///
	AttributeCommon();
	virtual ~AttributeCommon();

	///
	/// Construct an attribute with a tag, Value Representation and multiplicity.
	/// Attribute ID is set to 0.
	///
	AttributeCommon(const Tag &tag);

	///
	/// Copy Constructor
	///
	AttributeCommon(const AttributeCommon &attribute);

	///
	/// Assignment operator
	///
	AttributeCommon& operator=(const AttributeCommon& attribute);

	/// Stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const AttributeCommon&);
	
	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	///
	/// Comparison operator
	///
	bool operator==(const AttributeCommon& attribute)const;

	///
	/// Comparison operator
	///
	bool operator!=(const AttributeCommon& attribute)const;

	///
	/// Set DICOS Tag
	///
	virtual bool SetTag(const Tag& tag);

	/// Set the DICOS Tag to the given Group and Element.
	/// Note: This method does not check if the (Group, Element)
	/// pair is valid for the attribute type.
	virtual bool SetTag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Get DICOS Tag
	///
	const Tag& GetTag()const;

	/// Set the Group and Element to 0xFFFF to invalidate the Attribute.
	virtual void ClearTag();

	///
	/// Get Value Representation
	/// Implement by derived attribute class that must know their own VR.
	///
	virtual DcsString GetVR()const = 0;

	///
	/// Get Value Multiplicity
	/// Derived attributes must know and report their multiplicity
	///
	virtual S_UINT32 GetVM()const = 0;

	///
	/// Get the Attribute's Data Size in bytes
	/// Derived attributes must know and report the size of their data.
	///
	virtual S_UINT64 GetSizeInBytes()const = 0;

	/// Check that the Tag group and element are not 0xFFFF.
	bool TagIsValid() const;

	///
	/// Write the Attribute Common data to the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param bExplicit Value Representation (VR) is explicitly encoded.
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit) const;

	///
	/// Read the Attribute Common data from the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param strVR Value Representation if it is explicitly given
	/// @param attributemanager Attribute manager
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, DcsString &strVR, const AttributeManager &attributemanager);

	///
	/// Read VR and set to the provided tag 
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param tag Tag to set to this attribute
	/// @param strVR Output VR
	/// @param bExplicit Explicit encoding flag
	/// @param attributemanager Attribute Manager
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const Tag &tag, DcsString &strVR, const bool bExplicit, const AttributeManager &attributemanager);

	/// Check the Attribute's value is valid for its VR.
	/// @return true/false false if the Tag is invalid
	virtual bool IsValid() const;

protected:
	inline void Verify() const; ///< Check that the implementation pointer is valid

	class ImplAttributeCommon;
	ImplAttributeCommon	*m_pImplAttributeCommon; ///< Internal implementation

	bool Read_internal(IFile &file, ErrorLog &errorlog, DcsString &strVR, const bool bExplicit, const AttributeManager &attributemanager);

};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///
/// \class AttributeHeader
/// \brief Class meant to only read the group, element, and VR from file. Used to determine which attribute class to select based on the VR
///
class AttributeHeader : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributeHeader();

	///
	/// Copy constructor
	///
	AttributeHeader(const AttributeHeader &attrib);

	///
	/// Destructor
	///
	virtual ~AttributeHeader();

	///
	/// Copy operator
	///
	AttributeHeader& operator=(const AttributeHeader &attrib);

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	///
	/// Read the group, element, and VR
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param bExplicit Explicit encoding flag
	/// @param strVR Output attribute VR
	/// @param attributemanager Attribute Manager
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, DcsString &strVR, const AttributeManager &attributemanager);

	///
	/// Read the group, element, and VR
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param bExplicit Explicit encoding flag
	/// @param attributemanager Attribute Manager
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read VR and set to the provided tag 
	///
	/// @param file File to read from
	/// @param errorlog Error log
	/// @param tag Tag to set to this attribute
	/// @param bExplicit Explicit encoding flag
	/// @param attributemanager Attribute Manager
	///
	bool Read(IFile &file, ErrorLog &errorlog, const Tag &tag, const bool bExplicit, const AttributeManager &attributemanager);
	
	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// This class does not have a VM. Returns 0.
	///
	virtual S_UINT32 GetVM()const;

protected:
	class ImplAttributeHeader;
	ImplAttributeHeader *m_pImplAttributeHeader; ///< Internal implementation

	///
	/// Disabled
	///
	virtual S_UINT64 GetSizeInBytes()const;

	///
	/// Disabled
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit) const;
};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///
/// \class AttributeString
/// \brief Represents attributes with a string VR
///
class AttributeString : public AttributeCommon
{
public:
	typedef enum
	{
		enumApplicationEntity,
		enumAge,
		enumCodeString,
		enumDate,
		enumDecimal,
		enumDateTime,
		enumInteger,
		enumLongString,
		enumLongText,
		enumPersonName,
		enumShortString,
		enumShortText,
		enumTime,
		enumUniqueIdentifier,
		enumUnlimitedText,
	}STRING_VR;

	///
	/// Initialize with default values
	///
	AttributeString();

	///
	/// Initialize with string value and type
	/// Construction fails if string or type is not valid
	///
	AttributeString(const DcsString &strValue, const STRING_VR nType);

	///
	/// Initialize with an AttributeString object
	///
	AttributeString(const AttributeString &attribute);

	///
	/// Destructor
	///
	virtual ~AttributeString();

	///
	/// Copy an AttributeString object
	///
	AttributeString& operator=(const AttributeString &attribute);

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Comparison operator
	///
	bool operator==(const AttributeString &attribute)const;

	///
	/// Comparison operator
	///
	bool operator!=(const AttributeString &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array of strings
	///
	DcsString& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array of strings
	///
	const DcsString& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize, const STRING_VR nType);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	///
	/// Get the string value or first string in array of strings
	///
	bool GetValue(DcsString &str)const;

	/// Get all the strings 
	bool GetValues(Array1D<DcsString> &arrayValues)const;

	///
	/// Get reference to values
	///
	const Array1D<DcsString>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<DcsString> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	/// @param nType String Value Representation
	bool MoveValuesInto(Array1D<DcsString> &arrayValues, const STRING_VR nType);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsString &strValue, const STRING_VR nType);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsString> &arrayValues, const STRING_VR nType);
	
	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsApplicationEntity &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsApplicationEntity> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsAge &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsAge> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsDate &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsDate> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsTime &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsTime> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsPersonName &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsPersonName> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsDecimal &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsDecimal> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsInteger &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsInteger> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsUnlimitedText &strValue);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsShortText &strValue);
	///
	/// Set an array of strings (VM > 1)
	/// @param arrayValues Array of Short Text strings
	/// @return true/false
	bool SetValues(const Array1D<DcsShortText>& arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsLongText &strValue);
	///
	/// Set an array of strings (VM > 1)
	/// @param arrayValues Array of Long Text strings
	/// @return true/false
	bool SetValues(const Array1D<DcsLongText>& arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsShortString &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsShortString> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsLongString &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsLongString> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsCodeString &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsCodeString> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsDateTime &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsDateTime> &arrayValues);

	///
	/// Set a single string (VM = 1)
	///
	bool SetValue(const DcsUniqueIdentifier &strValue);
	///
	/// Set an array of strings (VM > 1)
	///
	bool SetValues(const Array1D<DcsUniqueIdentifier> &arrayValues);

	//////////////////////////////////////////////
	///
	/// Write to file
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
	
	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	///
	/// Read from file
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);
	//////////////////////////////////////////////

	///
	/// Check if the string(s) are valid
	///
	bool IsValid()const;

	///
	/// Get size of all strings, delimiters, and padding in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;

	///
	/// Get the Value Multiplicity
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the VR
	///
	virtual DcsString GetVR()const;

	///
	/// Check if VR is a string attribute
	///
	static bool IsStringVR(const DcsString &strVR);

	///
	/// Check if VR allows for the '\' character within the string
	///
	static bool CanContainDelimiter(const DcsString &strVR);
protected:
	class	ImplAttributeString;
	ImplAttributeString	*m_pImplAttributeString;

	///
	/// Reads the data after AttributeCommon::Read
	///
	bool Read_internal(IFile &file, ErrorLog &errorlog, const bool bExplicit);
	///
	/// Set a single string (VM = 1)
	///
	bool SetValue_internal(const DcsString &str); 
};

///
/// \class AttributeSignedInt16Bit
/// Attribute that represents one or more 16-bit integers.
/// Value Representation (VR) = SS
///
class AttributeSignedInt16Bit : public AttributeCommon
{
public:
	/// Default constructor.
	/// VR is set to SS, VM is set to 0
	AttributeSignedInt16Bit();

	virtual ~AttributeSignedInt16Bit();

	/// Construct from an array of integers VR is set to SS, and VM is set to the number of values
	/// @param	arrayValues	An array of 16-bit integers. size sets AttributeBase::SetVM
	AttributeSignedInt16Bit(const Array1D<S_INT16> &arrayValues);

	/// Copy Constructor
	AttributeSignedInt16Bit(const AttributeSignedInt16Bit &attribute);

	/// Assignment operator
	AttributeSignedInt16Bit& operator=(const AttributeSignedInt16Bit &attribute);

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeSignedInt16Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeSignedInt16Bit &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_INT16& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_INT16& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Initialize attribute with a single value.
	bool SetValue(const S_INT16 &nValue);

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_INT16& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_INT16& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_INT16>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_INT16> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_INT16> &arrayValues);

	/// Initialize attribute with an array of 16-bit ints.
	/// @param	arrayValues	An array of 16-bit integers. Attribute multiplicity is the array size.
	bool SetValues(const Array1D<S_INT16> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_INT16> &arrayValues)const;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute's data in bytes (sizeof(S_INT16 * GetVM())
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM()const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeSignedInt16Bit;
	ImplAttributeSignedInt16Bit	*m_pImplAttributeSignedInt16Bit;

	const ImplAttributeSignedInt16Bit* GetImpl() const;
	ImplAttributeSignedInt16Bit* GetImpl();
};

///
/// \class AttributeUnsignedInt16Bit
/// Attribute that represents one or more 16-bit integers.
/// Value Representation (VR) = US
///
class AttributeUnsignedInt16Bit : public AttributeCommon
{
public:
	/// Default Constructor
	/// Value Representation = US, Value Multiplicity = 0
	AttributeUnsignedInt16Bit();

	virtual ~AttributeUnsignedInt16Bit();

	/// Construct from an array of integers VR is set to US, and VM is set to the number of values
	/// @param	arrayValues	An array of 16-bit integers. size sets AttributeBase::SetVM
	AttributeUnsignedInt16Bit(const Array1D<S_UINT16> &arrayValues);

	/// Copy Constructor
	AttributeUnsignedInt16Bit(const AttributeUnsignedInt16Bit &attribute);

	/// Assignment operator
	AttributeUnsignedInt16Bit& operator=(const AttributeUnsignedInt16Bit &attribute);

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_UINT16& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_UINT16& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeUnsignedInt16Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeUnsignedInt16Bit &attribute)const;

	/// Initialize attribute to a single value
	bool SetValue(const S_UINT16 &nValue);

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_UINT16& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_UINT16& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_UINT16>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_UINT16> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_UINT16> &arrayValues);

	/// Initialize attribute with an array of 16-bit unsigned integers.
	/// @param	arrayValues	An array of 16-bit integers. Attribute multiplicity is the array size.
	bool SetValues(const Array1D<S_UINT16> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_UINT16> &arrayValues)const;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in bytes
	S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeUnsignedInt16Bit;
	ImplAttributeUnsignedInt16Bit	*m_pImplAttributeUnsignedInt16Bit;

	const ImplAttributeUnsignedInt16Bit* GetImpl() const;
	ImplAttributeUnsignedInt16Bit* GetImpl();
};
///////////////////////////////////////////////////

///
/// \class AttributeSignedInt32Bit
/// Attribute that represents one or more 32-bit integers.
/// Value Representation (VR) = SL
///
class AttributeSignedInt32Bit : public AttributeCommon
{
public:
	/// Default constructor.
	AttributeSignedInt32Bit();

	/// Destructor
	virtual ~AttributeSignedInt32Bit();

	/// Construct attribute with an array of signed 32 bit integers
	AttributeSignedInt32Bit(const Array1D<S_INT32> &arrayValues);

	/// Copy constructor
	AttributeSignedInt32Bit(const AttributeSignedInt32Bit &attribute);

	/// Assignment operator
	AttributeSignedInt32Bit& operator=(const AttributeSignedInt32Bit &attribute);

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeSignedInt32Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeSignedInt32Bit &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_INT32& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_INT32& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Initialize attribute to a single value
	bool SetValue(const S_INT32 &nValue);

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_INT32& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_INT32& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_INT32>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_INT32> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_INT32> &arrayValues);

	/// Initialize attribute with an array of values
	/// @param arrayValues	Array of 32 bit integers. VM is the size of the array
	bool SetValues(const Array1D<S_INT32> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_INT32> &arrayValues)const;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeSignedInt32Bit;
	ImplAttributeSignedInt32Bit	*m_pImplAttributeSignedInt32Bit;

	const ImplAttributeSignedInt32Bit* GetImpl() const;
	ImplAttributeSignedInt32Bit* GetImpl();
};

///
/// \class AttributeUnsignedInt32Bit
/// Attribute that represents one or more 32-bit unsigned integers.
/// Value Representation (VR) = UL
///
class AttributeUnsignedInt32Bit : public AttributeCommon
{
public:
	/// Default Constructor
	AttributeUnsignedInt32Bit();

	/// Destructor
	virtual ~AttributeUnsignedInt32Bit();

	/// Construct attribute from an array of unsigned integers
	AttributeUnsignedInt32Bit(const Array1D<S_UINT32> &arrayValues);

	/// Copy Constructor
	AttributeUnsignedInt32Bit(const AttributeUnsignedInt32Bit &attribute);

	/// Assignment operator
	AttributeUnsignedInt32Bit& operator=(const AttributeUnsignedInt32Bit &attribute);

	/// Reset to default values
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeUnsignedInt32Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeUnsignedInt32Bit &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_UINT32& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_UINT32& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_UINT32& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_UINT32& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_UINT32>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_UINT32> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_UINT32> &arrayValues);

	/// Initialize attribute to a single value
	bool SetValue(const S_UINT32 &nValue);

	/// Initialize with an array of values
	bool SetValues(const Array1D<S_UINT32> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_UINT32> &arrayValues)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeUnsignedInt32Bit;
	ImplAttributeUnsignedInt32Bit	*m_pImplAttributeUnsignedInt32Bit;

	const ImplAttributeUnsignedInt32Bit* GetImpl() const;
	ImplAttributeUnsignedInt32Bit* GetImpl();
};

///////////////////////////////////////////////////////////////////////////////////////
///
/// \class AttributeSignedInt64Bit
/// Attribute that represents one or more 64-bit integers.
/// Value Representation (VR) = SD
///
class AttributeSignedInt64Bit : public AttributeCommon
{
public:
	/// Default constructor.
	AttributeSignedInt64Bit();

	/// Destructor
	virtual ~AttributeSignedInt64Bit();

	/// Construct attribute with an array of signed 64 bit integers
	AttributeSignedInt64Bit(const Array1D<S_INT64> &arrayValues);

	/// Copy constructor
	AttributeSignedInt64Bit(const AttributeSignedInt64Bit &attribute);

	/// Assignment operator
	AttributeSignedInt64Bit& operator=(const AttributeSignedInt64Bit &attribute);

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeSignedInt64Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeSignedInt64Bit &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_INT64& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_INT64& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Initialize attribute to a single value
	bool SetValue(const S_INT64 &nValue);

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_INT64& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_INT64& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_INT64>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_INT64> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_INT64> &arrayValues);

	/// Initialize attribute with an array of values
	/// @param arrayValues	Array of 32 bit integers. VM is the size of the array
	bool SetValues(const Array1D<S_INT64> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_INT64> &arrayValues)const;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeSignedInt64Bit;
	ImplAttributeSignedInt64Bit	*m_pImplAttributeSignedInt64Bit;

	const ImplAttributeSignedInt64Bit* GetImpl() const;
	ImplAttributeSignedInt64Bit* GetImpl();
};

///
/// \class AttributeUnsignedInt64Bit
/// Attribute that represents one or more 64-bit unsigned integers.
/// Value Representation (VR) = UD
///
class AttributeUnsignedInt64Bit : public AttributeCommon
{
public:
	/// Default Constructor
	AttributeUnsignedInt64Bit();

	/// Destructor
	virtual ~AttributeUnsignedInt64Bit();

	/// Construct attribute from an array of unsigned integers
	AttributeUnsignedInt64Bit(const Array1D<S_UINT64> &arrayValues);

	/// Copy Constructor
	AttributeUnsignedInt64Bit(const AttributeUnsignedInt64Bit &attribute);

	/// Assignment operator
	AttributeUnsignedInt64Bit& operator=(const AttributeUnsignedInt64Bit &attribute);

	/// Reset to default values
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeUnsignedInt64Bit &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeUnsignedInt64Bit &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	S_UINT64& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const S_UINT64& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(S_UINT64& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, S_UINT64& value) const;

	///
	/// Get reference to values
	///
	const Array1D<S_UINT64>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<S_UINT64> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<S_UINT64> &arrayValues);

	/// Initialize attribute to a single value
	bool SetValue(const S_UINT64 &nValue);

	/// Initialize with an array of values
	bool SetValues(const Array1D<S_UINT64> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<S_UINT64> &arrayValues)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write to avoid hiding overloaded functions

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeUnsignedInt64Bit;
	ImplAttributeUnsignedInt64Bit	*m_pImplAttributeUnsignedInt64Bit;

	const ImplAttributeUnsignedInt64Bit* GetImpl() const;
	ImplAttributeUnsignedInt64Bit* GetImpl();
};
///////////////////////////////////////////////////////////////////////////////////////

///
/// \class AttributeFloat
/// Attribute that represents one or more 32-bit floats.
/// Value Representation (VR) = FL
///
class AttributeFloat : public AttributeCommon
{
public:
	/// Default constructor. VM = 1
	AttributeFloat();

	/// Destructor
	virtual ~AttributeFloat();

	/// Construct from an array of floats
	AttributeFloat(const Array1D<float> &arrayValues);

	/// Copy Constructor
	AttributeFloat(const AttributeFloat &attribute);

	/// Assignment Operator
	AttributeFloat& operator=(const AttributeFloat &attribute);

	/// Reset to default values
	virtual void FreeMemory();

	/// Comparison Operator
	bool operator==(const AttributeFloat &attribute)const;
	bool operator!=(const AttributeFloat &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	float& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const float& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(float& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, float& value) const;

	///
	/// Get reference to values
	///
	const Array1D<float>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<float> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<float> &arrayValues);

	/// Initialize to a single value
	bool SetValue(const float &fValue);

	/// Initialize with an array of values
	bool SetValues(const Array1D<float> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<float> &arrayValues)const;

	using AttributeCommon::Write;
	using AttributeCommon::Read;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeFloat;
	ImplAttributeFloat	*m_pImplAttributeFloat;

	const ImplAttributeFloat* GetImpl() const;
	ImplAttributeFloat* GetImpl();
};

///
/// \class AttributeFloat
/// Attribute that represents one or more 64-bit doubles
/// Value Representation (VR) = FD
///
class AttributeDouble : public AttributeCommon
{
public:
	/// Default Constructor
	AttributeDouble();

	/// Destructor
	virtual ~AttributeDouble();

	/// Construct from an array of doubles
	AttributeDouble(const Array1D<double> &arrayValues);

	/// Copy Constructor
	AttributeDouble(const AttributeDouble &attribute);

	/// Assignment operator
	AttributeDouble& operator=(const AttributeDouble &attribute);

	/// Reset to default values
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const AttributeDouble &attribute)const;

	/// Comparison operator
	bool operator!=(const AttributeDouble &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array
	///
	double& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array
	///
	const double& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	/// Get the value or first element in values array
	/// @return false if no value is set
	bool GetValue(double& value) const;

	/// Get the value at the given index in the values array
	/// @return false if index is out of bounds
	bool GetValue(const S_UINT32 index, double& value) const;

	///
	/// Get reference to values
	///
	const Array1D<double>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<double> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<double> &arrayValues);

	/// Initialize with a single value
	bool SetValue(const double &fValue);

	/// Initialize with an array of values
	bool SetValues(const Array1D<double> &arrayValues);

	/// @see SetValues
	bool GetValues(Array1D<double> &arrayValues)const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write methods to avoid hiding overrides
	using AttributeCommon::Write;

	/// Write attribute to a file
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	/// Read attribute from a file
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	/// Size of attribute in byes
	virtual S_UINT64 GetSizeInBytes() const;

	/// Get Value Multiplicity
	virtual S_UINT32 GetVM() const;

	/// Get Value Representation
	virtual DcsString GetVR()const;

protected:
	class	ImplAttributeDouble;
	ImplAttributeDouble	*m_pImplAttributeDouble;

	const ImplAttributeDouble* GetImpl() const;
	ImplAttributeDouble* GetImpl();
};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///
/// \class AttributeTag
/// \brief Attribute with VR = AT
///
class AttributeTag : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributeTag();
	///
	/// Initialize with an AttributeTag
	///
	AttributeTag(const AttributeTag &attribute);

	///
	/// Destructor
	///
	virtual ~AttributeTag();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributeTag& operator=(const AttributeTag &attribute);
	///
	/// Compare attribute
	///
	bool operator==(const AttributeTag &attribute)const;
	///
	/// Compare attribute
	///
	bool operator!=(const AttributeTag &attribute)const;

	///
	/// Bracket operator for accessing a specific value in an array of tags
	///
	Tag& operator[](const S_UINT32 nIndex);
	///
	/// Bracket operator for accessing a specific value in an array of tags
	///
	const Tag& operator[](const S_UINT32 nIndex)const;

	///
	/// Set the number of values. Deletes existing values.
	///
	bool SetSize(const S_UINT32 nSize);

	///
	/// Get the number of values
	///
	S_UINT32 GetSize()const;

	///
	/// Set a single value (VM = 1)
	///
	bool SetValue(const Tag &tag);
	///
	/// Get a single value or the first value in an array of values
	///
	bool GetValue(Tag &tag)const;
	///
	/// Set an array of values (VM > 1)
	///
	bool SetValues(const Array1D<Tag> &arrayValues);
	///
	/// Get an array of values
	///
	bool GetValues(Array1D<Tag> &arrayValues)const;

	///
	/// Get reference to values
	///
	const Array1D<Tag>& GetValues()const;

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param arrayValues Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(Array1D<Tag> &arrayValues);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param arrayValues Values moved from this parameter into the attribute
	///
	bool MoveValuesInto(Array1D<Tag> &arrayValues);

	///
	/// Get Value Multiplicity
	///
	virtual S_UINT32 GetVM()const;
	
	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// Get the Attribute's Data Size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;

	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write methods to avoid hiding overrides
	using AttributeCommon::Write; // Bring in Write methods from AttributeCommon

	//////////////////////////////////////////////
	///
	/// Write to file
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
	
	///
	/// Read from file
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);
	//////////////////////////////////////////////

protected:
	class	ImplAttributeTag;
	ImplAttributeTag	*m_pImplAttributeTag;

	///
	/// Reads the data after AttributeCommon::Read
	///
	bool Read_internal(IFile &file, ErrorLog &errorlog, const bool bExplicit);
};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///
/// \class AttributeOther
/// \brief Attribute with VR = OB or OW or OF
///
class AttributeOther : public AttributeCommon
{
public:

	/// \enum OTHER_VR
	/// VR for attribute other
	typedef enum
	{
		enumOB, ///< Other Byte (8bit int)
		enumOW,	///< Other Word (16bit int)
		enumOL, ///< Other Long (32bit int)
		enumOD, ///< Other Double (64bit int)
		enumOF, ///< Other Float (32bit float)
	}OTHER_VR;

	///
	/// Initialize with default values
	///
	AttributeOther();
	///
	/// Initialize with an AttributeOther object
	///
	AttributeOther(const AttributeOther &attrib);
	///
	/// Destructor
	///
	virtual ~AttributeOther();

	///
	/// Copy operator
	///
	AttributeOther& operator=(const AttributeOther &attrib);
	///
	/// Compare attributes
	///
	bool operator==(const AttributeOther &attrib)const;
	///
	/// Compare attributes
	///
	bool operator!=(const AttributeOther &attrib)const;

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Set value from memory buffer
	///
	bool SetValue(const MemoryBuffer &memorybuffer, const OTHER_VR nVR);

	///
	/// Set value from AttributeOther
	///
	bool SetValue(const AttributeOther &attribOther);

	///
	/// Get value as memory buffer.
	///
	bool GetValue(MemoryBuffer &memorybuffer)const;

	///
	/// Get reference to memory buffer
	///
	const MemoryBuffer& GetValue()const;

	///
	/// Get reference to memory buffer
	///
	MemoryBuffer& GetValue();

	///
	/// Move values out of the attribute and into the passed in parameter
	///
	/// @param memorybuffer Attribute's values moved into this parameter
	///
	bool MoveValuesFrom(MemoryBuffer &memorybuffer);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param memorybuffer Values moved from this parameter into the attribute
	/// @param nVR memory buffer value representation
	bool MoveValuesInto(MemoryBuffer &memorybuffer, const OTHER_VR nVR);

	///
	/// Move values into the attribute from the passed in parameter
	///
	/// @param sourceAttribOther Values moved from this parameter into the attribute
	/// @return true/false false if the values could not be moved
	bool MoveValuesInto(AttributeOther& sourceAttribOther);

	///
	/// Set values (VR = OB)
	///
	bool SetValues(const Array1D<S_UINT8> &arrayValues);
	///
	/// Get values as S_UINT8. VR must be OB or OW
	///
	bool GetValues(Array1D<S_UINT8> &arrayValues)const;
	///
	/// Set values (VR = OB)
	///
	bool SetValues(const Array1D<S_INT8> &arrayValues);
	///
	/// Get values as S_INT8. VR must be OB or OW
	///
	bool GetValues(Array1D<S_INT8> &arrayValues)const;

	///
	/// Set values (VR = OW)
	///
	bool SetValues(const Array1D<S_UINT16> &arrayValues);
	///
	/// Get values as S_UINT16. VR must be OW.
	///
	bool GetValues(Array1D<S_UINT16> &arrayValues)const;
	///
	/// Set values (VR = OW)
	///
	bool SetValues(const Array1D<S_INT16> &arrayValues);
	///
	/// Get values as S_INT16. VR must be OW.
	///
	bool GetValues(Array1D<S_INT16> &arrayValues)const;

	///
	/// Set values (VR = OL)
	///
	bool SetValues(const Array1D<S_INT32> &arrayValues);
	///
	/// Get values as S_UINT32. VR must be OL.
	///
	bool GetValues(Array1D<S_INT32> &arrayValues)const;
	///
	/// Set values (VR = OL)
	///
	bool SetValues(const Array1D<S_UINT32> &arrayValues);
	///
	/// Get values as S_UINT32. VR must be OL.
	///
	bool GetValues(Array1D<S_UINT32> &arrayValues)const;

	///
	/// Set values (VR = OL)
	///
	bool SetValues(const Array1D<S_INT64> &arrayValues);
	///
	/// Get values as S_UINT64. VR must be OD.
	///
	bool GetValues(Array1D<S_INT64> &arrayValues)const;
	///
	/// Set values (VR = OL)
	///
	bool SetValues(const Array1D<S_UINT64> &arrayValues);
	///
	/// Get values as S_UINT64. VR must be OD.
	///
	bool GetValues(Array1D<S_UINT64> &arrayValues)const;

	///
	/// Set values (VR = OF)
	///
	bool SetValues(const Array1D<float> &arrayValues);
	///
	/// Get values as float. VR must be OF.
	///
	bool GetValues(Array1D<float> &arrayValues)const;

	///
	/// Check if VR = OB
	///
	bool IsOtherByte()const;
	///
	/// Check if VR = OW
	///
	bool IsOtherWord()const;
	///
	/// Check if VR = OL
	///
	bool IsOtherLong()const;
	///
	/// Check if VR = OD
	///
	bool IsOtherDouble()const;
	///
	/// Check if VR = OF
	///
	bool IsOtherFloat()const;

	//////////////////////////////////////////////
	///
	/// Write to file
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager)const;
	
	using AttributeCommon::Read; // Bring in AttributeCommon Read/Write methods to avoid hiding overrides

	///
	/// Read from file
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &attributemanager);
	//////////////////////////////////////////////

	///
	/// Get Value Multiplicity
	///
	virtual S_UINT32 GetVM()const;
	
	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Representation of AttributeOther as AttributeOther::OTHER_VR
	///
	OTHER_VR GetOtherVR()const;

	///
	/// Get the Attribute's Data Size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;

protected:
	class	ImplAttributeOther;
	ImplAttributeOther	*m_pImplAttributeOther;

	///
	/// Reads the data after AttributeCommon::Read
	///
	bool Read_internal(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager);

	/// Disabled
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///
/// \class AttributeUnknown
/// \brief Attribute with VR = UN. Data is stored in a memory buffer.
///
class AttributeUnknown : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributeUnknown();
	///
	/// Initialize with an AttributeUnknown object
	///
	AttributeUnknown(const AttributeUnknown &attribute);

	///
	/// Destructor
	///
	virtual ~AttributeUnknown();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributeUnknown& operator=(const AttributeUnknown &attribute);

	///
	/// Comparison
	///
	bool operator==(const AttributeUnknown &attribute)const;
	///
	/// Comparison
	///
	bool operator!=(const AttributeUnknown &attribute)const;

	///
	/// Set memory buffer
	//
	bool SetValue(const MemoryBuffer &buffer);

	///
	/// Get memory buffer
	//
	bool GetValue(MemoryBuffer &buffer)const;

	///
	/// Get memory buffer
	//
	const MemoryBuffer& GetValue()const;

	///
	/// Get memory buffer
	///
	MemoryBuffer& GetValue();

	using AttributeCommon::Read; // Bring read methods from base class Attribute Common

	//////////////////////////////////////////////
	///
	/// Read from file
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader);

	///
	/// Write to file
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit) const;
	//////////////////////////////////////////////

	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the Attribute's Data Size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;

protected:
	class	ImplAttributeUnknown;
	ImplAttributeUnknown	*m_pImplAttributeUnknown;

	///
	/// Reads the data after AttributeCommon::Read
	///
	bool Read_internal(IFile &file, ErrorLog &errorlog, const bool bExplicit);
};
///////////////////////////////////////////////////

///
/// \class AttributePixelData
/// \brief Handles pixel data, tag (7FE0, 0010), reading/writing based on transfer syntax. Values stored as 8bit or 16bit data.
class AttributePixelData : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributePixelData();
	///
	/// Initialize with another AttributePixelData object
	///
	AttributePixelData(const AttributePixelData &attrib);

	///
	/// Destructor
	///
	virtual ~AttributePixelData();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributePixelData& operator=(const AttributePixelData& attrib);

	///
	/// Comparison operator
	///
	bool operator==(const AttributePixelData& attrib)const;
	
	///
	/// Comparison operator
	///
	bool operator!=(const AttributePixelData& attrib)const;
	
	///
	/// Returns true if the data is 16bit
	///
	bool Is16Bit()const;

	///
	/// Returns true if the data is 8bit
	///
	bool Is8Bit()const;

	///
	/// Returns the width of the data
	///
	S_UINT16 GetWidth()const;

	///
	/// Returns the height of the data
	///
	S_UINT16 GetHeight()const;

	///
	/// Returns the depth of the data
	///
	S_UINT32 GetDepth()const;

	///
	/// Returns the samples per pixel
	///
	S_UINT32 GetSamplePerPixel()const;

	///
	/// Returns the planar configuration. Used when samples per pixel is greater than 1.
	/// 0: Pixel data configured as 'R1,G1,B1,R2,G2,B2...'. 
	/// 1: Pixel data configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	S_UINT16 GetPlanarConfiguration()const;

	///
	/// Return true if the data is unsigned
	///
	bool IsUnsigned()const;

	///
	/// Set single frame pixel data
	///
	bool SetValue(const Array2D<S_UINT8> &arrayImage);
	///
	/// Set single frame pixel data
	///
	bool SetValue(const Array2D<S_INT8> &arrayImage);
	///
	/// Set multiframe pixel data
	///
	bool SetValue(const Array3DLarge<S_UINT8> &arrayImage);
	///
	/// Set multiframe pixel data
	///
	bool SetValue(const Array3DLarge<S_INT8> &arrayImage);

	///
	/// Set single frame pixel data
	///
	bool SetValue(const Array2D<S_UINT16> &arrayImage);
	///
	/// Set single frame pixel data
	///
	bool SetValue(const Array2D<S_INT16> &arrayImage);
	///
	/// Set multiframe pixel data
	///
	bool SetValue(const Array3DLarge<S_UINT16> &arrayImage);
	///
	/// Set multiframe pixel data
	///
	bool SetValue(const Array3DLarge<S_INT16> &arrayImage);
	///
	/// Set single frame 8bit unsigned RGB pixel data
	///
	/// @param membuffer	Single 2D frame buffer of size nWidth * nHeight * 3
	/// @param nWidth		Width of frame
	/// @param nHeight		Height of frame
	/// @param nPlanarConfiguration	Configuration of RGB data in buffer. 0: Data in buffer configured as 'R1,G1,B1,R2,G2,B2...'. 1: Data in buffer configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	bool SetValueRGB(const MemoryBuffer &membuffer, const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT16 nPlanarConfiguration);
	///
	/// Set multiframe 8bit unsigned RGB pixel data
	///
	/// @param arrayMembuffer	Array of 2D frames. 
	///							If nPlanarConfiguration = 0 : Each frame is of size nWidth * nHeight * 3 and arrayMembuffer's size is the number of frames
	///							If nPlanarConfiguration = 1 : Each frame is of size nWidth * nHeight and arrayMembuffer's size is 3x the number of frames
	/// @param nWidth			Width of frame
	/// @param nHeight			Height of frame
	/// @param nPlanarConfiguration	Configuration of RGB data per frame. 0: Data in buffer configured as 'R1,G1,B1,R2,G2,B2...'. 1: Data in buffer configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	bool SetValueRGB(const Array1D<MemoryBuffer> &arrayMembuffer, const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT16 nPlanarConfiguration);
	///
	/// Set single frame 8bit unsigned RGBA pixel data
	///
	/// @param membuffer	Single 2D frame buffer of size nWidth * nHeight * 4
	/// @param nWidth		Width of frame
	/// @param nHeight		Height of frame
	/// @param nPlanarConfiguration	Configuration of RGB data in buffer. 0: Data in buffer configured as 'R1,G1,B1,A1,R2,G2,B2,A2...'. 1: Data in buffer configured as 'R1,R2,...,G1,G2,...,B1,B2,...,A1,A2,...'
	///
	bool SetValueRGBA(const MemoryBuffer &membuffer, const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT16 nPlanarConfiguration);
	///
	/// Set multiframe 8bit unsigned RGBA pixel data
	///
	/// @param arrayMembuffer	Array of 2D frames.
	///							If nPlanarConfiguration = 0 : Each frame is of size nWidth * nHeight * 4 and arrayMembuffer's size is the number of frames
	///							If nPlanarConfiguration = 1 : Each frame is of size nWidth * nHeight and arrayMembuffer's size is 4x the number of frames
	/// @param nWidth			Width of frame
	/// @param nHeight			Height of frame
	/// @param nPlanarConfiguration	Configuration of RGBA data per frame. 0: Data in buffer configured as 'R1,G1,B1,A1,R2,G2,B2,A2...'. 1: Data in buffer configured as 'R1,R2,...,G1,G2,...,B1,B2,...,A1,A2,...'
	///
	bool SetValueRGBA(const Array1D<MemoryBuffer> &arrayMembuffer, const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT16 nPlanarConfiguration);

	///
	/// Get single frame data. If data is multiframe, get the first frame.
	///
	bool GetValue(Array2D<S_UINT8> &arrayImage)const;
	///
	/// Get single frame data. If data is multiframe, get the first frame.
	///
	bool GetValue(Array2D<S_INT8> &arrayImage)const;
	///
	/// Get multiframe data
	///
	bool GetValue(Array3DLarge<S_UINT8> &arrayImage)const;
	///
	/// Get multiframe data
	///
	bool GetValue(Array3DLarge<S_INT8> &arrayImage)const;

	///
	/// Get single frame data. If data is multiframe, get the first frame. Converts unsigned 8bit to unsigned 16bit.
	///
	bool GetValue(Array2D<S_UINT16> &arrayImage)const;
	///
	/// Get single frame data. If data is multiframe, get the first frame. Converts signed 8bit to signed 16bit.
	///
	bool GetValue(Array2D<S_INT16> &arrayImage)const;
	///
	/// Get multiframe data. Converts unsigned 8bit to unsigned 16bit.
	///
	bool GetValue(Array3DLarge<S_UINT16> &arrayImage)const;
	///
	/// Get multiframe data. Converts signed 8bit to signed 16bit.
	///
	bool GetValue(Array3DLarge<S_INT16> &arrayImage)const;
	///
	/// @see SetValueRGB
	///
	bool GetValueRGB(MemoryBuffer &membuffer, S_UINT16 &nWidth, S_UINT16 &nHeight, S_UINT16 &nPlanarConfiguration)const;
	///
	/// @see SetValueRGB
	///
	bool GetValueRGB(Array1D<MemoryBuffer> &arrayMembuffer, S_UINT16 &nWidth, S_UINT16 &nHeight, S_UINT16 &nPlanarConfiguration)const;
	///
	/// @see SetValueRGB
	///
	bool GetValueRGBA(MemoryBuffer &membuffer, S_UINT16 &nWidth, S_UINT16 &nHeight, S_UINT16 &nPlanarConfiguration)const;
	///
	/// @see SetValueRGB
	///
	bool GetValueRGBA(Array1D<MemoryBuffer> &arrayMembuffer, S_UINT16 &nWidth, S_UINT16 &nHeight, S_UINT16 &nPlanarConfiguration)const;

	/// Allocate the volume and use GetUnsigned8Bit() to fill in the data.
	///
	/// For number of samples greater than 1:
	///		- If nPlanarConfiguration = 0 : Each slice stores RGBA samples. A sample is accessed with (*GetUnsigned8Bit())[nSlice][nRow][nColumn + 0,1,2,3]
	///		- If nPlanarConfiguration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with (*GetUnsigned8Bit())[nSlice + 0,1,2,3][nRow][nColumn]
	///
	/// @param nWidth Width of slice
	/// @param nHeight Height of slice
	/// @param nDepth Number of slices. Set to 1 for 2D.
	/// @param nNumSamples Number of samples per voxel or pixel
	/// @param nPlanarConfiguration Planar configuration = 0 or 1. If 0, samples are stored as RGBA, RGBA, RGBA, etc. If 1, samples are stored as RRRRR..., GGGGG..., BBBBB..., AAAA....
	/// @see GetUnsigned8Bit
	bool SetUnsigned8Bit(const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT32 nDepth, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Allocate the volume and use GetSigned8Bit() to fill in the data.
	///
	/// For number of samples greater than 1:
	///		- If nPlanarConfiguration = 0 : Each slice stores RGBA samples. A sample is accessed with (*GetSigned8Bit())[nSlice][nRow][nColumn + 0,1,2,3]
	///		- If nPlanarConfiguration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with (*GetSigned8Bit())[nSlice + 0,1,2,3][nRow][nColumn]
	///
	/// @param nWidth Width of slice
	/// @param nHeight Height of slice
	/// @param nDepth Number of slices. Set to 1 for 2D.
	/// @param nNumSamples Number of samples per voxel or pixel
	/// @param nPlanarConfiguration Planar configuration = 0 or 1. If 0, samples are stored as RGBA, RGBA, RGBA, etc. If 1, samples are stored as RRRRR..., GGGGG..., BBBBB..., AAAA....
	/// @see GetSigned8Bit
	bool SetSigned8Bit(const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT32 nDepth, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Allocate the volume and use GetUnsigned16Bit() to fill in the data.
	///
	/// For number of samples greater than 1:
	///		- If nPlanarConfiguration = 0 : Each slice stores RGBA samples. A sample is accessed with (*GetUnsigned16Bit())[nSlice][nRow][nColumn + 0,1,2,3]
	///		- If nPlanarConfiguration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with (*GetUnsigned16Bit())[nSlice + 0,1,2,3][nRow][nColumn]
	///
	/// @param nWidth Width of slice
	/// @param nHeight Height of slice
	/// @param nDepth Number of slices. Set to 1 for 2D.
	/// @param nNumSamples Number of samples per voxel or pixel
	/// @param nPlanarConfiguration Planar configuration = 0 or 1. If 0, samples are stored as RGBA, RGBA, RGBA, etc. If 1, samples are stored as RRRRR..., GGGGG..., BBBBB..., AAAA....
	/// @see GetUnsigned16Bit
	bool SetUnsigned16Bit(const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT32 nDepth, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Allocate the volume and use GetSigned16Bit() to fill in the data.
	///
	/// For number of samples greater than 1:
	///		- If nPlanarConfiguration = 0 : Each slice stores RGBA samples. A sample is accessed with (*GetSigned16Bit())[nSlice][nRow][nColumn + 0,1,2,3]
	///		- If nPlanarConfiguration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with (*GetSigned16Bit())[nSlice + 0,1,2,3][nRow][nColumn]
	///
	/// @param nWidth Width of slice
	/// @param nHeight Height of slice
	/// @param nDepth Number of slices. Set to 1 for 2D.
	/// @param nNumSamples Number of samples per voxel or pixel
	/// @param nPlanarConfiguration Planar configuration = 0 or 1. If 0, samples are stored as RGBA, RGBA, RGBA, etc. If 1, samples are stored as RRRRR..., GGGGG..., BBBBB..., AAAA....
	/// @see GetSigned16Bit
	bool SetSigned16Bit(const S_UINT16 nWidth, const S_UINT16 nHeight, const S_UINT32 nDepth, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not unsigned 8 bit, S_NULL is returned.
	Array3DLarge<S_UINT8>*			GetUnsigned8Bit();
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not unsigned 8 bit, S_NULL is returned.
	const Array3DLarge<S_UINT8>*	GetUnsigned8Bit()const;
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not signed 8 bit, S_NULL is returned.
	Array3DLarge<S_INT8>*			GetSigned8Bit();
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not signed 8 bit, S_NULL is returned.
	const Array3DLarge<S_INT8>*		GetSigned8Bit()const;
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not unsigned 16 bit, S_NULL is returned.
	Array3DLarge<S_UINT16>*			GetUnsigned16Bit();
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not unsigned 16 bit, S_NULL is returned.
	const Array3DLarge<S_UINT16>*	GetUnsigned16Bit()const;
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not signed 16 bit, S_NULL is returned.
	Array3DLarge<S_INT16>*			GetSigned16Bit();
	/// Returns pointer to volume data. 2D data is represented as a single slice volume.
	/// If data is not signed 16 bit, S_NULL is returned.
	const Array3DLarge<S_INT16>*	GetSigned16Bit()const;

	/// Move data from this attribute to the parameter
	///
	/// @param pixeldata Data is moved into this parameter from the attribute
	bool MoveFrom(AttributePixelData &pixeldata);

	/// Move data into this attribute from the parameter
	///
	/// @param pixeldata Data moved from this parameter into the attribute
	bool MoveInto(AttributePixelData &pixeldata);

	/// Move data from this attribute to the parameter
	///
	/// @param volDst Data is moved into this parameter from the attribute
	bool MoveFrom(Volume &volDst);
	/// Move data into this attribute from the parameter
	///
	/// @param volSrc pixel data moved from this parameter into the attribute
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool MoveInto(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Get references to the pixel data's slices. Stores pointers to each slice's data.
	/// If this object is deleted, then volDst must be reset with a call to volDst.FreeMemory()
	bool GetReference(Volume &volDst);
	/// Set this object as a reference to volSrc. Stores pointers to each slice's data.
	/// If volSrc is deleted, then this object must be reset with a call to FreeMemory()
	///
	/// @param volSrc The pixel data to reference
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool SetAsReference(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Returns true if this object owns its pixel data and is not a reference
	bool OwnsData()const;

	using AttributeCommon::Read;

	///
	/// Read the Attribute Common data from the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Report errors in this ErrorLog
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param attributeManager Attribute manager to lookup data and dependencies.
	/// @return true/false
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &attributeManager);

	///
	/// Write to file
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager)const;

	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity. Always returns 1.
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the total uncompressed image size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;
protected:
	class ImplAttributePixelData;
	ImplAttributePixelData *m_pImplAttributePixelData; ///< Internal implementation

	///
	/// Disabled
	///
	virtual bool SetTag(const Tag& tag);

	///
	/// Disabled
	///
	virtual bool SetTag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Disabled
	///
	virtual void ClearTag();

	///
	/// Disabled
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
};
///////////////////////////////////////////////////

///
/// \class AttributePixelData32Bit
/// \brief Handles 32 bit pixel data, tag (7FE0, 0011), reading/writing based on transfer syntax. Only uncompressed transfer syntax is supported.
class AttributePixelData32Bit : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributePixelData32Bit();
	///
	/// Initialize with another AttributePixelData object
	///
	AttributePixelData32Bit(const AttributePixelData32Bit &attrib);

	///
	/// Destructor
	///
	virtual ~AttributePixelData32Bit();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributePixelData32Bit& operator=(const AttributePixelData32Bit& attrib);

	///
	/// Comparison operator
	///
	bool operator==(const AttributePixelData32Bit& attrib)const;

	///
	/// Comparison operator
	///
	bool operator!=(const AttributePixelData32Bit& attrib)const;

	///
	/// Returns the width of the data
	///
	S_UINT16 GetWidth()const;

	///
	/// Returns the height of the data
	///
	S_UINT16 GetHeight()const;

	///
	/// Returns the depth of the data
	///
	S_UINT32 GetDepth()const;

	///
	/// Returns the samples per pixel
	///
	S_UINT32 GetSamplePerPixel()const;

	///
	/// Returns the planar configuration. Used when samples per pixel is greater than 1.
	/// 0: Pixel data configured as 'R1,G1,B1,R2,G2,B2...'. 
	/// 1: Pixel data configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	S_UINT16 GetPlanarConfiguration()const;

	///
	/// Return true if the data is unsigned
	///
	bool IsUnsigned()const;
	///
	/// Return true if the data is signed
	///
	bool IsSigned()const;

	/// Set pixel data to signed. Deletes existing data.
	bool SetSigned(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const S_UINT32 nSamplesPerPixel = 1, const S_UINT16 nPlanarConfiguration = 0);
	/// Set pixel data to unsigned. Deletes existing data.
	bool SetUnsigned(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const S_UINT32 nSamplesPerPixel = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Returns NULL if data is signed. 
	/// If samples per pixel is greater than 1 and planar configuration is 0. Ex. 4 samples per pixel, Pixel = array3d[z][y][x*nSamplesPerPixel + 0,1,2,3]. array3d.GetWidth() is equal to this->GetWidth() * this->GetSamplePerPixel()
	/// If samples per pixel is greater than 1 and planar configuration is 1. Ex. 4 samples per pixel, Pixel = array3d[z*nSamplesPerPixel + 0,1,2,3][y][x]. array3d.GetDepth() is equal to this->GetDepth() * this->GetSamplePerPixel()
	Array3DLarge<S_UINT32>* GetAsUnsigned();
	/// Returns NULL if data is signed
	const Array3DLarge<S_UINT32>* GetAsUnsigned()const;

	/// Returns NULL if data is unsigned
	Array3DLarge<S_INT32>* GetAsSigned();
	/// Returns NULL if data is unsigned
	const Array3DLarge<S_INT32>* GetAsSigned()const;

	using AttributeCommon::Read;

	/// Move data from this attribute to the parameter
	///
	/// @param pixeldata Data is moved into this parameter from the attribute
	bool MoveFrom(AttributePixelData32Bit &pixeldata);

	/// Move data into this attribute from the parameter
	///
	/// @param pixeldata Data moved from this parameter into the attribute
	bool MoveInto(AttributePixelData32Bit &pixeldata);

	/// Move data from this attribute to the parameter
	///
	/// @param volDst Data is moved into this parameter from the attribute
	bool MoveFrom(Volume &volDst);
	/// Move data into this attribute from the parameter
	///
	/// @param volSrc pixel data moved from this parameter into the attribute
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool MoveInto(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Get references to the pixel data's slices. Stores pointers to each slice's data.
	/// If this object is deleted, then volDst must be reset with a call to volDst.FreeMemory()
	bool GetReference(Volume &volDst);
	/// Set this object as a reference to volSrc. Stores pointers to each slice's data.
	/// If volSrc is deleted, then this object must be reset with a call to FreeMemory()
	///
	/// @param volSrc The pixel data to reference
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool SetAsReference(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Returns true if this object owns its pixel data and is not a reference
	bool OwnsData()const;

	///
	/// Read the Attribute Common data from the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Report errors in this ErrorLog
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param attributeManager Attribute manager to lookup data and dependencies.
	/// @return true/false
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &attributeManager);

	///
	/// Write to file
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager)const;

	///
	/// Get Value Representation. Always returns "OL"
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity. Always returns 1.
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the total uncompressed image size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;
protected:
	class ImplAttributePixelData;
	ImplAttributePixelData *m_pImplAttributePixelData; ///< Internal implementation

	///
	/// Disabled
	///
	virtual bool SetTag(const Tag& tag);

	///
	/// Disabled
	///
	virtual bool SetTag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Disabled
	///
	virtual void ClearTag();

	///
	/// Disabled
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
};
///////////////////////////////////////////////////

///
/// \class AttributePixelData64Bit
/// \brief Handles 64 bit pixel data, tag (7FE0, 0012), reading/writing based on transfer syntax. Only uncompressed transfer syntax is supported.
class AttributePixelData64Bit : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributePixelData64Bit();
	///
	/// Initialize with another AttributePixelData object
	///
	AttributePixelData64Bit(const AttributePixelData64Bit &attrib);

	///
	/// Destructor
	///
	virtual ~AttributePixelData64Bit();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributePixelData64Bit& operator=(const AttributePixelData64Bit& attrib);

	///
	/// Comparison operator
	///
	bool operator==(const AttributePixelData64Bit& attrib)const;

	///
	/// Comparison operator
	///
	bool operator!=(const AttributePixelData64Bit& attrib)const;

	///
	/// Returns the width of the data
	///
	S_UINT16 GetWidth()const;

	///
	/// Returns the height of the data
	///
	S_UINT16 GetHeight()const;

	///
	/// Returns the depth of the data
	///
	S_UINT32 GetDepth()const;

	///
	/// Returns the samples per pixel
	///
	S_UINT32 GetSamplePerPixel()const;

	///
	/// Returns the planar configuration. Used when samples per pixel is greater than 1.
	/// 0: Pixel data configured as 'R1,G1,B1,R2,G2,B2...'. 
	/// 1: Pixel data configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	S_UINT16 GetPlanarConfiguration()const;

	///
	/// Return true if the data is unsigned
	///
	bool IsUnsigned()const;
	///
	/// Return true if the data is signed
	///
	bool IsSigned()const;

	/// Set pixel data to signed. Deletes existing data.
	bool SetSigned(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const S_UINT32 nSamplesPerPixel = 1, const S_UINT16 nPlanarConfiguration = 0);
	/// Set pixel data to unsigned. Deletes existing data.
	bool SetUnsigned(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const S_UINT32 nSamplesPerPixel = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Returns NULL if data is signed. 
	/// If samples per pixel is greater than 1 and planar configuration is 0. Ex. 4 samples per pixel, Pixel = array3d[z][y][x*nSamplesPerPixel + 0,1,2,3]. array3d.GetWidth() is equal to this->GetWidth() * this->GetSamplePerPixel()
	/// If samples per pixel is greater than 1 and planar configuration is 1. Ex. 4 samples per pixel, Pixel = array3d[z*nSamplesPerPixel + 0,1,2,3][y][x]. array3d.GetDepth() is equal to this->GetDepth() * this->GetSamplePerPixel()
	Array3DLarge<S_UINT64>* GetAsUnsigned();
	/// Returns NULL if data is signed
	const Array3DLarge<S_UINT64>* GetAsUnsigned()const;

	/// Returns NULL if data is unsigned
	Array3DLarge<S_INT64>* GetAsSigned();
	/// Returns NULL if data is unsigned
	const Array3DLarge<S_INT64>* GetAsSigned()const;

	using AttributeCommon::Read;

	/// Move data from this attribute to the parameter
	///
	/// @param pixeldata Data is moved into this parameter from the attribute
	bool MoveFrom(AttributePixelData64Bit &pixeldata);

	/// Move data into this attribute from the parameter
	///
	/// @param pixeldata Data moved from this parameter into the attribute
	bool MoveInto(AttributePixelData64Bit &pixeldata);

	/// Move data from this attribute to the parameter
	///
	/// @param volDst Data is moved into this parameter from the attribute
	bool MoveFrom(Volume &volDst);
	/// Move data into this attribute from the parameter
	///
	/// @param volSrc pixel data moved from this parameter into the attribute
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool MoveInto(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Get references to the pixel data's slices. Stores pointers to each slice's data.
	/// If this object is deleted, then volDst must be reset with a call to volDst.FreeMemory()
	bool GetReference(Volume &volDst);
	/// Set this object as a reference to volSrc. Stores pointers to each slice's data.
	/// If volSrc is deleted, then this object must be reset with a call to FreeMemory()
	///
	/// @param volSrc The pixel data to reference
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool SetAsReference(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Returns true if this object owns its pixel data and is not a reference
	bool OwnsData()const;

	///
	/// Read the Attribute Common data from the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Report errors in this ErrorLog
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param attributeManager Attribute manager to lookup data and dependencies.
	/// @return true/false
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &attributeManager);

	///
	/// Write to file
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager)const;

	///
	/// Get Value Representation. Always returns "OD"
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity. Always returns 1.
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the total uncompressed image size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;
protected:
	class ImplAttributePixelData;
	ImplAttributePixelData *m_pImplAttributePixelData; ///< Internal implementation

	///
	/// Disabled
	///
	virtual bool SetTag(const Tag& tag);

	///
	/// Disabled
	///
	virtual bool SetTag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Disabled
	///
	virtual void ClearTag();

	///
	/// Disabled
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
};
///////////////////////////////////////////////////

///
/// \class AttributePixelData32BitFloat
/// \brief Handles 32 bit float pixel data, tag (7FE0, 0013), reading/writing based on transfer syntax. Only uncompressed transfer syntax is supported.
class AttributePixelData32BitFloat : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributePixelData32BitFloat();
	///
	/// Initialize with another AttributePixelData object
	///
	AttributePixelData32BitFloat(const AttributePixelData32BitFloat &attrib);

	///
	/// Destructor
	///
	virtual ~AttributePixelData32BitFloat();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributePixelData32BitFloat& operator=(const AttributePixelData32BitFloat& attrib);

	///
	/// Comparison operator
	///
	bool operator==(const AttributePixelData32BitFloat& attrib)const;

	///
	/// Comparison operator
	///
	bool operator!=(const AttributePixelData32BitFloat& attrib)const;

	///
	/// Returns the width of the data
	///
	S_UINT16 GetWidth()const;

	///
	/// Returns the height of the data
	///
	S_UINT16 GetHeight()const;

	///
	/// Returns the depth of the data
	///
	S_UINT32 GetDepth()const;

	///
	/// Returns the samples per pixel
	///
	S_UINT32 GetSamplePerPixel()const;

	///
	/// Returns the planar configuration. Used when samples per pixel is greater than 1.
	/// 0: Pixel data configured as 'R1,G1,B1,R2,G2,B2...'. 
	/// 1: Pixel data configured as 'R1,R2,...,G1,G2,...,B1,B2,...'
	///
	S_UINT16 GetPlanarConfiguration()const;

	/// Set the size, samples per pixel, and planar configuration
	bool SetSize(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const S_UINT32 nSamplesPerPixel = 1, const S_UINT16 nPlanarConfiguration = 0);

	/// Returns pixel data as volume
	/// If samples per pixel is greater than 1 and planar configuration is 0. Ex. 4 samples per pixel, Pixel = array3d[z][y][x*nSamplesPerPixel + 0,1,2,3]. array3d.GetWidth() is equal to this->GetWidth() * this->GetSamplePerPixel()
	/// If samples per pixel is greater than 1 and planar configuration is 1. Ex. 4 samples per pixel, Pixel = array3d[z*nSamplesPerPixel + 0,1,2,3][y][x]. array3d.GetDepth() is equal to this->GetDepth() * this->GetSamplePerPixel()
	Array3DLarge<float>* GetData();
	/// Returns pixel data as volume
	const Array3DLarge<float>* GetData()const;

	using AttributeCommon::Read;

	/// Move data from this attribute to the parameter
	///
	/// @param pixeldata Data is moved into this parameter from the attribute
	bool MoveFrom(AttributePixelData32BitFloat &pixeldata);

	/// Move data into this attribute from the parameter
	///
	/// @param pixeldata Data moved from this parameter into the attribute
	bool MoveInto(AttributePixelData32BitFloat &pixeldata);

	/// Move data from this attribute to the parameter
	///
	/// @param volDst Data is moved into this parameter from the attribute
	bool MoveFrom(Volume &volDst);
	/// Move data into this attribute from the parameter
	///
	/// @param volSrc pixel data moved from this parameter into the attribute
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool MoveInto(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Get references to the pixel data's slices. Stores pointers to each slice's data.
	/// If this object is deleted, then volDst must be reset with a call to volDst.FreeMemory()
	bool GetReference(Volume &volDst);
	/// Set this object as a reference to volSrc. Stores pointers to each slice's data.
	/// If volSrc is deleted, then this object must be reset with a call to FreeMemory()
	///
	/// @param volSrc The pixel data to reference
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Planar Configuration = 0 : Each slice stores RGBA samples. A sample is accessed with volSrc[nSlice][nRow][nColumn + 0,1,2,3]
	///							Planar Configuration = 1 : Each slice stores single R, G, B, or A sample. A sample is accessed with volSrc[nSlice + 0,1,2,3][nRow][nColumn]
	bool SetAsReference(Volume &volSrc, const S_UINT16 nNumSamples = 1, const S_UINT16 nPlanarConfig = 0);

	/// Returns true if this object owns its pixel data and is not a reference
	bool OwnsData()const;

	///
	/// Read the Attribute Common data from the indicated file
	///
	/// @param file File to read from
	/// @param errorlog Report errors in this ErrorLog
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param attributeManager Attribute manager to lookup data and dependencies.
	/// @return true/false
	///
	virtual bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &attributeManager);

	///
	/// Write to file
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributeManager)const;

	///
	/// Get Value Representation. Always returns "OF"
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity. Always returns 1.
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the total uncompressed image size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;
protected:
	class ImplAttributePixelData;
	ImplAttributePixelData *m_pImplAttributePixelData; ///< Internal implementation

	///
	/// Disabled
	///
	virtual bool SetTag(const Tag& tag);

	///
	/// Disabled
	///
	virtual bool SetTag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Disabled
	///
	virtual void ClearTag();

	///
	/// Disabled
	///
	virtual bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;
};

///////////////////////////////////////////////////

class AttributeSequence;
namespace Network { class DcsClient; }

///////////////////////////////////////////////////
///
/// \class AttributeManager
/// \brief Holds all the attributes
///
class AttributeManager
{
public:

	///
	/// \class AttributePointer
	/// \brief Pointer to an attribute
	///
	template<typename ATTRIB_TYPE>
	class AttributePointer
	{
	public:
		AttributePointer() {m_pattrib = S_NULL;}

		friend bool operator==(const AttributePointer<ATTRIB_TYPE>& p0, const ATTRIB_TYPE* p1) { return (p0.m_pattrib == p1); }
		friend bool operator==(const ATTRIB_TYPE* p0, const AttributePointer<ATTRIB_TYPE>& p1) { return (p0 == p1.m_pattrib);}
		friend bool operator!=(const AttributePointer<ATTRIB_TYPE>& p0, const ATTRIB_TYPE* p1) { return (p0.m_pattrib != p1); }
		friend bool operator!=(const ATTRIB_TYPE* p0, const AttributePointer<ATTRIB_TYPE>& p1) { return (p0 != p1.m_pattrib);}

		operator bool() const { return (NULL != m_pattrib); }

		/// Dereference operator
		const ATTRIB_TYPE& operator*() const { return (*m_pattrib); }
		ATTRIB_TYPE& operator*() { return (*m_pattrib); }

		ATTRIB_TYPE* operator->() { return m_pattrib; }
		const ATTRIB_TYPE* operator->() const { return m_pattrib; }
		
		ATTRIB_TYPE *m_pattrib;
	};

	///
	/// \struct OverlayPlane
	/// \brief A struct for holding overlay plane attribute pointers
	///
	struct OverlayPlane
	{
		S_UINT16 m_nGroup;
		AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> m_attptrRows; //(60XX, 0010)
		AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> m_attptrColumns; //(60XX, 0011)
		AttributeManager::AttributePointer<AttributeString> m_attptrType; //(60XX, 0040)
		AttributeManager::AttributePointer<AttributeSignedInt16Bit> m_attptrOrigin; //(60XX, 0050)
		AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> m_attptrBitsAllocated; //(60XX, 0100)
		AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> m_attptrBitPosition; //(60XX, 0102)
		AttributeManager::AttributePointer<AttributeOther> m_attptrData; //(60XX, 3000)
		AttributeManager::AttributePointer<AttributeString> m_attptrDescription; //(60XX, 0022)
		AttributeManager::AttributePointer<AttributeString> m_attptrSubtype; //(60XX, 0045)
		AttributeManager::AttributePointer<AttributeString> m_attptrLabel; //(60XX, 1500)
		AttributeManager::AttributePointer<AttributeString> m_attptrROIArea; //(60XX, 1301)
		AttributeManager::AttributePointer<AttributeString> m_attptrROIMean; //(60XX, 1302)
		AttributeManager::AttributePointer<AttributeString> m_attptrStandardDeviation; //(60XX, 1303)
	};

	/// Attribute filter based on searches from calls to FindAttribute
	typedef enum
	{
		enumAll,				///< All attributes
		enumSearchedOnly,		///< Attributes that have been searched for
		enumNotSearchedOnly,	///< Attributes that have not been searched for
		enumNotDICOSTag,		///< Attribute with Tag that is not in the DICOS spec.
	}SEARCHEDATTRIB;

	///
	/// Initialize with default values
	///
	AttributeManager();
	///
	/// Initialize with another AttributeManager object
	///
	AttributeManager(const AttributeManager &attributemanager);
	///
	/// Destructor
	///
	virtual ~AttributeManager();

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	///
	/// Copy operator
	///
	AttributeManager& operator=(const AttributeManager &attributemanager);

	///
	/// Comparison operator
	///
	bool operator==(const AttributeManager &attributemanager)const;
	///
	/// Comparison operator
	///
	bool operator!=(const AttributeManager &attributemanager)const;

	///
	/// Returns true if the attribute with the specified tag is present
	///
	bool HasAttribute(const S_UINT16 nGroup, const S_UINT16 nElement)const;

	///
	/// Returns true if the attribute with the specified tag is present
	///
	bool HasAttribute(const Tag &tag)const;

	///
	/// Get the VR of a specific attribute stored in the manager
	///
	bool GetAttributeVR(const S_UINT16 nGroup, const S_UINT16 nElement, DcsString &strVR)const;

	///
	/// Get the VR of a specific attribute stored in the manager
	/// @return true/false if attribute is present
	///
	bool GetAttributeVR(const Tag &tag, DcsString &strVR)const;

	///
	/// Delete an attribute in the manager
	///	@param nGroup Tag group
	/// @param nElement Tag element
	/// @param bSearchSequences Flag to search and delete attribute from sequences
	///
	bool DeleteAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, const bool bSearchSequences = false);

	///
	/// Delete an attribute in the manager
	///
	bool DeleteAttribute(const Tag &tag, const bool bSearchSequences = false);

	/// Delete pixel data (8-16bit)
	void DeletePixelData();
	/// Delete pixel data (32bit)
	void DeletePixelData32Bit();
	/// Delete pixel data (64bit)
	void DeletePixelData64Bit();
	/// Delete pixel data (32bit Float)
	void DeletePixelData32BitFloat();

	///
	/// Write a listing of all the attributes as text to file. Includes tag, VR, and values.
	///
	/// @param filename	File to write data to.
	/// @param bWriteData true: write attribute data. false: write attribute tag and VR only
	/// @param nfilter Filter which attributes written out. Attributes are marked as searched when FindAttribute returns true and it does not allocate the attribute
	///
	bool WriteToFileAsText(const Filename &filename, const bool bWriteData = true, const SEARCHEDATTRIB nfilter = enumAll)const;

	///
	/// Write a listing of all the attributes as text to file. Includes tag, VR, and values.
	///
	/// @param file	File object to write attribute data to.
	/// @param bWriteData true: write attribute data. false: write attribute tag and VR only
	/// @param nfilter Filter which attributes written out. Attributes are marked as searched when FindAttribute returns true and it does not allocate the attribute
	///
	bool WriteToFileAsText(IFile &file, const bool bWriteData = true, const SEARCHEDATTRIB nfilter = enumAll)const;

	///
	/// Get a copy of the attribute manager that only include the filtered attributes.
	/// Sequences excluded from the filter, but including attributes that match the filter, will also be included as references and are flagged as such
	///
	void GetFilteredCopy(const SEARCHEDATTRIB nfilter, AttributeManager &manager)const;

	/// Provide a memory manager responsible for allocating pixel data slices to the read process.
	/// This provides a way of managing memory allocation and deallocation of pixel data.
	///
	/// During the read process, if this SDK needs to allocate a slice it will call IMemoryManager::Allocate()
	/// instead of allocating the memory internally. When this SDK needs to deallocate the slice it 
	/// will call IMemoryManager::Deallocate() instead of deleting it internally.
	///
	/// For pixel data with more than 1 sample per pixel or voxel:
	/// If using planar configuration 0: Slices are allocated with size (bytes) = WIDTH * HEIGHT * NUM_SAMPLES * SIZE_OF_TYPE.
	///		This allocates all samples per slice.
	/// If using planar configuration 1: Slices are allocated with size (bytes) = WIDTH * HEIGHT * SIZE_OF_TYPE.
	///		This allocates a slice for each sample (i.e. For RGB: a slice for R samples, a slice for G samples, and a slice for B samples)
	///
	/// SIZE_OF_TYPE = The size of the pixel data's type, such as S_UINT8, S_UINT16, etc.
	///
	/// \ref IMemoryManager
	void SetPixelDataMemoryManager(IMemoryManager *pMemManager);
	/// @see SetPixelDataMemoryManager
	IMemoryManager* GetPixelDataMemoryManager()const;

	///
	/// Set pixel data
	///
	bool SetPixelData(const AttributePixelData &attribPixelData);

	///
	/// Get pixel data
	///
	bool GetPixelData(AttributePixelData &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	///
	bool GetPixelData(AttributePointer<AttributePixelData> &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	/// @param bAllocateIfNotFound Allocate the attribute in the manager if it's not found
	///
	bool GetPixelData(AttributePointer<AttributePixelData> &attribPixelData, const bool bAllocateIfNotFound);

	///
	/// Set pixel data
	///
	bool SetPixelData(const AttributePixelData32Bit &attribPixelData);

	///
	/// Get pixel data
	///
	bool GetPixelData(AttributePixelData32Bit &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	///
	bool GetPixelData(AttributePointer<AttributePixelData32Bit> &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	/// @param bAllocateIfNotFound Allocate the attribute in the manager if it's not found
	///
	bool GetPixelData(AttributePointer<AttributePixelData32Bit> &attribPixelData, const bool bAllocateIfNotFound);

	///
	/// Set pixel data
	///
	bool SetPixelData(const AttributePixelData64Bit &attribPixelData);

	///
	/// Get pixel data
	///
	bool GetPixelData(AttributePixelData64Bit &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	///
	bool GetPixelData(AttributePointer<AttributePixelData64Bit> &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	/// @param bAllocateIfNotFound Allocate the attribute in the manager if it's not found
	///
	bool GetPixelData(AttributePointer<AttributePixelData64Bit> &attribPixelData, const bool bAllocateIfNotFound);

	///
	/// Set pixel data
	///
	bool SetPixelData(const AttributePixelData32BitFloat &attribPixelData);

	///
	/// Get pixel data
	///
	bool GetPixelData(AttributePixelData32BitFloat &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	///
	bool GetPixelData(AttributePointer<AttributePixelData32BitFloat> &attribPixelData)const;
	///
	/// Get pixel data
	///
	/// @param attribPixelData Reference to attribute
	/// @param bAllocateIfNotFound Allocate the attribute in the manager if it's not found
	///
	bool GetPixelData(AttributePointer<AttributePixelData32BitFloat> &attribPixelData, const bool bAllocateIfNotFound);

	/// Finds the attribute with the SOP class UID
	bool FindSopClassUID(DcsString &dsUID)const;
	/// Finds the attribute with the SOP instance UID
	bool FindSopInstanceUID(DcsString &dsUID)const;
	/// Finds the attribute with the scan instance UID
	bool FindScanInstanceUID(DcsString &dsUID)const;
	/// Finds the attribute with the series instance UID
	bool FindSeriesInstanceUID(DcsString &dsUID)const;

	///
	/// Set an attribute. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	/// The AttributeManager takes ownership of the data referenced by pAttrCommon.
	///
	bool SetAttribute(const AttributeCommon *pAttrCommon);
	///
	/// Set an attribute. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeString &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeSignedInt16Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeUnsignedInt16Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeSignedInt32Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeUnsignedInt32Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeSignedInt64Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeUnsignedInt64Bit &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeFloat &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeDouble &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeTag &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeOther &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeSequence &attribute);
	///
	/// Set an attribute. Padding will be added if needed within this function. If the item already exists as a different attribute class, then it will not be overwritten (Ex. Call with AttributeString, but the existing attribute is an AttributeOther).
	///
	bool SetAttribute(const AttributeUnknown &attribute);
	///
	/// Set pixel data
	///
	bool SetAttribute(const AttributePixelData &attribPixelData);
	///
	/// Set pixel data
	///
	bool SetAttribute(const AttributePixelData32Bit &attribPixelData);
	///
	/// Set pixel data
	///
	bool SetAttribute(const AttributePixelData64Bit &attribPixelData);
	///
	/// Set pixel data
	///
	bool SetAttribute(const AttributePixelData32BitFloat &attribPixelData);

	/// 
	/// Utility method to set Object of Inspection ID (0x0010,0x0020)
	/// @param dsOOIId Object of Inspection ID
	/// @return true/false false if dsOOIId is not a valid OOIId
	///
	bool SetObjectOfInspectionID(const SDICOS::DcsLongString& dsOOIId);

	///
	/// Utility method to set the Scan Instance UID (0x0020, 0x000D)
	/// @param dsScanInstanceUID Scan Instance UID
	/// @return true/faqlse false if dsScanInstanceUID is not a valid Scan Instance UID
	///
	bool SetScanInstanceUID(const SDICOS::DcsUniqueIdentifier& dsScanInstanceUID);

	///
	/// Utility method to set the Scan Description (0x0008,0x1030)
	/// @param dsScanDescription Scan Description attribute
	/// @return true/false false if dsScanDescription is not valid
	///
	bool SetScanDescription(const SDICOS::DcsLongString& dsScanDescription);

	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeString &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeString &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeSignedInt16Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeSignedInt16Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeUnsignedInt16Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeUnsignedInt16Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeSignedInt32Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeSignedInt32Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeUnsignedInt32Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeUnsignedInt32Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeSignedInt64Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeSignedInt64Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeUnsignedInt64Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeUnsignedInt64Bit &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeFloat &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeFloat &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeDouble &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeDouble &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeTag &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeTag &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeOther &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeOther &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeSequence &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeSequence &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributeUnknown &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributeUnknown &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePixelData &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePixelData32Bit &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePixelData64Bit &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePixelData32BitFloat &attribPixelData)const;

	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeString> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeString> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt16Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt16Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt16Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt16Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt32Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt32Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt32Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt32Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt64Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt64Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt64Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt64Bit> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeFloat> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeFloat> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeDouble> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeDouble> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeTag> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeTag> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeOther> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeOther> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSequence> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSequence> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnknown> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnknown> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	///
	/// Get pixel data (8-16bit)
	///
	bool FindAttribute(AttributePointer<AttributePixelData> &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData32Bit> &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData64Bit> &attribPixelData)const;
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData32BitFloat> &attribPixelData)const;

	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeString> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeString> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt16Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt16Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt16Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt16Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt32Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt32Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt32Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt32Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSignedInt64Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSignedInt64Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnsignedInt64Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnsignedInt64Bit> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeFloat> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeFloat> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeDouble> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeDouble> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeTag> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeTag> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeOther> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeOther> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeSequence> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeSequence> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Find an attribute. If the attribute is not found or is of a differing VR, the function will return false
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeUnknown> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeUnknown> &attribute, const bool bAllocateIfNotFound = false, const bool bSearchRootLevelIfNotFound = false);
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData> &attribPixelData, const bool bAllocateIfNotFound);
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData32Bit> &attribPixelData, const bool bAllocateIfNotFound);
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData64Bit> &attribPixelData, const bool bAllocateIfNotFound);
	///
	/// Get pixel data
	///
	bool FindAttribute(AttributePointer<AttributePixelData32BitFloat> &attribPixelData, const bool bAllocateIfNotFound);

	///
	/// Find an attribute
	///
	bool FindAttribute(const S_UINT16 nGroup, const S_UINT16 nElement, AttributePointer<AttributeCommon> &attribute, const bool bSearchRootLevelIfNotFound = false)const;
	bool FindAttribute(const Tag &tag, AttributePointer<AttributeCommon> &attribute, const bool bSearchRootLevelIfNotFound = false)const;

	///
	/// Get the Parent level AttributeManager if one exists
	///
	const AttributeManager* GetParent()const;

	///
	/// Find and group overlay plane attributes
	/// @return Returns true if overlay planes are found
	///
	bool FindOverlayPlanes(LinkedList<OverlayPlane> &listPlanes)const;

	///
	/// Returns true if overlay planes exist
	///
	bool HasOverlayPlanes()const;

	///
	/// Enable/Disable using references
	///
	bool EnableReferences(const bool bEnable);
	///
	/// Returns true if manager allow reference attributes
	///
	bool AllowsReferences()const;
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributePixelData &attrPixelData);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributePixelData32Bit &attrPixelData);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributePixelData64Bit &attrPixelData);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributePixelData32BitFloat &attrPixelData);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeString &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeOther &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeUnsignedInt16Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeSignedInt16Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeUnsignedInt32Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeSignedInt32Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeUnsignedInt64Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeSignedInt64Bit &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeFloat &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeDouble &attr);
	///
	/// Store a reference to an attribute
	/// Attribute manager does not delete the attribute. The reference must be removed when the 
	/// original attribute is deleted.
	///
	bool SetReference(AttributeTag &attr);
	///
	/// Remove a reference
	///
	bool RemoveReference(const Tag& tag);
	///
	/// Remove all references
	///
	bool RemoveAllReferences();

	/// A flag to indicate if Module-Level API classes can transfer data ownership out of this object.
	/// Default: Does not allow transfer
	/// Flag does not change by calling FreeMemory()
	void AllowMovingData(const bool bAllow);
	/// @see AllowMovingData
	bool CanMoveData()const;

	//////////////////////////////////////////////
	//  Read/Write

	///
	/// Reads meta preamble, meta information, and all attributes from file
	///
	bool Read(IFile &file, ErrorLog &errorlog);

	///
	/// Reads meta preamble, meta information, and all attributes from file. Optical drive flag 
	/// parameter improves efficiency when reading from optical discs
	///
	bool Read(const Filename &filename, ErrorLog &errorlog, const bool bFromOpticalDrive = false);

	///
	/// Write preamble, meta information, and all to file
	///
	bool Write(IFile &file, ErrorLog &errorlog);

	///
	/// Write preamble, meta information, and all to file. File extension must be set to ".dcs".
	///
	bool Write(const Filename &filename, ErrorLog &errorlog);

	///
	/// Only writes the meta information and preamble (Sets file endian to match transfer syntax)
	///
	bool WriteMetaInfo(IFile &file, ErrorLog &errorlog);

	///
	/// Only reads the meta information and preamble (Sets file endian to match transfer syntax)
	///
	bool ReadMetaInfo(IFile &file, ErrorLog &errorlog);

	///
	/// Write only the data set (Skips meta info and preamble, does not set file endian to match transfer syntax)
	///
	bool WriteDataSet(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	///
	/// Write all attributes (Skips preamble, does not set file endian to match transfer syntax)
	///
	bool WriteAttributes(IFile &file, ErrorLog &errorlog, const bool bExplicit)const;

	///
	/// Reads all attributes until end of file is reached (Does not read preamble, does not set file endian to match transfer syntax)
	///
	bool ReadAttributes(IFile &file, ErrorLog &errorlog, const bool bExplicit);

	///
	/// Reads all attributes until the pixel data is reached (Does not read preamble, does not set file endian to match transfer syntax)
	///
	bool ReadAttributesUpToPixelData(IFile &file, ErrorLog &errorlog, const bool bExplicit);

	///
	/// Reads all attributes up to and including the specified group (Does not read preamble, does not set file endian to match transfer syntax)
	///
	bool ReadAttributesUpTo(const Tag &tag, IFile &file, ErrorLog &errorlog, const bool bExplicit);

	///
	/// Read a single sequence item. Sequence item tag (0xFFFE, 0xE000) and length already read before calling this function.
	///
	/// @param file File to read from
	/// @param errorlog Report errors in this ErrorLog
	/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
	/// @param attributemanager Attribute manager to lookup data and dependencies.
	/// @param nSizeOfObjectInBytes Size of sequence item. Set to 0xFFFFFFFF to search for delimiter. Reads delimiter tag (0xFFFE, 0xE00D) and 4 bytes for its length.
	/// @return true/false
	///
	virtual bool ReadSingleSequenceItem(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager, const S_UINT32 nSizeOfObjectInBytes);
	//////////////////////////////////////////////

	/// Send data over TCP/IP connection. Handles opening and closing a socket connection and starting 
	/// and ending a DICOS session.
	/// @param nPort Host port
	/// @param dsIP Host IP address
	/// @param aeSrcAppName Name of source application (i.e. Name of application calling this function)
	/// @param aeDstAppName Name of destination application
	/// @param errorlog Error log
	/// @param dsUserID User ID. Leave empty if not used.
	/// @param dsPasscode Passcode. If used, user ID must be set.
	bool SendOverNetwork(const S_INT32 nPort, const DcsString &dsIP, const DcsApplicationEntity &aeSrcAppName, 
						const DcsApplicationEntity &aeDstAppName, ErrorLog &errorlog, 
						const DcsString &dsUserID = DcsString(), const DcsString dsPasscode = DcsString());

	/// Send data over TCP/IP connection. The passed in client must already be connected to a host.
	/// Handles Starting and ending a DICOS session if a session is not already in progress.
	/// @param dclient Client already connected to host.
	/// @param errorlog Error log
	bool SendOverNetwork(Network::DcsClient &dclient, ErrorLog &errorlog);

	///
	/// Check if attribute manager contains all the required attributes for the meta information
	///
	bool ValidateMetaInfo(ErrorLog &errorlog)const;

	///
	/// Compare if both managers contain attributes with the same tags, VR, and VM. Comparison includes comparing nested sequences. Does not compare values stored within the attributes.
	///
	bool CompareAttributeList(const AttributeManager &attributemanager)const;

	///
	/// Get the number of tags. Has option to expand all sequences to include the sequence object tags.
	///
	/// @param bIncludeExpandedSquences true = Include tags within sequences, which includes the sequence object header (0xFFFE, 0xE000) and delimiter (0xFFFE, 0xE00D) tags and the sequence delimiter tag (0xFFFE, 0xE0DD)
	/// @param nFilter	Apply this filter to the attributes.
	/// @return Number of tags
	///
	S_UINT64 GetNumberOfTags(const bool bIncludeExpandedSquences, const SEARCHEDATTRIB nFilter = enumAll)const;

	///
	/// Provides basic attribute info
	///
	struct AttributeInfo
	{
		Tag										m_tag;		///< Attribute tag
		DcsString								m_strVR;	///< Attribute VR
		AttributePointer<const AttributeCommon>	m_attptr;	///< Pointer to base class
	};

	typedef LinkedList<const AttributeInfo> TagList;

	///
	/// Get list of all tags in manager
	///
	/// @param listTags Returned list of tags in manager
	/// @param bExpandSquences true = Include sequence objects with the encapsulating header (0xFFFE, 0xE000) and delimiter (0xFFFE, 0xE00D) tags and the end of the sequence with the sequence delimiter tag (0xFFFE, 0xE0DD)
	///
	bool GetTagListing(TagList &listTags, const bool bExpandSquences)const;

	///
	/// Returns false indicating this is not a nested attribute manager
	///
	virtual bool IsNested()const;

	///
	/// Returns the transfer syntax
	///
	DcsString GetTransferSyntax()const;

	///
	/// Deletes all private attributes
	///
	void DeletePrivateAttributes();

	///
	///	Delete a range of tags using group and element prefixes.
	///	Ex. To remove all (60xx, xxxx): nGroupPrefix = 0x6000, nGroupMask = 0xFF00, nElementPrefix = 0, nElementMask = 0
	/// Ex. To remove all (60xx, 3000): nGroupPrefix = 0x6000, nGroupMask = 0xFF00, nElementPrefix = 0x3000, nElementMask = 0xFFFF
	///
	/// @param nGroupPrefix Prefix for group
	/// @param nGroupMask Group mask to match prefix range or exact group
	/// @param nElementPrefix Prefix for element
	/// @param nElementMask Element mask to match prefix range or exact element
	/// @param bRemovePrivate Remove private tags
	/// @param bSearchSequences Search sequences
	void DeleteGroup(const S_UINT16 nGroupPrefix, const S_UINT16 nGroupMask, 
				const S_UINT16 nElementPrefix = 0, const S_UINT16 nElementMask = 0, const bool bRemovePrivate = true, const bool bSearchSequences = true);

	///
	/// Check if the transfer syntax is supported for writing
	///
	/// @param strTransferSyntax transfer syntax to check
	///
	static bool IsTransferSyntaxSupportedForWriting(const DcsString &strTransferSyntax);

	///
	/// Check if the transfer syntax is supported for reading
	///
	/// @param strTransferSyntax transfer syntax to check
	///
	static bool IsTransferSyntaxSupportedForReading(const DcsString &strTransferSyntax);

	///
	/// Check if the transfer syntax uses implicit VR
	///
	/// @param strTransferSyntax transfer syntax to check
	///
	static bool IsTransferSyntaxImplicitVR(const DcsString &strTransferSyntax);

	///
	/// Check if the transfer syntax uses little endian
	///
	/// @param strTransferSyntax transfer syntax to check
	///
	static bool IsTransferSyntaxLittleEndian(const DcsString &strTransferSyntax);

	/// Enumerations for when reading a file's meta info
	/// succeeds or fails
	typedef enum
	{
		enumNoMetaErrors,					///< No errors reading meta info

		enumPassedReadingMetaInfo,			///< The file is identified as a DICOS or DICOM file and 
											///< contains properly formatted attributes
		enumFailedReadingMetaInfoIsDICOS,	///< The file is a DICOS or DICOM file, but is missing part of the header
											///< or encountered an incorrectly formatted attribute
		enumMissingMetaInfo,				///< The file does not have the meta info

		enumFailedMetaInfoValidation,		///< Meta info failed validating specification requirements, but 
											///< has read in attributes in the correct format
	}METAHEADERLOG;

	///
	/// Returns the meta header log enumeration. Call after Read() or ReadMetaInfo()
	///
	METAHEADERLOG	GetMetaHeaderLog()const;

	///
	/// Returns true if all attributes are empty
	///
	bool AreAllAttributesEmpty()const;
protected:

	class ImplAttributeManager;
	ImplAttributeManager	*m_pImplAttributeManager; ///< Internal implementation
};
///////////////////////////////////////////////////

///////////////////////////////////////////////////
///  Attribute with VR = SQ
class AttributeSequence : public AttributeCommon
{
public:
	///
	/// Initialize with default values
	///
	AttributeSequence();
	///
	/// Initialize with an AttributeSequence
	///
	AttributeSequence(const AttributeSequence &attribute);
	///
	/// Destructor
	///
	virtual ~AttributeSequence();

	///
	/// Delete all items from the sequence
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	AttributeSequence& operator=(const AttributeSequence &attribute);
	///
	/// Comparison operator
	///
	bool operator==(const AttributeSequence &attribute)const;
	///
	/// Comparison operator
	///
	bool operator!=(const AttributeSequence &attribute)const;

	using AttributeCommon::Read;
	using AttributeCommon::Write;

	//////////////////////////////////////////////
	///  Read/Write
	///
	/// Write to file. Writes as sequence of undefined length, which ends with the tag (0xFFFE, 0xE0DD) followed by a 4 byte length of 0x00000000
	///
	bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &manager)const;
	///
	/// Read from file
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &manager);

	///
	/// Read from file. Skips AttributeCommon::Read and gets tag and VR from attribHeader
	///
	bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeHeader &attribHeader, const AttributeManager &manager);
	//////////////////////////////////////////////

	/// Each sequence item can contain any combination of attributes
	class SequenceItem : public AttributeManager
	{
	public:
		///
		/// Initialize with default values
		///
		SequenceItem();
		///
		/// Initialize with a SequenceItem
		///
		SequenceItem(const SequenceItem &attribute);
		///
		/// Initialize with default values and set a parent manager (Used with nested sequences)
		///
		SequenceItem(const AttributeManager &mgrParent);
		///
		/// Destructor
		///
		virtual ~SequenceItem();

		///
		/// Copy operator
		///
		SequenceItem& operator=(const SequenceItem &attribute);
		///
		/// Copy operator for a base class input
		///
		SequenceItem& operator=(const AttributeManager &manager);
		///
		/// Comparison operator
		///
		bool operator==(const SequenceItem &attribute)const;
		///
		/// Comparison operator
		///
		bool operator!=(const SequenceItem &attribute)const;

		//////////////////////////////////////////////
		//  Read/Write
		// Sequence items start with the tag (0xFFFE, 0xE000), followed by a 4 byte length
		// Sequence items with undefined length (i.e. length = 0xFFFFFFFF), end with the delimiter tag (0xFFFE, 0xE00D), followed by a 4 byte length of 0x00000000

		///
		/// Write to file. Writes as item with undefined length, which ends with the delimiter tag (0xFFFE, 0xE00D) followed by a 4 byte length of 0x00000000
		///
		bool Write(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &manager)const;
		///
		/// Read from file
		///
		bool Read(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &manager);
		//////////////////////////////////////////////
		
		///
		/// Read a single sequence item. Sequence item tag (0xFFFE, 0xE000) and length already read before calling this function.
		///
		/// @param file File to read from
		/// @param errorlog Report errors in this ErrorLog
		/// @param bExplicit VR is explicitly encoded instead of determined from Tag.
		/// @param attributemanager Attribute manager to lookup data and dependencies.
		/// @param nSizeOfObjectInBytes Size of sequence item. Set to 0xFFFFFFFF to search for delimiter. Reads delimiter tag (0xFFFE, 0xE00D) and 4 bytes for its length.
		/// @return true/false
		///
		virtual bool ReadSingleSequenceItem(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &attributemanager, const S_UINT32 nSizeOfObjectInBytes);

		///
		/// Return true indicating this is a nested attribute manager
		///
		virtual bool IsNested()const;

		///
		/// Returns tag (0xFFFE, 0xE000)
		///
		static Tag GetHeaderTag();

		///
		/// Returns tag (0xFFFE, 0xE00D)
		///
		static Tag GetDelimiterTag();

	protected:
		class ImplSequenceItem;
		ImplSequenceItem*m_pImplSequenceItem; ///< Internal implementation
	};

	///
	/// Append sequence item
	///
	/// @param sequenceitem sequence item
	///
	bool AppendItem(const SequenceItem &sequenceitem);

	///
	/// Delete an item from the sequence
	///
	///	@param nIndex Offset from GetFirstItem()
	///
	bool DeleteItem(const S_UINT64 nIndex);

	/// Set the number of items in the sequence. Creates the specified number of empty items in the sequence. Deletes existing items.
	///
	/// @param nNumItems Number of items to create
	/// @param pmanagerParent Set the parent attribute manager of the sequence. Set to S_NULL for no parent manager.
	bool SetNumberOfItems(const S_UINT64 nNumItems, AttributeManager *pmanagerParent);

	///
	/// Delete an item from the sequence
	///
	/// @param it Iterator of item to delete
	///
	bool DeleteItem(LinkedList<SequenceItem*>::const_iterator &it);

	typedef LinkedList<SequenceItem*>::const_iterator ConstSequenceIterator; ///< Typedef for constant sequence item iterator
	typedef LinkedList<SequenceItem*>::iterator SequenceIterator; ///< Typedef for sequence item iterator

	///
	/// Get iterator to first sequence item
	///
	/// @return iterator to first sequence
	///
	SequenceIterator GetFirstItem();

	///
	/// Get iterator to first sequence item
	///
	/// @return iterator to first sequence
	///
	ConstSequenceIterator GetFirstItem()const;

	///
	/// Returns a null iterator
	///
	SequenceIterator GetEndItem();

	///
	/// Returns a null iterator
	///
	ConstSequenceIterator GetEndItem()const;

	///
	/// Bracket operator for accessing sequence items
	///
	/// @param nIndex Index of sequence item to get
	///
	SequenceItem& operator[](S_UINT64 nIndex);

	///
	/// Bracket operator for accessing sequence items
	///
	/// @param nIndex Index of sequence item to get
	///
	const SequenceItem& operator[](S_UINT64 nIndex)const;

	///
	/// Returns the number of sequence items
	///
	S_UINT64 GetNumberOfItems()const;

	///
	/// Verify that the sequence is valid: All sequence items must have the same number of attributes all with equal tags, VR, and VM
	///
	/// @return true/false
	///
	bool IsValid()const;

	///
	/// Get delimiter tag (0xFFFE, 0xE0DD)
	///
	static Tag GetDelimiterTag();

	///
	/// Get Value Representation
	///
	virtual DcsString GetVR()const;

	///
	/// Get Value Multiplicity
	///
	virtual S_UINT32 GetVM()const;

	///
	/// Get the Attribute's Data Size in bytes
	///
	virtual S_UINT64 GetSizeInBytes()const;

protected:
	class ImplAttributeSequence;
	ImplAttributeSequence	*m_pImplAttributeSequence; ///< Internal implementation

	///
	/// Internal read function. Called by all read functions
	///
	bool Read_internal(IFile &file, ErrorLog &errorlog, const bool bExplicit, const AttributeManager &manager);
};
///////////////////////////////////////////////////

///
/// \typedef AttributeManager::AttributePointer<AttributeSequence> AttributeSequencePointer
///
typedef AttributeManager::AttributePointer<AttributeSequence> AttributeSequencePointer;

///
/// \typedef AttributeManager::AttributePointer<AttributeString> AttributeStringPointer
///
typedef AttributeManager::AttributePointer<AttributeString> AttributeStringPointer;

/// \typedef AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> AttributeUnsignedInt16BitPointer
typedef AttributeManager::AttributePointer<AttributeUnsignedInt16Bit> AttributeUnsignedInt16BitPointer;
/// \typedef AttributeManager::AttributePointer<AttributeSignedInt16Bit> AttributeSignedInt16BitPointer
typedef AttributeManager::AttributePointer<AttributeSignedInt16Bit> AttributeSignedInt16BitPointer;

/// \typedef AttributeManager::AttributePointer<AttributeUnsignedInt32Bit> AttributeUnsignedInt32BitPointer
typedef AttributeManager::AttributePointer<AttributeUnsignedInt32Bit> AttributeUnsignedInt32BitPointer;
/// \typedef AttributeManager::AttributePointer<AttributeSignedInt32Bit> AttributeSignedInt32BitPointer
typedef AttributeManager::AttributePointer<AttributeSignedInt32Bit> AttributeSignedInt32BitPointer;

/// \typedef AttributeManager::AttributePointer<AttributeUnsignedInt64Bit> AttributeUnsignedInt64BitPointer
typedef AttributeManager::AttributePointer<AttributeUnsignedInt64Bit> AttributeUnsignedInt64BitPointer;
/// \typedef AttributeManager::AttributePointer<AttributeSignedInt64Bit> AttributeSignedInt64BitPointer
typedef AttributeManager::AttributePointer<AttributeSignedInt64Bit> AttributeSignedInt64BitPointer;

///
/// \typedef AttributeManager::AttributePointer<AttributeFloat> AttributeFloatPointer
///
typedef AttributeManager::AttributePointer<AttributeFloat> AttributeFloatPointer;

///
/// \typedef AttributeManager::AttributePointer<AttributeCommon> AttributeCommonPointer
///
typedef AttributeManager::AttributePointer<AttributeCommon> AttributeCommonPointer;

///
/// \typedef AttributeManager::AttributePointer<AttributeDouble> AttributeDoublePointer
///
typedef AttributeManager::AttributePointer<AttributeDouble> AttributeDoublePointer;

///
/// \typedef AttributeManager::AttributePointer<AttributeOther> AttributeOtherPointer
///
typedef AttributeManager::AttributePointer<AttributeOther> AttributeOtherPointer;

///
/// \typedef AttributeManager::AttributePointer<AttributePixelData> AttributePixelDataPointer
///
typedef AttributeManager::AttributePointer<AttributePixelData> AttributePixelDataPointer;

///
/// \typedef AttributeManager::AttributePointer<AttributePixelData32Bit> AttributePixelData32Pointer
///
typedef AttributeManager::AttributePointer<AttributePixelData32Bit> AttributePixelData32Pointer;

///
/// \typedef AttributeManager::AttributePointer<AttributePixelData64Bit> AttributePixelData64Pointer
///
typedef AttributeManager::AttributePointer<AttributePixelData64Bit> AttributePixelData64Pointer;

///
/// \typedef AttributeManager::AttributePointer<AttributePixelData32BitFloat> AttributePixelData32FloatPointer
///
typedef AttributeManager::AttributePointer<AttributePixelData32BitFloat> AttributePixelData32FloatPointer;


}//namespace SDICOS

#endif
