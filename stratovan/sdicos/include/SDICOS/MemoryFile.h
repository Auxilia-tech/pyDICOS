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
#ifndef _STRATOVAN_DICOS_MEMORYFILE_H__
#define _STRATOVAN_DICOS_MEMORYFILE_H__

#include "SDICOS/IMemoryFile.h"
#include "SDICOS/MemoryBuffer.h"
#include <stdio.h>
#include <vector>

namespace SDICOS
{

	class MemoryFile	: public IMemoryFile, protected MemoryBuffer
	{
	public:
		MemoryFile();
		virtual ~MemoryFile();

		// Allow copying of memory buffer objects...
		MemoryFile(const MemoryFile &);
		MemoryFile& operator=(const MemoryFile &);

		/// Returns true if the if Length() amount of GetBuffer() is equal
		virtual bool operator==(const MemoryFile &rhs)const;
		virtual bool operator!=(const MemoryFile &rhs)const;

		virtual bool		Open(const Filename &filename, OPEN_TYPE nType);
		virtual bool		Open(const std::string &strFilename, OPEN_TYPE nType);
		virtual bool		Close();

		/// Preserves contents in the current buffer. Changes allocated size if nSize 
		/// is larger than the current allocated size
		virtual bool		GrowToSafe(S_UINT64 nSize);	
		virtual S_UINT64	GetAllocatedBufferSize()const; ///< Returns the allocated buffer size

		virtual bool		Seek(S_INT64 nPos, SEEK nType);
		virtual S_UINT64	Tell()const;
		virtual bool		IsEof();
		/// Returns the size of the allocated buffer in use
		/// @see GrowToSafe
		/// @see ChangeSize
		virtual S_UINT64	Length()const;	

		/// Changes the size of the buffer in use if less than the allocated buffer size.
		/// Otherwise increases the buffer size using GrowToSafe()
		/// @see GrowToSafe
		virtual bool		ChangeSize(S_UINT64 nSize); 

		virtual bool		Compress(IMemoryFile &output)const;							///< Compress this object and places the results in output
		virtual bool		Uncompress(IMemoryFile &output, int nOutputSize = -1)const;	///< Uncompress this object and place the results in output, if the output size is known (saved using some other mechanism) please specify it here, otherwise a -1 indicates that a memory buffer of at least twice the size as the input buffer will be allocated (and possibly re-allocated if it's too small, which could slow things down).

		virtual bool		CompressByBlock(IMemoryFile &output, S_UINT64 nRecommendedBlockSize = 2<<24)const;	///< Compress this object (nMaxBlockSize bytes at a time) and places the results in output
		virtual bool		UncompressByBlock(IMemoryFile &output, int nOutputSize = -1)const;			///< Uncompress this object (nMaxBlockSize bytes at a time) and place the results in output, if the output size is known (saved using some other mechanism) please specify it here, otherwise a -1 indicates that a memory buffer of at least twice the size as the input buffer will be allocated (and possibly re-allocated if it's too small, which could slow things down).

		virtual bool		Deflate(IMemoryFile &output)const;							///< Same as Compress(), but it doesn't wrap the compressed data with the zlib header/trailer. The data is then the raw DEFLATE data...which is useful in many situations such as DICOM compressions and zip archives.
		virtual bool		Inflate(IMemoryFile &output, int nOutputSize = -1)const;		///< Same as Uncompress(), but it doesn't expect the zlib header/trailer to be wrapped.  The data is then the raw DEFLATE data...which is useful in many situations such as DICOM compressions and zip archives.

		virtual bool		WriteInto(IFile &file)const;
		virtual bool		ReadFrom(IFile &file, S_UINT64 nLength);

		//virtual bool		ComputeMD5(MD5 &md5)const;			///< Computes the md5 hash on the whole memory file
		virtual bool		ComputeCRC32(unsigned int &nCRC32)const;	///< Computes the crc32 hash on the whole memory file

		unsigned char*			GetBuffer();
		const unsigned char*	GetBuffer()const;

		/// Set if this object owns or does not own the data. By default, the object is set to own the data.
		///
		/// If the memory file owns the data and data is open for writing, then a write that would occur beyond
		/// the allocated space would cause the buffer to increase in size to facilitate the write
		void SetMemoryPolicy(const MEMORY_POLICY nPolicy);
		/// @see SetMemoryPolicy
		MEMORY_POLICY GetMemoryPolicy()const;

		void SetBuffer(unsigned char* pBuffer, const S_UINT64 nSize); ///< Calls MemoryBuffer::SetBuffer.  Sets file pointer to front of file
		void SetBuffer(MemoryBuffer &membuffer); ///< Moves buffer to MemoryFile

		/// Creates a single buffer from the set of buffers. If 'bMoveData' is 'true', data is move out of the buffers in 'vmembuffers'.
		bool SetBufferCombined(std::vector<MemoryBuffer*> &vmembuffers, const bool bMoveData);

		/// Move buffer from this object to memfileDst. This object is reset to default values, but retains memory policy.
		void TransferBuffer(MemoryFile &memfileDst);
		/// Move memory buffer from MemoryFile to membufferDst.
		/// If this object does not own the buffer data or the param bTransferLengthSize is set to false, call Length() before 
		/// this function to retrieve the used size of the buffer as the entire buffer is moved to membufferDst.
		/// @param membufferDst			Buffer to move/copy data into
		/// @param bTransferLengthSize	Parameter used only if this object own the buffer data. If 'true' and 
		///								GetAllocatedBufferSize() does not equal Length(), membufferDst is 
		///								allocated to the size of Length() and the data is copied. If 'false', the buffer 
		///								data is moved into membufferDst.
		/// @see Length
		bool TransferBuffer(MemoryBuffer &membufferDst, const bool bTransferLengthSize);

	protected:

		// Hide copying of base class object...
		MemoryFile(const IFile &){}
		void operator=(const IFile &){}
		MemoryFile(const IMemoryFile &){}
		void operator=(const IMemoryFile &){}
		MemoryFile(const MemoryBuffer &){}
		void operator=(const MemoryBuffer &){}

		virtual bool ReadInternal(S_UINT8  pData[], S_UINT64 nLen);
		virtual bool WriteInternal(const S_UINT8  pData[], S_UINT64 nLen);

		class MemoryFileImpl;
		MemoryFileImpl	*m_pMemoryFileImpl;
	};

}	// namespace SDICOS


#endif

///	\file
/// Use for memory-resident files.
///








