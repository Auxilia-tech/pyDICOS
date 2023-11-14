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
#ifndef _STRATOVAN_DICOS_IMAGE_HISTOGRAM_MODULE_H_
#define _STRATOVAN_DICOS_IMAGE_HISTOGRAM_MODULE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class ImageHistogramModule
/// Implements Image Histogram
/// SPECREF V03 Section 14.2.6, Table 92
///
class ImageHistogramModule
{
public:
	/// Default constructor
	ImageHistogramModule();

	/// Copy Constructor
	ImageHistogramModule(const ImageHistogramModule &imagehistogrammodule);

	/// Destructor
	~ImageHistogramModule();

	/// Assignment operator
	ImageHistogramModule& operator=(const ImageHistogramModule &imagehistogrammodule);

	/// Comparison operator
	bool operator==(const ImageHistogramModule &imagehistogrammodule)const;
	/// Comparison operator
	bool operator!=(const ImageHistogramModule &imagehistogrammodule)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified and are invalid
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Free allocated resources and reset to default state
	void FreeMemory();
	
	///
	/// \class HistogramSequenceItem
	/// The HistogramSequenceItem represents one attribute in the histogram sequence
	/// It encompasses the attributes in table 76 that are part of the histogram sequence.
	///
	class HistogramSequenceItem
	{
	public:
		/// Constructor
		HistogramSequenceItem();

		/// Copy Constructor
		HistogramSequenceItem(const HistogramSequenceItem &histogramsequenceitem);

		/// Destructor
		~HistogramSequenceItem();

		/// Initialize the class attributes from the given AttributeManager
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Copy the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified and are invalid
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Free allocated resources and reset to default state
		void FreeMemory();

		/// Assignment operator
		HistogramSequenceItem& operator=(const HistogramSequenceItem &histogramsequenceitem);

		/// Comparison operator
		bool operator==(const HistogramSequenceItem &histogramsequenceitem)const;

		/// Comparison operator
		bool operator!=(const HistogramSequenceItem &histogramsequenceitem)const;

		/// Set Number of Bins : Tag (0060, 3002), VR = US [required]
		bool SetNumberOfBins(const S_UINT16 nNumberOfBins);

		/// @see SetNumberOfBins
		S_UINT16 GetNumberOfBins()const;

		/// Set First Bin Value : Tag (0060, 3004), VR = US or SS [required if using 8-16bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Lowest pixel value
		bool SetFirstBinValue(const S_UINT16 nFirstBinValue);
		/// @see SetFirstBinValue(const S_UINT16)
		bool SetFirstBinValue(const S_INT16 nFirstBinValue);
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_UINT16 &nFirstBinValue)const;
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_INT16 &nFirstBinValue)const;
		/// Set First Bin Value : Tag (0060, 4004), VR = UL or SL [required if using 32bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Lowest pixel value
		bool SetFirstBinValue(const S_UINT32 nFirstBinValue);
		/// @see SetFirstBinValue(const S_UINT32)
		bool SetFirstBinValue(const S_INT32 nFirstBinValue);
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_UINT32 &nFirstBinValue)const;
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_INT32 &nFirstBinValue)const;
		/// Set First Bin Value : Tag (0060, 5004), VR = UD or SD [required if using 64bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Lowest pixel value
		bool SetFirstBinValue(const S_UINT64 nFirstBinValue);
		/// @see SetFirstBinValue(const S_UINT64)
		bool SetFirstBinValue(const S_INT64 nFirstBinValue);
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_UINT64 &nFirstBinValue)const;
		/// @see SetFirstBinValue
		bool GetFirstBinValue(S_INT64 &nFirstBinValue)const;
		/// Set First Bin Value : Tag (0060, 6004), VR = FL [required if using 32bit float pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Lowest pixel value
		bool SetFirstBinValue(const float nFirstBinValue);
		/// @see SetFirstBinValue
		bool GetFirstBinValue(float &nFirstBinValue)const;

		/// Set Last Bin Value : Tag (0060, 3006), VR = US or SS [required if using 8-16bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Highest pixel value
		bool SetLastBinValue(const S_UINT16 nLastBinValue);
		/// @see SetLastBinValue
		bool SetLastBinValue(const S_INT16 nLastBinValue);
		/// @see SetLastBinValue
		bool GetLastBinValue(S_UINT16 &nLastBinValue)const;
		/// @see SetLastBinValue
		bool GetLastBinValue(S_INT16 &nLastBinValue)const;

		/// Set Last Bin Value : Tag (0060, 4006), VR = UL or SL [required if using 32bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Highest pixel value
		bool SetLastBinValue(const S_UINT32 nLastBinValue);
		/// @see SetLastBinValue
		bool SetLastBinValue(const S_INT32 nLastBinValue);
		/// @see SetLastBinValue
		bool GetLastBinValue(S_UINT32 &nLastBinValue)const;
		/// @see SetLastBinValue
		bool GetLastBinValue(S_INT32 &nLastBinValue)const;

		/// Set Last Bin Value : Tag (0060, 5006), VR = UD or SD [required if using 64bit pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Highest pixel value
		bool SetLastBinValue(const S_UINT64 nLastBinValue);
		/// @see SetLastBinValue
		bool SetLastBinValue(const S_INT64 nLastBinValue);
		/// @see SetLastBinValue
		bool GetLastBinValue(S_UINT64 &nLastBinValue)const;
		/// @see SetLastBinValue
		bool GetLastBinValue(S_INT64 &nLastBinValue)const;

		/// Set Last Bin Value : Tag (0060, 6006), VR = FL [required if using 32bit float pixel data]
		///		i) VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
		///		ii) Highest pixel value
		bool SetLastBinValue(const float nLastBinValue);
		/// @see SetLastBinValue
		bool GetLastBinValue(float &nLastBinValue)const;

		/// Set Bin Width : Tag (0060, 3008), VR = US [required]
		bool SetBinWidth(const S_UINT16 nBinWidth);

		/// @see SetBinWidth
		S_UINT16 GetBinWidth()const;

		/// Set Histogram Explanation : Tag (0060, 3010), VR = LO [optional]
		bool SetExplanation(const DcsLongString strExplanation);

		/// @see SetExplanation
		DcsString GetExplanation()const;

		/// Returns true if data is set
		/// @see SetExplanation
		bool HasExplanation()const;
		/// Deletes data
		void DeleteExplanation();

		/// Set Histogram Data : Tag (0060, 3020)
		///	@param arrayHistogramValues Param 1, Data Array : Tag (0060, 3020), VR = UL [required]
		///		i) All values stored in the same tag
		bool SetData(const Array1D<S_UINT32> &arrayHistogramValues);

		/// @see SetData
		bool GetData(Array1D<S_UINT32> &arrayHistogramValues)const;
		/// @see SetData
		Array1D<S_UINT32>& GetData();
		/// @see SetData
		const Array1D<S_UINT32>& GetData()const;

	private:

		class ImplHistogramSequenceItem;
		ImplHistogramSequenceItem	*m_pImplHistogramSequenceItem; ///< Internal implementation

		ImplHistogramSequenceItem* GetImpl();
		const ImplHistogramSequenceItem *GetImpl() const;
	};

	/// Set Histogram Sequence : Tag (0060, 3000), VR = SQ [required]
	/// @param arrayHistograms Array of histogram sequence items containing histogram attributes
	/// @return true/false false if some of the histogram sequences are invalid
	bool SetHistograms(const Array1D<HistogramSequenceItem> &arrayHistograms);

	/// @see SetHistograms
	bool GetHistograms(Array1D<HistogramSequenceItem> &arrayHistograms)const;

	/// @see SetHistograms
	Array1D<HistogramSequenceItem>& GetHistograms();
	
	/// @see SetHistograms
	const Array1D<HistogramSequenceItem>& GetHistograms() const;
	
private:
	class ImplImageHistogram;
	ImplImageHistogram	*m_pImplImageHistogram; ///< Internal implementation

	ImplImageHistogram* GetImpl();
	const ImplImageHistogram* GetImpl() const;
};

}//namespace SDICOS

#endif
