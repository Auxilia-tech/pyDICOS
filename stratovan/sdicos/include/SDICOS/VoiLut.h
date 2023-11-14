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
#ifndef _STRATOVAN_DICOS_VOI_LUT_H_
#define _STRATOVAN_DICOS_VOI_LUT_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

///
/// \namespace SDICOS
/// Contains all class, methods, enums etc. for Stratovan DICOS implementation
///
namespace SDICOS
{

///
/// \class VoiLut
/// \brief Implements VOI LUT Module
/// \date 02-17-2014
///
/// The SDICOS::VoiLut class implements the VOI LUT Module
/// SPECREF V03 Section 14.2.5, Table 90
///
class VoiLut
{
public:
	/// \typedef Array1D<S_UINT16> UnsignedLUT
	/// LUT transformation described as a piecewise linear function using unsigned shorts.
	typedef Array1D<S_UINT16> UnsignedLUT;
	
	/// \typedef Array1D<S_INT16> SignedLUT
	/// LUT transformation described as a piecewise linear function using signed shorts.
	typedef Array1D<S_INT16> SignedLUT;
	
	/// Initialize VoiLut to default values
	VoiLut();

	/// Copy a VoiLut
	VoiLut(const VoiLut &voilut);

	/// Destructor deletes internal implementation
	virtual ~VoiLut();

	/// Reset to default values
	void FreeMemory();

	/// Assignment operator
	VoiLut& operator=(const VoiLut &voilut);

	/// Comparison operator
	bool operator==(const VoiLut &voilut)const;
	/// Comparison operator
	bool operator!=(const VoiLut &voilut)const;

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
	/// Enumeration for VOI LUT Functions
	/// DICOS Tag (0028, 1056)
	///
	typedef enum
	{
		enumUnknownVoiLutFunction, ///< Unknown LUT Function

		enumLinear,		///< "LINEAR"
		enumSigmoid,	///< "SIGMOID"

		enumDefault = enumLinear, ///< Default to Linear
	}VOI_LUT_FUNCTION;

	///
	/// \class VoiLutItem
	/// Data for a VOI LUT Sequence, Tag (0028, 3010)
	/// SPECREF V03 Section 14.2.5, Table 91
	/// - LUT Sequence Elements
	///   - LUT Descriptor (0028, 3002)
	///   - LUT Explanation (0028, 3003)
	///   - LUT Data (0028, 3006)
	///
	class VoiLutItem 
	{
	public:
		/// Create an empty VoiLutItem
		VoiLutItem();

		/// Copy a VoiLutItem
		VoiLutItem(const VoiLutItem &voilutitem);

		/// Destructor deletes internal implementation
		~VoiLutItem();

		/// Assignment Operator
		VoiLutItem& operator=(const VoiLutItem &voilutitem);

		/// Comparison Operator
		bool operator==(const VoiLutItem &voilutitem)const;
		/// Comparison Operator
		bool operator!=(const VoiLutItem &voilutitem)const;

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

		/// Set first input value mapped to entry 0 of the LUT as an unsigned short
		bool SetFirstValueMapped(const S_UINT16 nFirstValueMapped);
		
		/// Set first input value mapped to entry 0 of the LUT as a signed short
		bool SetFirstValueMapped(const S_INT16 nFirstValueMapped);
		
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_UINT16& firstValueMapped) const;
		
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_INT16& firstValueMapped) const;
		
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
		friend class VoiLut;

		class ImplVoiLutItem;
		ImplVoiLutItem	*m_pImplVoiLutItem; ///< Internal implementation

		ImplVoiLutItem* GetImpl();
		const ImplVoiLutItem *GetImpl() const;
	};

	///
	/// Set VOI LUT Sequence : Tag (0028, 3010), VR = SQ [required if Window Center (0028, 1050) is not present]
	/// @param arrayVoiLut Array of VoiLutItem objects representing VOI LUT Sequences
	/// @return true/false
	///
	virtual bool SetVoiLut(const Array1D<VoiLutItem> &arrayVoiLut);

	///
	/// Get VOI LUT Sequence : Tag (0028, 3010)
	/// @param arrayVoiLut Array to store VoiLutItems
	/// @return true/false
	///
	virtual bool GetVoiLut(Array1D<VoiLutItem> &arrayVoiLut)const;

	/// @see SetVoiLut
	Array1D<VoiLutItem>& GetVoiLut();
	/// @see SetVoiLut
	const Array1D<VoiLutItem>& GetVoiLut()const;

	/// Remove all VOI Lut Sequences from the Module
	bool DeleteVoiLut();

	///
	/// Set Window Center and Width.  Center and Width arrays must be the same size and width >= 1.0f.
	/// \brief Set Window Center and Width.
	/// @param arrayCenter Window Center : Tag (0028, 1050), VR = DS [required if "VOI LUT Sequence" is not set] \n
	///					   i) All values stored in a single tag (Ex. "Center1\Center2")
	/// @param arrayWidth  Window Width : Tag (0028, 1051), VR = DS [required if "VOI LUT Sequence" is not set] \n
	///					   i) All values stored in a single tag (Ex. "Width1\Width2")
	/// @return true/false	false if arrays are not the proper size and value.
	///
	bool SetWindowCenterAndWidth(const Array1D<float> &arrayCenter, const Array1D<float> &arrayWidth);
	/// Set one Window Center and Width
	bool SetWindowCenterAndWidth(const float fCenter, const float fWidth);

	///
	/// Get Window Center and Width. If no window center and width have been set
	/// arrayCenter and arrayWidth are unchanged.
	///
	/// @see SetWindowCenterAndWidth(const Array1D<float> &, const Array1D<float> &)
	/// @return true/false	false if Window Center and Width have not been set.
	bool GetWindowCenterAndWidth(Array1D<float> &arrayCenter, Array1D<float> &arrayWidth)const;
	/// Get one Window Center and Width.  If more than one center and width are available, the first center and width found are returned.
	bool GetWindowCenterAndWidth(float &fCenter, float &fWidth)const;

	/// Delete the Window Center and Width attribute
	bool DeleteWindowCenterAndWidth();

	///
	/// Set Window Center and Width Explanation : Tag (0028, 1055)
	/// This method does not check that the size of the array is equivalent to the size
	/// of the window center and window width.
	/// @param strExplanation Window Center and Width Explanation : Tag (0028, 1055), VR = LO [optional] \n
	///			i) All values stored in a single tag (Ex. "Expl1\Expl2") \n
	///			ii) Array size must be equal to SetWindowCenterAndWidth() parameters
	/// @return true/false	false if DcsLongString objects are invalid
	///
	bool SetWindowCenterAndWidthExplanation(const Array1D<DcsLongString> &strExplanation);

	///
	/// Get Window Center and Width Explanation
	/// @see SetWindowCenterAndWidthExplanation(const Array1D<DcsLongString> &)
	/// @return true/false	false if no explanation has been set.
	///
	bool GetWindowCenterAndWidthExplanation(Array1D<DcsString> &strExplanation)const;

	/// Delete the Window Center and Width Explanation Attribute
	bool DeleteWindowCenterAndWidthExplanation();

	///
	/// Set VOI LUT Function : Tag (0028, 1056)
	/// @param nFunction VOI LUT Function : Tag (0028, 1056), VR = CS [optional] \n
 	///			i) Values: "LINEAR", "SIGMOID" \n
	///			ii) If not provided, default value is "LINEAR"
	/// @return true/false
	///
	bool SetVoiLutFunction(const VOI_LUT_FUNCTION nFunction);

	///
	/// Get Voi Lut Function
	/// @return VOI_LUT_FUNCTION @see VOI_LUT_FUNCTION
	///
	VOI_LUT_FUNCTION GetVoiLutFunction()const;

	///
	/// Get Lut Function as String
	/// @return DscString object
	///
	DcsString GetVoiLutFunctionAsString()const;

	/// Delete the Voi Lut Function Attribute
	bool DeleteVoiLutFunction();

private:
	class ImplVoiLut;
	ImplVoiLut	*m_pImplVoiLut; ///< Internal implementation

	ImplVoiLut* GetImpl();
	const ImplVoiLut * GetImpl() const;
};

}//namespace SDICOS

#endif
