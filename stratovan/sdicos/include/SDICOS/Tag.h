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
#ifndef _STRATOVAN_DICOS_TAG_H_
#define _STRATOVAN_DICOS_TAG_H_

#include <ostream>

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/IFile.h"

namespace SDICOS
{

/// 
/// \class Tag
/// \brief Base Object for DICOS Tags
/// \date 02-12-2014
///
/// The SDICOS::Tag class is the base object for DICOS Tags 
/// and consists of a Group identifier and an Element identifier.
///

class Tag
{
public: 
	///
	/// Default Constructor set the Group and Element to 0xFFFF
	///
	Tag(); ///< Defaults to (0xFFFF, 0xFFFF)

	/// 
	/// Construct a DICOS Tag with a group and element identifier
	/// e.g. Tag(4010, 1047) is the DICOS Tag for OOI Owner Sequence.
	///
	/// @param nGroup DICOS Tag Group Identifier 
	/// @param nElement DICOS Tag Element Identifier
	/// 
	Tag(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	///  Copy Constructor
	///
	Tag(const Tag &tag);
 
	/// Destructor
	~Tag();

	/// Reset to default values
	void FreeMemory();

	/// 
	/// Assignment operator
	///
	Tag& operator=(const Tag& tag);

	/// 
	/// Comparison operator 
	///
	bool operator==(const Tag& tag)const;

	/// 
	/// Comparison operator 
	///
	bool operator!=(const Tag& tag)const;

	/// Stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const Tag& tag);
	
	///
	/// Set the DICOS Group and Element 
	/// @see Tag()
	/// 
	/// @return true/false
	///
	bool Set(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Get the DICOS group and element
	/// 
	/// @param nGroup an unsigned short in which to store the group
	/// @param nElement an unsigned short in which store the element
	/// @return true/false
	///
	bool Get(S_UINT16 &nGroup, S_UINT16 &nElement)const;

	///
	/// Convert a DICOS Tag (Group, Element)  to a string as "Group Element"
	///
	/// @return DscString
	/// 
	DcsString GetString()const; //! Returns as (Group, Element) as "Group Element"

	///
	/// Returns true if this is a private tag.  Private tags use an odd number for 'group'
	///
	/// @return true/false
	///
	bool IsPrivate()const;

	/// Number of bytes to store data for Tag information on disk.
	static S_UINT32 GetSizeInBytes();

	///
	/// Write tag to file
	///
	bool Write(IFile &file)const;

	///
	/// Read tag from file
	///
	bool Read(IFile &file);

	///
	/// Get the tag's group number
	///
	S_UINT16 GetGroup()const;

	///
	/// Get the tag's element number
	///
	S_UINT16 GetElement()const;

private:
	S_UINT16 m_nGroup;
	S_UINT16 m_nElement;
};

}//namespace SDICOS

#endif
