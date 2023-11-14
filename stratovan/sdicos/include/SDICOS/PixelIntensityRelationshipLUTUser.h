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
#ifndef _STRATOVAN_DICOS_PIXEL_INTENSITY_RELATIONSHIP_LUT_USER_H_
#define _STRATOVAN_DICOS_PIXEL_INTENSITY_RELATIONSHIP_LUT_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/PixelIntensityRelationshipLUT.h"

namespace SDICOS
{
	///
	/// \class PixelIntensityRelationshipLUTInfo
	/// \brief An item in Pixel Intensity Relationship LUT Sequence
	///
	class PixelIntensityRelationshipLUTInfo
	{
	public:
		/// Constructor
		PixelIntensityRelationshipLUTInfo();
		/// Copy constructor
		PixelIntensityRelationshipLUTInfo(const PixelIntensityRelationshipLUTInfo& pir);
		/// Destructor
		~PixelIntensityRelationshipLUTInfo();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		PixelIntensityRelationshipLUTInfo& operator=(const PixelIntensityRelationshipLUTInfo& pir);
		/// Comparison operator
		bool operator==(const PixelIntensityRelationshipLUTInfo& pir)const;
		/// Comparison operator
		bool operator!=(const PixelIntensityRelationshipLUTInfo& pir)const;
		
		/// Read from Module
		/// @param rhs Read from this object
		/// @param el Error log object
		/// @return true/false
		bool Read(const PixelIntensityRelationshipLutSequence::PixelIntensityRelationshipLUT& rhs, ErrorLog& el);

		/// Write to Module
		/// @param lhs Write to this object
		/// @param el Error log object
		/// @return true/false
		bool Write(PixelIntensityRelationshipLutSequence::PixelIntensityRelationshipLUT& lhs, ErrorLog& el);

		/// Return true if LUT data is unsigned
		bool IsLutDataUnsigned()const;
		/// Return true if LUT data is signed
		bool IsLutDataSigned()const;

		/// Return true if first value mapped is unsigned
		bool IsFirstValueMappedUnsigned()const;
		/// Return true if first value mapped is signed
		bool IsFirstValueMappedSigned()const;

		///
		/// First value mapped [value 2 of LUT Descriptor (0028, 3002)].  
		/// Used as base index LUTData[nValue - FirstValueMapped]
		///
		bool SetFirstValueMapped(const S_UINT16 nFirstValueMapped);
		///
		/// First value mapped [value 2 of LUT Descriptor (0028, 3002)].  
		/// Used as base index LUTData[nValue - FirstValueMapped]
		///
		bool SetFirstValueMapped(const S_INT16 nFirstValueMapped);
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_UINT16& nFirstValueMapped)const;
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_INT16& nFirstValueMapped)const;

		/// LUT Data : Tag (0028, 3006), VR = US [required]
		bool SetData(const Array1D<S_UINT16>& arrayData);
		/// LUT Data : Tag (0028, 3006), VR = SS [required]
		bool SetData(const Array1D<S_INT16>& arrayData);
		/// Get unsigned LUT data. Deletes signed data.
		Array1D<S_UINT16>& GetUnsignedData();
		/// Get unsigned LUT data. Deletes unsigned data.
		Array1D<S_INT16>& GetSignedData();
		/// @see SetData
		const Array1D<S_UINT16>& GetUnsignedData()const;
		/// @see SetData
		const Array1D<S_INT16>& GetSignedData()const;

		/// LUT Function : Tag (0028, 9474), VR = CS [required]
		bool SetLutFunction(const PixelIntensityRelationshipLutSequence::PixelIntensityRelationshipLUT::LUT_FUNCTION nFunction);
		/// @see SetLutFunction
		PixelIntensityRelationshipLutSequence::PixelIntensityRelationshipLUT::LUT_FUNCTION GetLutFunction()const;
		/// @see SetLutFunction
		DcsString GetLutFunctionAsString()const;

	private:
		class PixelIntensityRelationshipLUTInfoImpl;
		PixelIntensityRelationshipLUTInfoImpl* m_pPixelIntensityRelationshipLUTInfoImpl;
	};

	/// Array of LUTs for User Level API
	class PixelIntensityRelationshipLUTUser
	{
	public:
		PixelIntensityRelationshipLUTUser();
		PixelIntensityRelationshipLUTUser(const PixelIntensityRelationshipLUTUser& rhs);
		virtual ~PixelIntensityRelationshipLUTUser();

		/// Assignment operator
		PixelIntensityRelationshipLUTUser& operator=(const PixelIntensityRelationshipLUTUser& rhs);

		/// Equality operator
		bool operator==(const PixelIntensityRelationshipLUTUser& rhs) const;
	
		/// Inequality operator
		bool operator!=(const PixelIntensityRelationshipLUTUser& rhs) const;

		void FreeMemory();

		/// Read from PixelIntensityRelationshipLutSequence
		/// @param rhs PixelIntensityRelationshipLutSequence
		/// @param el Error log object
		/// @return true/false
		bool Read(const PixelIntensityRelationshipLutSequence& rhs, ErrorLog& el);

		/// Write to PixelIntensityRelationshipLutSequence
		/// @param lhs PixelIntensityRelationshipLutSequence
		/// @param el Error log object
		/// @return true/false
		bool Write(PixelIntensityRelationshipLutSequence& lhs, ErrorLog& el) const;

		/// Set LUTs
		/// @param arrayPixelIntensityRelationshipLUT Array of LUTs
		/// @return true/false
		bool SetPixelIntensityRelationshipLUT(const Array1D<PixelIntensityRelationshipLUTInfo>& arrayPixelIntensityRelationshipLUT);
		/// @see SetPixelIntensityRelationshipLUT
		bool GetPixelIntensityRelationshipLUT(Array1D<PixelIntensityRelationshipLUTInfo>& arrayPixelIntensityRelationshipLUT)const;
		/// @see SetPixelIntensityRelationshipLUT
		void DeletePixelIntensityRelationshipLUTS();
		/// @see SetPixelIntensityRelationshipLUT
		bool HasPixelIntensityRelationshipLUTS() const;

	private:
		class PixelIntensityRelationshipLUTUserImpl;
		PixelIntensityRelationshipLUTUserImpl* m_pPixelIntensityRelationshipLUTUserImpl;
	};
	
}//namespace SDICOS

#endif
