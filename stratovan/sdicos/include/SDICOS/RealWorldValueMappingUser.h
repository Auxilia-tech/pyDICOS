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
#ifndef _STRATOVAN_DICOS_REAL_WORLD_VALUE_MAPPING_USER_H_
#define _STRATOVAN_DICOS_REAL_WORLD_VALUE_MAPPING_USER_H_

#include "SDICOS/MeasurementUnitsCodeSequence.h"
#include "SDICOS/RealWorldValueMapping.h"

namespace SDICOS
{
	///
	/// \class RealWorldValueMappingSequenceUser
	/// \brief World Value Mapping
	/// SPECREF V03 Section 14.14.9, Table 119
	///
	class RealWorldValueMappingSequenceUser
	{
	public:
		/// Constructor
		RealWorldValueMappingSequenceUser();
		/// Copy constructor
		RealWorldValueMappingSequenceUser(const RealWorldValueMappingSequenceUser& rwvm);
		/// Destructor
		virtual ~RealWorldValueMappingSequenceUser();

		/// Is the sequence set to valid values
		/// @return true/false;
		bool IsValid() const;

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		RealWorldValueMappingSequenceUser& operator=(const RealWorldValueMappingSequenceUser& rwvm);
		/// Comparison operator
		bool operator==(const RealWorldValueMappingSequenceUser& rwvm)const;
		/// Comparison operator
		bool operator!=(const RealWorldValueMappingSequenceUser& rwvm)const;

		/// Read from AitPlaneOrientationUser Module
		bool Read(const RealWorldValueMappingSequence& rhs, ErrorLog& el);

		/// Write to AitPlaneOrientationUser Module
		bool Write(RealWorldValueMappingSequence& lhs, ErrorLog& el) const;

		/// Real World Value Mapping Sequence : Tag (0040, 9096), VR = SQ [optional]
		bool SetRealWorldValueMapping(const Array1D<RealWorldValueMappingSequence::RealWorldValueItem>& arrayRealWorldValues);
		/// @see SetRealWorldValueMapping
		bool GetRealWorldValueMapping(Array1D<RealWorldValueMappingSequence::RealWorldValueItem>& arrayRealWorldValues)const;
		/// @see SetRealWorldValueMapping
		Array1D<RealWorldValueMappingSequence::RealWorldValueItem>& GetRealWorldValueMapping();
		/// @see SetRealWorldValueMapping
		const Array1D<RealWorldValueMappingSequence::RealWorldValueItem>& GetRealWorldValueMapping()const;

	protected:
		class RealWorldValueMappingSequenceUserImpl;
		RealWorldValueMappingSequenceUserImpl* m_pRealWorldValueMappingSequenceUserImpl;
	};

}//namespace SDICOS

#endif
