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
#ifndef _STRATOVAN_DICOS_VOLUME_H_
#define _STRATOVAN_DICOS_VOLUME_H_

#include "SDICOS/Array3DLarge.h"
#include "SDICOS/ImageDataBase.h"
#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/MemoryBufferConst.h"

namespace SDICOS
{

///
/// \class Volume
/// \brief Stores 3D volume of any data type: float and 8-, 16-, 32-, and 64-bit
class Volume : public ImageDataBase
{
public:

	///
	/// \class SliceIterator
	/// \brief Slice iterator for Volume class
	class SliceIterator
	{
	public:
		/// Constructor
		SliceIterator();
		/// Copy Constructor
		SliceIterator(const SliceIterator &it);
		/// Initialize the iterator for the target volume
		SliceIterator(const Volume &vol);
		/// Destructor
		~SliceIterator();

		/// Initialize the iterator for the target volume
		bool InitBegin(const Volume &vol);

		/// Returns the data type of the volume
		IMAGE_DATA_TYPE GetVolumeDataType()const;

		/// Returns slice index for iterator's current slice
		S_INT32 GetCurrentSlice()const;

		/// Copy an iterator
		SliceIterator& operator=(const SliceIterator &it);
		/// Compare iterator
		bool operator==(const SliceIterator &it)const;
		/// Compare iterator
		bool operator!=(const SliceIterator &it)const;

		/// Pre-increment
		SliceIterator&	operator++();
		/// Pre-decrement
		SliceIterator&	operator--();
		/// Post-increment
		SliceIterator	operator++(S_INT32);
		/// Post-decrement
		SliceIterator	operator--(S_INT32);
		/// Offset iterator by index
		SliceIterator	operator+(const S_INT32 n);
		/// Offset iterator by index
		SliceIterator	operator-(const S_INT32 n);
		/// Offset iterator by index
		SliceIterator&	operator+=(const S_INT32 n);
		/// Offset iterator by index
		SliceIterator&	operator-=(const S_INT32 n);

		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_UINT8>*	AsUnsigned8();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_UINT16>*	AsUnsigned16();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_UINT32>*	AsUnsigned32();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_UINT64>*	AsUnsigned64();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_INT8>*	AsSigned8();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_INT16>*	AsSigned16();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_INT32>*	AsSigned32();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<S_INT64>*	AsSigned64();
		/// Returns pointer to slice or S_NULL if data type does not match
		Array2D<float>*		AsFloat();

		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_UINT8>*		AsUnsigned8()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_UINT16>*	AsUnsigned16()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_UINT32>*	AsUnsigned32()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_UINT64>*	AsUnsigned64()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_INT8>*		AsSigned8()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_INT16>*		AsSigned16()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_INT32>*		AsSigned32()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<S_INT64>*		AsSigned64()const;
		/// Returns pointer to slice or S_NULL if data type does not match
		const Array2D<float>*		AsFloat()const;

	protected:
		class SliceIteratorImpl;
		SliceIteratorImpl *m_pSliceIteratorImpl;
	};//class SliceIterator

	/// Construct a volume indicating data type and memory policy.
	Volume(	const IMAGE_DATA_TYPE nDataType = enumUndefinedDataType,
			const MemoryPolicy::VOLUME_MEMORY_POLICY nMemoryPolicy = SDICOS::MemoryPolicy::OWNS_SLICES);

	/// Copy constructor
	Volume(const Volume &vol);
	/// Destructor
	~Volume();

	/// Copy operator
	Volume& operator=(const Volume &vol);
	/// Comparison operator
	bool operator==(const Volume &vol)const;
	/// Comparison operator
	bool operator!=(const Volume &vol)const;

	/// Copy signed 8bit volume
	Volume& operator=(const Array3DLarge<S_INT8> &vol);
	/// Copy unsigned 8bit volume
	Volume& operator=(const Array3DLarge<S_UINT8> &vol);
	/// Copy signed 16bit volume
	Volume& operator=(const Array3DLarge<S_INT16> &vol);
	/// Copy unsigned 16bit volume
	Volume& operator=(const Array3DLarge<S_UINT16> &vol);
	/// Copy signed 32bit volume
	Volume& operator=(const Array3DLarge<S_INT32> &vol);
	/// Copy unsigned 32bit volume
	Volume& operator=(const Array3DLarge<S_UINT32> &vol);
	/// Copy signed 64bit volume
	Volume& operator=(const Array3DLarge<S_INT64> &vol);
	/// Copy unsigned 64bit volume
	Volume& operator=(const Array3DLarge<S_UINT64> &vol);
	/// Copy signed float volume
	Volume& operator=(const Array3DLarge<float> &vol);

	/// Comparison operator
	bool operator==(const Array3DLarge<S_INT8> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_INT8> &vol)const;
	/// Comparison operator
	bool operator==(const Array3DLarge<S_UINT8> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_UINT8> &vol)const;

	/// Comparison operator
	bool operator==(const Array3DLarge<S_INT16> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_INT16> &vol)const;
	/// Comparison operator
	bool operator==(const Array3DLarge<S_UINT16> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_UINT16> &vol)const;

	/// Comparison operator
	bool operator==(const Array3DLarge<S_INT32> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_INT32> &vol)const;
	/// Comparison operator
	bool operator==(const Array3DLarge<S_UINT32> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_UINT32> &vol)const;

	/// Comparison operator
	bool operator==(const Array3DLarge<S_INT64> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_INT64> &vol)const;
	/// Comparison operator
	bool operator==(const Array3DLarge<S_UINT64> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<S_UINT64> &vol)const;

	/// Comparison operator
	bool operator==(const Array3DLarge<float> &vol)const;
	/// Comparison operator
	bool operator!=(const Array3DLarge<float> &vol)const;

	/// Returns iterator to first slice
	SliceIterator Begin()const;
	/// Returns iterator to end slice
	SliceIterator End()const;

	/// Return volume width
	S_UINT32 GetWidth()const;
	/// Return volume height
	S_UINT32 GetHeight()const;
	/// Return volume depth
	S_UINT32 GetDepth()const;

	/// GetWidth() * GetHeight*()
	S_UINT32 GetSliceSize()const;

	/// Get the number of bytes in a slice
	S_UINT32 GetSliceSizeInBytes()const;

	/// Get the size of the volume in bytes
	S_UINT64 GetSizeInBytes()const;

	/// Get the number of elements that have been allocated
	S_UINT32 GetCapacity()const;

	/// Free allocated memory according to the Memory Allocation Policy
	/// Reset the dimensions of the volume to (0,0,0).
	void FreeMemory();

	/// Clear the number of slices in the volume and free slice memory.
	/// Does not reset the dimensions of the volume.
	/// This method is intended to be used with SDICOS::MemoryPolicy::DOES_NOT_OWN_SLICES
	/// where the user, not the Volume object, controls slice memory.
	void Clear();

	/// Write image data only, excludes dimensions, data type, and memory policy
	bool WriteImageData(IFile &file)const;
	/// Read image data only. Volume must already be allocated to proper dimensions before reading
	bool ReadImageData(IFile &file);

	/// Indicate whether or not the Volume is responsible for deleting its slices.
	void SetMemoryPolicy(const MemoryPolicy::VOLUME_MEMORY_POLICY nMemoryPolicy);
	/// Get the memory policy
	MemoryPolicy::VOLUME_MEMORY_POLICY GetMemoryPolicy()const;

	/// Set memory manager for deallocating pixel data not owned by this object
	void SetMemoryManager(IMemoryManager *pMemManager);
	/// @see SetMemoryManager
	IMemoryManager* GetMemoryManager()const;

	/// Set volume data type. Calls FreeMemory() if data type does not match the current data type.
	bool Allocate(const IMAGE_DATA_TYPE nDataType);

	/// Set volume data type and allocate space.
	/// @return true/false Returns false if data type or bounds are invalid
	bool Allocate(const IMAGE_DATA_TYPE nDataType, SDICOS::S_UINT32 nWidth, const SDICOS::S_UINT32 nHeight, const SDICOS::S_UINT32 nDepth);

	/// Sets data size.
	/// @return true/false Returns false if data type has not been set
	bool SetSize(SDICOS::S_UINT32 nWidth, const SDICOS::S_UINT32 nHeight, const SDICOS::S_UINT32 nDepth);

	/// Returns data type
	IMAGE_DATA_TYPE GetVolumeDataType()const;

	/// Extract volume from an ImagePixelModule object.
	/// Returns false if data could not be extracted from ImagePixelModule object. false can occur 
	/// if the pixel representation value within ImagePixelModule is unknown.
	///
	/// @param ipm Source of pixel data
	/// @param bSetAsReference	true = Changes memory policy to not own data and to reference the input data
	///							false = Changes memory policy to own data and copies pixel data
	bool Set(ImagePixelModule& ipm, const bool bSetAsReference);

	/// Move ownership of pixel data from ImagePixelModule to this object.
	/// If ImagePixelModule does not own the data, this object will be a reference to the data instead.
	///
	/// @param ipm Input pixel data
	/// @param bMustOwnData	true = return false if ImagePixelModule does not own the data
	///						false = allow this object to reference pixel data. Removes references from ImagePixelModule.
	bool MoveInto(ImagePixelModule& ipm, const bool bMustOwnData = true);

	/// Set as a sub volume. Range from volume[nFirstFrame] to volume[nLastFrame] inclusive.
	bool SetAsSubVolume(const S_UINT32 nFirstFrame, const S_UINT32 nLastFrame, const Volume &volume);

	/// Set as a composite volume from an array of volumes.
	///
	/// @param vVolumes Array of volumes must have equal width and height dimensions and data type.
	/// @param bSetAsReference	true = Set as reference to vVolumes, instead of copying slices
	///							false = Copy data to build single volume
	/// @return Returns false if one or more volumes in the array did meet the requirements
	bool SetAsCompositeVolume(const Array1D<Volume*> &vVolumes, const bool bSetAsReference);
	/// @see SetAsCompositeVolume(const Array1D<const Volume*> &, const bool)
	bool SetAsCompositeVolume(Array1D<Volume> &vVolumes, const bool bSetAsReference);

	/// Delete existing data, then moves all slices from volSrc to this object. 
	/// This object uses the same memory policy as volSrc.
	/// @param volSrc Source data to move data out of
	bool Move(Volume &volSrc);

	/// Copies pointer to Array2D buffer.
	/// To transfer data ownership, the input slice and this object must both be set to own the data.
	/// If this object is set to own data, but the input slice is set to not own data, then this function
	/// returns false and the slice is not added.
	/// If the volume data type does not match the slice data type, false is returned.
	///
	/// @param pNewSlice Slice to add
	/// @param nFailurePolicy Action to take if adding a slice fails.
	/// @return true/false false if the slice was not added
	/// @see SetMemoryPolicy
	bool AddSlice(Array2D<S_UINT8> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_UINT16> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_UINT32> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_UINT64> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_INT8> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_INT16> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_INT32> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<S_INT64> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlice(Array2D<S_UINT8>*)
	bool AddSlice(Array2D<float> *pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// Add a specific slice from the source volume.
	/// If both volumes own data, then the slice will transfer ownership to this object, but the source volume's
	/// memory policy will remain unchanged. Multiple calls to this function can result in a volume where some
	/// slices are owned by this object and other slices are referenced. As long as SetMemoryPolicy() is not called
	/// afterwards, the memory deletion will occur as expected. SetMemoryPolicy() updates the default memory policy
	/// as well as each slice's individual memory policy.
	///
	/// @param volSrc Source volume to add slice from
	/// @param nSliceSrc Slice to add from source volume
	/// @param nFailurePolicy Action to take if adding a slice fails.
	bool AddSlice(Volume &volSrc, const S_UINT32 nSliceSrc, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// Add slice. 
	/// Transfer data ownership by setting the memory buffer and this object to own the data.
	/// Set this object as a reference to the data by settin this object's memory policy to not own the data.
	bool AddSlice(MemoryBuffer &mbSlice, const S_UINT32 nWidth, const S_UINT32 nHeight);

	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_UINT8>* AddSliceUnsigned8();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_INT8>* AddSliceSigned8();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_UINT16>* AddSliceUnsigned16();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_INT16>* AddSliceSigned16();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_UINT32>* AddSliceUnsigned32();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_INT32>* AddSliceSigned32();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_UINT64>* AddSliceUnsigned64();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<S_INT64>* AddSliceSigned64();
	/// Allocate and add a slice to the end of the volume. The volume must already be allocated with at least one slice.
	Array2D<float>* AddSliceFloat();

	/// Copies pointers to volume slices. The memory policy determines ownership. 
	/// If this volume's data type does not match the slices' data type, false is returned.
	/// @param vol Three dimensional volume of data
	/// @return true/false false if the volume data types or dimensions do not match
	/// @param nFailurePolicy Action to take if adding a slice fails.
	/// @see SetMemoryPolicy
	bool AddSlices(Array3DLarge<S_UINT8> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_UINT16> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_UINT32> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_UINT64> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_INT8> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_INT16> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_INT32> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<S_INT64> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Array3DLarge<float> &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSlices(Array3DLarge<S_UINT8>&)
	bool AddSlices(Volume &vol, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);

	/// Add slices using iterators similar to stl iterators.
	///
	/// The dereferenced iterator must be pf type Array2D<TYPE>*, where TYPE is 
	/// the data of this object if it is already allocated.
	///
	/// Allocates volume to slice type if volume is not allocated.
	template<typename ITERATOR>
	bool AddSlices(ITERATOR itStart, const ITERATOR &itEnd, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{
		bool bRes(true);

		if (Array3DLargeBase::EARLY_OUT == nFailurePolicy)
		{
			for (; bRes && itStart != itEnd; ++itStart)
				bRes = AddSlice(*itStart, nFailurePolicy);
		}
		else
		{
			for (; itStart != itEnd; ++itStart)
				bRes = AddSlice(*itStart, nFailurePolicy) && bRes;
		}

		return bRes;
	}

	/// Copies a slice from the source to a slice of this object
	/// @param volSrc Volume with slice to copy
	/// @param nSliceSrc Index of slice to copy
	/// @param nSliceDst Index of this object's slice to overwrite with source's slice
	bool CopySlice(const Volume &volSrc, const S_UINT32 nSliceSrc, const S_UINT32 nSliceDst);

	/// Applies rescale slope and intercept to the volume
	bool ApplyRescale(const float fSlope, const float fIntercept);

	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_INT8>*	GetSigned8();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_INT16>*	GetSigned16();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_INT32>*	GetSigned32();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_INT64>*	GetSigned64();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_UINT8>*	GetUnsigned8();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_UINT16>* GetUnsigned16();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_UINT32>* GetUnsigned32();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<S_UINT64>* GetUnsigned64();
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	Array3DLarge<float>*	GetFloat();

	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_INT8>*		GetSigned8()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_INT16>*	GetSigned16()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_INT32>*	GetSigned32()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_INT64>*	GetSigned64()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_UINT8>*	GetUnsigned8()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_UINT16>*	GetUnsigned16()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_UINT32>*	GetUnsigned32()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<S_UINT64>*	GetUnsigned64()const;
	/// Returns pointer to volume or S_NULL if volume type does not match return type
	const Array3DLarge<float>*		GetFloat()const;

	/// Get a reference to a slice as a memory buffer. The memory buffer does not own the data.
	/// @param mbSlice Memory buffer to reference the target slice
	/// @param nSlice Slice to reference
	bool GetSlice(MemoryBufferConst &mbSlice, const S_UINT32 nSlice)const;

protected:
	class VolumeImpl;
	VolumeImpl *m_pVolumeImpl;
};//class Volume

}//namespace SDICOS

#endif