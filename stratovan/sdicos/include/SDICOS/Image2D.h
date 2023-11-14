//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2018 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_IMAGE2D_H_
#define _STRATOVAN_DICOS_IMAGE2D_H_

#include "SDICOS/Array2D.h"
#include "SDICOS/ImageDataBase.h"
#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/MemoryBufferConst.h"

namespace SDICOS
{
class Image2D : public ImageDataBase
{
public:

	/// Construct an image indicating data type
	Image2D(const IMAGE_DATA_TYPE nDataType = enumUndefinedDataType,
			const MemoryPolicy::VOLUME_MEMORY_POLICY nMemoryPolicy = MemoryPolicy::OWNS_DATA);

	/// Copy constructor
	Image2D(const Image2D &img);
	/// Destructor
	~Image2D();

	/// Copy operator
	Image2D& operator=(const Image2D &img);
	/// Comparison operator
	bool operator==(const Image2D &img)const;
	/// Comparison operator
	bool operator!=(const Image2D &img)const;

	/// Copy signed 8bit Image2D
	Image2D& operator=(const Array2D<S_INT8> &img);
	/// Copy unsigned 8bit Image2D
	Image2D& operator=(const Array2D<S_UINT8> &img);
	/// Copy signed 16bit Image2D
	Image2D& operator=(const Array2D<S_INT16> &img);
	/// Copy unsigned 16bit Image2D
	Image2D& operator=(const Array2D<S_UINT16> &img);
	/// Copy signed 32bit Image2D
	Image2D& operator=(const Array2D<S_INT32> &img);
	/// Copy unsigned 32bit Image2D
	Image2D& operator=(const Array2D<S_UINT32> &img);
	/// Copy signed 64bit Image2D
	Image2D& operator=(const Array2D<S_INT64> &img);
	/// Copy unsigned 64bit Image2D
	Image2D& operator=(const Array2D<S_UINT64> &img);
	/// Copy signed float Image2D
	Image2D& operator=(const Array2D<float> &img);

	/// Comparison operator
	bool operator==(const Array2D<S_INT8> &img)const;
	bool operator!=(const Array2D<S_INT8> &img)const;
	bool operator==(const Array2D<S_UINT8> &img)const;
	bool operator!=(const Array2D<S_UINT8> &img)const;

	/// Comparison operator
	bool operator==(const Array2D<S_INT16> &img)const;
	bool operator!=(const Array2D<S_INT16> &img)const;
	bool operator==(const Array2D<S_UINT16> &img)const;
	bool operator!=(const Array2D<S_UINT16> &img)const;

	/// Comparison operator
	bool operator==(const Array2D<S_INT32> &img)const;
	bool operator!=(const Array2D<S_INT32> &img)const;
	bool operator==(const Array2D<S_UINT32> &img)const;
	bool operator!=(const Array2D<S_UINT32> &img)const;

	/// Comparison operator
	bool operator==(const Array2D<S_INT64> &img)const;
	bool operator!=(const Array2D<S_INT64> &img)const;
	bool operator==(const Array2D<S_UINT64> &img)const;
	bool operator!=(const Array2D<S_UINT64> &img)const;

	/// Comparison operator
	bool operator==(const Array2D<float> &img)const;
	bool operator!=(const Array2D<float> &img)const;

	/// Return bits per pixel
	S_UINT32 GetBitsPerPixel() const;

	/// Return bits stored per pixel
	S_UINT32 GetBitsStoredPerPixel() const;

	/// Return most significant high-bit for pixel data
	S_UINT32 GetHighBit() const;

	/// Return image width
	S_UINT32 GetWidth()const;
	/// Return image height
	S_UINT32 GetHeight()const;

	/// GetWidth() * GetHeight*()
	S_UINT32 GetSize()const;

	/// Get the number of bytes in a slice
	S_UINT32 GetSizeInBytes()const;

	/// Free allocated memory
	/// Reset the dimensions of the image to (0,0).
	void FreeMemory();

	/// Indicate whether or not Image2D is responsible for deleting its data.
	void SetMemoryPolicy(const MemoryPolicy::VOLUME_MEMORY_POLICY nMemoryPolicy);
	/// Get the memory policy
	MemoryPolicy::VOLUME_MEMORY_POLICY GetMemoryPolicy()const;

	/// Set memory manager for deallocating pixel data not owned by this object
	void SetMemoryManager(IMemoryManager *pMemManager);
	/// @see SetMemoryManager
	IMemoryManager* GetMemoryManager()const;

	/// Set image data type. Calls FreeMemory() if data type does not match the current data type.
	bool Allocate(const IMAGE_DATA_TYPE nDataType);

	/// Set image data type and allocate space.
	/// @return true/false Returns false if data type or bounds are invalid
	bool Allocate(const IMAGE_DATA_TYPE nDataType, SDICOS::S_UINT32 nWidth, const SDICOS::S_UINT32 nHeight);

	/// Sets data size.
	/// @return true/false Returns false if data type has not been set
	bool SetSize(SDICOS::S_UINT32 nWidth, const SDICOS::S_UINT32 nHeight);

	/// Applies rescale slope and intercept to the volume
	bool ApplyRescale(const float fSlope, const float fIntercept);

	/// Returns data type
	IMAGE_DATA_TYPE GetImageDataType()const;

	/// Extract image from an ImagePixelModule object.
	/// Returns false if data could not be extracted from ImagePixelModule object. false can occur 
	/// if the pixel representation value within ImagePixelModule is unknown.
	///
	/// @param ipm Source of image data
	/// @param bMoveData	true = Move data from ipm to this object
	///						false = Copy data from ipm to this object
	bool Set(ImagePixelModule& ipm, const bool bMoveData);

	/// Delete existing data, then moves image from imgSrc to this object. 
	/// This object uses the same memory policy as imgSrc.
	/// @param imgSrc Source data to move data out of
	bool Move(Image2D &imgSrc);

	/// Returns pointer to image or S_NULL if image type does not match return type
	Array2D<S_INT8>*	GetSigned8();
	Array2D<S_INT16>*	GetSigned16();
	Array2D<S_INT32>*	GetSigned32();
	Array2D<S_INT64>*	GetSigned64();
	Array2D<S_UINT8>*	GetUnsigned8();
	Array2D<S_UINT16>*	GetUnsigned16();
	Array2D<S_UINT32>*	GetUnsigned32();
	Array2D<S_UINT64>*	GetUnsigned64();
	Array2D<float>*		GetFloat();

	/// Returns pointer to image or S_NULL if image type does not match return type
	const Array2D<S_INT8>*		GetSigned8()const;
	const Array2D<S_INT16>*		GetSigned16()const;
	const Array2D<S_INT32>*		GetSigned32()const;
	const Array2D<S_INT64>*		GetSigned64()const;
	const Array2D<S_UINT8>*		GetUnsigned8()const;
	const Array2D<S_UINT16>*	GetUnsigned16()const;
	const Array2D<S_UINT32>*	GetUnsigned32()const;
	const Array2D<S_UINT64>*	GetUnsigned64()const;
	const Array2D<float>*		GetFloat()const;

	/// Get a reference to the pixel data as a memory buffer
	bool GetAsBuffer(MemoryBufferConst &mbImage)const;

protected:
	class Image2DImpl;
	Image2DImpl *m_pImage2DImpl;
};//class Image2D

}//namespace SDICOS

#endif