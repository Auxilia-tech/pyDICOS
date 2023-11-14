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
#ifndef _STRATOVAN_DICOS_SDCS_BITMAP_H_
#define	_STRATOVAN_DICOS_SDCS_BITMAP_H_

#include <iostream>
#include "SDICOS/MemoryBuffer.h"

namespace SDICOS {
	
	///
	/// \class Bitmap
	/// Represent a packed bitmap storing 1-bit per entry
	///
	class Bitmap {
		
	public:
		/// Default Constructor
		Bitmap();

		/// Create a bitmap to hold the indicated number of bits
		Bitmap(const S_UINT64 numBits);

		/// Create a bitmap with the number of bits in each dimension
		Bitmap(const S_UINT64 xDim, const S_UINT64 yDim, const S_UINT64 zDim);

		/// Copy Constructor
		Bitmap(const Bitmap& b);
		
		~Bitmap(){};

		/// Assignment operator
		Bitmap& operator=(const Bitmap& b);
		
		bool operator==(const Bitmap& b) const;
		bool operator!=(const Bitmap& b) const;

		/// Comparison that uses the first N bytes of the bitmaps.
		///
		/// @param rhs Bitmap to compare
		/// @param iNumBytesToCompare Number of bytes to compare. Zero indicates to use the lessor of the two bitmap sizes.
		/// @return true/false true if dimensions are equal and indicated number of bytes match
		bool Compare(const Bitmap& rhs, SDICOS::S_UINT64 iNumBytesToCompare) const;

		friend std::ostream& operator<<(std::ostream& os, const Bitmap& b);
		
		/// Delete allocated memory
		void FreeMemory();

		MemoryBuffer& GetBitmap();
		const MemoryBuffer& GetBitmap() const;

		/// Set Bitmap from the indicated buffer
		/// @param mb Packed Bitmap data
		/// @param move	bool indicating whether data should be moved or copied
		bool SetBitmapData(MemoryBuffer& mb, const bool move = false);

		/// Copy the memory buffer into the bitmap
		bool SetBitmapData(const MemoryBuffer& mb);
		
		/// Set the indicated bit
		/// @return true/false false if the index is out of bounds
		bool SetBit(const S_UINT64 bitIndex, const bool bit);
		bool SetBit(const S_UINT64 x, const S_UINT64 y, const S_UINT64 z, const bool bit);

		/// Get the indicated bit
		/// @return true/false false if the index is out of bounds
		bool GetBit(const S_UINT64 bitIndex, bool& bit) const;
		bool GetBit(const S_UINT64 x, const S_UINT64 y, const S_UINT64 z, bool& bit) const;

		bool GetBit(const S_UINT64 bitIndex) const;
		bool GetBit(const S_UINT64 x, const S_UINT64 y, const S_UINT64 z) const;

		S_UINT64 GetSize() const;
		
		/// Set bitmap's dimensions. Bits are initialized to 0.
		///  1) This deletes existing data.
		/// @param x Magnitude for X
		/// @param y Magnitude for Y
		/// @param z Magnitude for Z
		/// @param bAllocateEvenNumberOfBytes If (X*Y*Z) number of bits maps to an odd number of bytes, allocate an additional byte to make it even.
		/// @return true/false false if any dimensions are 0
		bool SetDims(const S_UINT64 x, const S_UINT64 y, const S_UINT64 z, const bool bAllocateEvenNumberOfBytes = false);

		bool GetDims(S_UINT32& x, S_UINT32& y, S_UINT32& z) const;
		bool GetDims(S_UINT64& x, S_UINT64& y, S_UINT64& z) const;

		/// Equivalent to GetWidth()*GetHeight()*GetDepth().
		S_UINT64 GetNumBits() const;

		S_UINT64 GetWidth()const;
		S_UINT64 GetHeight()const;
		S_UINT64 GetDepth()const;

	private:
		
		/// Initialize bitmap memory buffer
		void InitBitmap(const S_UINT64 nNumBits, const bool bAllocateEvenNumberOfBytes);

		S_UINT64 m_NumBits;
		S_UINT64 m_Dims[3];
		MemoryBuffer m_Bitmap;
	};
} // namespace SDICOS

#endif	/* _STRATOVAN_DICOS_SDCS_BITMAP_H_ */

