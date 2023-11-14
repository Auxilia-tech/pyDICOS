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
#ifndef _STRATOVAN_DICOS_IMAGE_HISTOGRAM_USER_H_
#define _STRATOVAN_DICOS_IMAGE_HISTOGRAM_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/ImageHistogramModule.h"

namespace SDICOS
{
	///
	/// \class ImageHistogramUser
	/// Implements Image Histogram Module User Level API
	///
	class ImageHistogramUser
	{
	public:
		/// Default constructor
		ImageHistogramUser();

		/// Copy Constructor
		ImageHistogramUser(const ImageHistogramUser& imagehistogrammodule);

		/// Destructor
		~ImageHistogramUser();

		/// Assignment operator
		ImageHistogramUser& operator=(const ImageHistogramUser& imagehistogrammodule);

		/// Comparison operator
		bool operator==(const ImageHistogramUser& imagehistogrammodule)const;
		/// Comparison operator
		bool operator!=(const ImageHistogramUser& imagehistogrammodule)const;

		/// Read from ImageHistogramModule object
		bool Read(const ImageHistogramModule& rhs, ErrorLog& el);

		/// Write to ImageHistogramModule object
		bool Write(ImageHistogramModule& lhs, ErrorLog& el) const;

		/// Is the Image Histogram set to valid values
		bool IsValid() const;

		/// Free allocated resources and reset to default state
		void FreeMemory();

		/// Set Histogram Sequence : Tag (0060, 3000), VR = SQ [required]
		/// @param arrayHistograms Array of histogram sequence items containing histogram attributes
		/// @return true/false false if some of the histogram sequences are invalid
		bool SetHistograms(const Array1D<ImageHistogramModule::HistogramSequenceItem>& arrayHistograms);

		/// @see SetHistograms
		bool GetHistograms(Array1D<ImageHistogramModule::HistogramSequenceItem>& arrayHistograms)const;

		/// @see SetHistograms
		Array1D<ImageHistogramModule::HistogramSequenceItem>& GetHistograms();

		/// @see SetHistograms
		const Array1D<ImageHistogramModule::HistogramSequenceItem>& GetHistograms() const;

	private:
		class ImplImageHistogram;
		ImplImageHistogram* m_pImplImageHistogram; ///< Internal implementation

		ImplImageHistogram* GetImpl();
		const ImplImageHistogram* GetImpl() const;
	};

}//namespace SDICOS

#endif
