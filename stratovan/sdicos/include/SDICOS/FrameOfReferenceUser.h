//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_FRAME_OF_REFERENCE_USER_H_
#define _STRATOVAN_DICOS_FRAME_OF_REFERENCE_USER_H_

#include "SDICOS/FrameOfReference.h"
#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

	class FrameOfReferenceUser
	{
	public:
		/// Constructor
		FrameOfReferenceUser();

		/// Destructor
		~FrameOfReferenceUser();

		/// Copy Constructor
		FrameOfReferenceUser(const FrameOfReferenceUser& FrameOfReferenceUser);

		/// Reset to default values
		void FreeMemory();

		/// Assignment operator
		FrameOfReferenceUser& operator=(const FrameOfReferenceUser& FrameOfReferenceUser);

		/// Comparison operator
		bool operator==(const FrameOfReferenceUser &FrameOfReferenceUser)const;
		bool operator!=(const FrameOfReferenceUser &FrameOfReferenceUser)const;

		/// Read FrameOfReferenceUser from the FrameOfReference object
		/// @param frameOfReference Object to read from
		/// @param el Error Log
		/// @return true/false
		bool Read(const FrameOfReference& frameOfReference, ErrorLog& el);

		/// Write FrameOfReference
		/// @param frameOfReference Object to write into
		/// @param el Error log
		/// @return true/false
		bool Write(FrameOfReference& frameOfReference, ErrorLog& el) const;

		/// Set Frame Of Reference UID
		/// @param strFrameOfReferenceUID Frame Of Reference UID [required]
		/// @return true/false false if strFrameOfReferenceUID is not valid
		bool SetFrameOfReferenceUID(const DcsUniqueIdentifier& strFrameOfReferenceUID);

		/// Generate a new Frame of Reference UID
		/// @return true/false false if unable to generate new FrameOfReferenceUID
		bool GenerateFrameOfReferenceUID();

		/// @see SetFrameOfReferenceUID
		/// @return Frame of Reference UID or an empty string if their is none.
		DcsUniqueIdentifier GetFrameOfReferenceUID()const;

		/// Set Position Reference Indicator
		/// @param strPositionReferenceIndicator Position Reference Indicator [required, can be NULL]
		/// @return true/false false if strPositionReferenceIndicator is not valid
		bool SetPositionReferenceIndicator(const DcsLongString& strPositionReferenceIndicator);

		/// @see SetPositionReferenceIndicator
		/// @return Position Reference Indicator or an empty string if their is none.
		DcsString GetPositionReferenceIndicator()const;

	private:
		class ImplFrameOfReferenceUser;
		ImplFrameOfReferenceUser* m_pImplFrameOfReferenceUser; ///< Internal implementation

		ImplFrameOfReferenceUser* GetImpl();
		const ImplFrameOfReferenceUser* GetImpl() const;

	};
}//namespace SDICOS

#endif
