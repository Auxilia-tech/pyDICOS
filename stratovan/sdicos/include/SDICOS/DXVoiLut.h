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
#ifndef _STRATOVAN_DICOS_DX_VOI_LUT_H_
#define _STRATOVAN_DICOS_DX_VOI_LUT_H_

#include "SDICOS/VoiLut.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class DXVoiLut
/// \brief Implements DX specialization of the VOI LUT Module
/// SPECREF V03 Section 8.2.2.2, Table 35
/// SPECREF V03 Section 8.2.2.2.1.4
///
class DXVoiLut : public VoiLut
{
public:
	/// Initialize VoiLut to default values
	DXVoiLut();

	/// Copy a VoiLut
	DXVoiLut(const DXVoiLut &voilut);

	/// Destructor deletes internal implementation
	virtual ~DXVoiLut();

	/// Reset to default values
	void FreeMemory();

	/// Assignment operator
	DXVoiLut& operator=(const DXVoiLut &voilut);

	/// Comparison operator
	bool operator==(const DXVoiLut &voilut)const;
	/// Comparison operator
	bool operator!=(const DXVoiLut &voilut)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if some attributes failed IsValid()
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// \class DXVoiLutItem
	/// Data for a VOI LUT Sequence, Tag (0028, 3010)
	/// SPECREF V03 Section 8.2.2.2, Table 35
	/// - LUT Sequence Elements
	///   - LUT Descriptor (0028, 3002)
	///   - LUT Explanation (0028, 3003)
	///   - LUT Data (0028, 3006)
	///
	class DXVoiLutItem
	{
	public:
		/// Create an empty VoiLutItem
		DXVoiLutItem();

		/// Copy a VoiLutItem
		DXVoiLutItem(const DXVoiLutItem &item);

		/// Destructor deletes internal implementation
		~DXVoiLutItem();

		/// Assignment Operator
		DXVoiLutItem& operator=(const DXVoiLutItem &item);

		/// Comparison Operator
		bool operator==(const DXVoiLutItem &item)const;
		/// Comparison Operator
		bool operator!=(const DXVoiLutItem &item)const;

		/// Check that the LUT Descriptor settings and LUT data size are consistent.
		/// @param attribManager	AttributeManager to look up dependencies.
		/// @param errorlog			ErrorLog for reporting errors.
		/// @return true/false
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		///
		/// Set the LUT Descriptor Attribute : Tag (0028, 3002) using unsigned shorts.
		/// The third value in the LUT Descriptor Attribute, indicating the
		/// number of bit for each entry in the LUT Data defaults to 16 bits.
		///
		/// @param nNumEntries 			Number of LUT Entries. 0 means 2^16 Lut Entries.
		///	@param nFirstValueMapped 	First Input Value Mapped. Can be signed or unsigned.
		/// @param nBitsPerEntry		Bits per LUT Entry. Max is 16.
		///	@return true/false
		///
		bool SetLutDescriptor(const S_UINT16 nNumEntries, const S_UINT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);

		///
		/// Set the LUT Descriptor Attribute using a signed value for
		/// the first input value mapped to the output range.
		/// @see SetLutDescriptor(const S_UINT16, const S_UINT16, const S_UINT16)
		///
		bool SetLutDescriptor(const S_UINT16 nNumEntries, const S_INT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);

		/// Get the Number of entries in the LUT.
		/// @return	NumEntries set by SetLutDescriptor() or 2^16 if it is 0.
		S_UINT32 GetLutNumEntries() const;

		///
		/// Get LUT Descriptor Information
		/// LUT Descriptor (0028, 3002) is implied by the function signature.
		///
		/// @param nNumEntries 			Number of LUT Entries. Always interpreted as unsigned.
		///	@param nFirstValueMapped 	First Input Value Mapped. Can be signed or unsigned
		/// @param nBitsPerEntry 		Defaults to "16" (can be 8 or 16). Always unsigned.
		/// @return true/false
		///
		bool GetLutDescriptor(S_UINT16 &nNumEntries, S_UINT16 &nFirstValueMapped, S_UINT16 &nBitsPerEntry)const;

		///
		/// Get LUT Descriptor Information as signed integers
		/// @see GetLutDescriptor(S_UINT16&, S_UINT16&, S_UINT16&)
		///
		bool GetLutDescriptor(S_UINT16 &nNumEntries, S_INT16 &nFirstValueMapped, S_UINT16 &nBitsPerEntry)const;

		///
		/// Set the LUT Explanation : Tag (0028, 3003) VR = LO [optional]
		/// Trailing spaces in the explanation string will be removed.
		///
		/// @param strExplanation Freeform text Explanation of the LUT's meaning
		/// @return true/false	false if strExplanation is not a valid string with VR=LO
		///
		bool SetLutExplanation(const DcsLongString &strExplanation);

		///
		/// Get the LUT Explanation : Tag (0028, 3003)
		/// @return Explanation string
		///
		DcsString GetLutExplanation()const;
		
		/// Delete the Lut Explanation attribute
		bool DeleteLutExplanation();

		///
		/// Set LUT Data : Tag (0028, 3006) VR = OW [required]
		/// VR = OW is not used for writing
		/// @param arrayData Array of unsigned short ints
		/// @return true/false
		///
		bool SetLutData(const Array1D<S_UINT16> &arrayData);

		/// @see SetLutData(const Array1D<S_UINT16>)
		bool SetLutData(const Array1D<S_INT16> &arrayData);

		///
		/// Get LUT Data as unsigned short ints
		/// @param arrayData Array of unsigned short ints
		/// @return true/false
		///
		bool GetLutData(Array1D<S_UINT16> &arrayData)const;

		/// @see GetLutData(Array1D<S_UINT16> &)
		bool GetLutData(Array1D<S_INT16> &arrayData)const;

		/// Maximum number of entries in a LUT is 2^16 which is encoded as 0.
		static S_UINT32 GetMaxLutEntries() { return (1 << 16); }

	protected:
		friend class DXVoiLut;

		class ImplDXVoiLutItem;
		ImplDXVoiLutItem	*m_pImplDXVoiLutItem; ///< Internal implementation

		ImplDXVoiLutItem* GetImpl();
		const ImplDXVoiLutItem *GetImpl() const;
	};

	///
	/// Set VOI LUT Sequence : Tag (0028, 3010), VR = SQ [required if Window Center (0028, 1050) is not present]
	/// @param arrayVoiLut Array of DXVoiLutItem objects representing VOI LUT Sequences
	/// @return true/false
	///
	virtual bool SetVoiLut(const Array1D<DXVoiLutItem> &arrayVoiLut);

	///
	/// Get VOI LUT Sequence : Tag (0028, 3010)
	/// @param arrayVoiLut Array to store DXVoiLutItem
	/// @return true/false
	///
	virtual bool GetVoiLut(Array1D<DXVoiLutItem> &arrayVoiLut)const;

private:
	class ImplDXVoiLut;
	ImplDXVoiLut	*m_pDXImplVoiLut; ///< Internal implementation

	ImplDXVoiLut* GetImpl();
	const ImplDXVoiLut * GetImpl() const;

	/// Disabled
	virtual bool SetVoiLut(const Array1D<VoiLutItem> &arrayVoiLut);
	/// Disabled
	virtual bool GetVoiLut(Array1D<VoiLutItem> &arrayVoiLut)const;
};

}//namespace DXTypes
}//namespace SDICOS

#endif
