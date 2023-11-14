//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_MEMORY_BLOCK_FILE_H_
#define _STRATOVAN_DICOS_MEMORY_BLOCK_FILE_H_

#include "SDICOS/File.h"
#include "SDICOS/Memory.h"

namespace SDICOS
{

	/// @brief
	/// Read only
	/// Only loads the minimum needed number of memory blocks
	class MemoryBlockFile_MethodA : public IFile
	{
	public:
		MemoryBlockFile_MethodA(const S_UINT64 nBlockSize = 4096); // Block size in bytes
		~MemoryBlockFile_MethodA();

		S_UINT64				GetBlockSize()const;

		virtual bool			Open(const Filename &filename, OPEN_TYPE nType);
		virtual bool			OpenReading(const Filename &filename);
		virtual bool			Close();

		virtual bool			Seek(S_INT64 nPos, SEEK nType);
		virtual S_UINT64		Tell()const;				///< Tell the position/offset of the file pointer
		virtual bool			IsEof();					///< Whether or not we're at the end of the file. Has similar behavior to feof(). Returns a true after the first read operation that attempts to read past the end of the file. It returns false if the current position is not end of file.
		virtual S_UINT64		Length()const;				///< returns the length of the file...
		virtual bool			ChangeSize(S_UINT64 nSize);	///< Lengthens or shortens the file to the specified size...use with caution
		virtual bool			IsBuffered()const;			///< Return true if this object is a "memory" object. This is/can-be used internally to decide whether or not to make a temporary buffer for reading and writing more quickly...

	protected:

		bool					ReadAdditionalBlocks(const S_UINT64 nLen);

		virtual bool			ReadInternal(S_UINT8 pData[], S_UINT64 nLen);
		virtual bool			WriteInternal(const S_UINT8 pData[], S_UINT64 nLen);
		virtual void			Flush();

		S_UINT64						m_nFileLength;
		File							m_file;				///< File pointer
		S_UINT64						m_nBlockSize;		///< Block size to read at once

		std::vector< MemoryBuffer* >	m_vBlocks;			///< Memory blocks
		S_UINT8							*m_pPointer;		///< Pointer into current block's buffer
		S_UINT64						m_nCurrentBlock;	///< Index into current block

		bool							m_bIsEof;
	};

	/// @brief
	/// Read only
	/// Maintains a maximum number of loaded memory blocks
	class MemoryBlockFile_MethodB : public IFile
	{
	public:
		MemoryBlockFile_MethodB(const S_UINT64 nBlockSize = 4096); ///< Block size in bytes
		~MemoryBlockFile_MethodB();

		S_UINT64				GetBlockSize()const;

		virtual bool			Open(const Filename &filename, OPEN_TYPE nType);
		virtual bool			OpenReading(const Filename &filename);
		virtual bool			Close();

		virtual bool			Seek(S_INT64 nPos, SEEK nType);
		virtual S_UINT64		Tell()const;				///< Tell the position/offset of the file pointer
		virtual bool			IsEof();					///< Whether or not we're at the end of the file. Has similar behavior to feof(). Returns a true after the first read operation that attempts to read past the end of the file. It returns false if the current position is not end of file.
		virtual S_UINT64		Length()const;				///< returns the length of the file...
		virtual bool			ChangeSize(S_UINT64 nSize);	///< Lengthens or shortens the file to the specified size...use with caution
		virtual bool			IsBuffered()const;			///< Return true if this object is a "memory" object. This is/can-be used internally to decide whether or not to make a temporary buffer for reading and writing more quickly...

	protected:

		//bool					ReadAdditionalBlocks(const S_UINT64 nLen);

		void					LoadUpTo(S_UINT64 nPos);

		virtual bool			ReadInternal(S_UINT8 pData[], S_UINT64 nLen);
		virtual bool			WriteInternal(const S_UINT8 pData[], S_UINT64 nLen);
		virtual void			Flush();

		S_UINT64						m_nFileLength;
		File							m_file;				///< File pointer
		S_UINT64						m_nBlockSize;		///< Block size to read at once

		class Block
		{
		public:
			Block()
			{
				m_bIsLoaded		= false;
				m_pBuffer		= NULL;
				m_nSize			= 0;
			}
			~Block()
			{
				DELETE_ARRAY( m_pBuffer );
			}
			bool			m_bIsLoaded;
			S_UINT8			*m_pBuffer;
			S_UINT64		m_nSize;
		};

		void EstablishIterator(S_UINT64 nPos);

		std::vector< Block >			m_vBlocks;			///< Memory blocks
		S_UINT64						m_nFilePointer;		///< Index into whole file

		/// Iterator info
		S_UINT8							*m_pPointer;
		S_UINT64						m_nCurrentBlockRemaining;	///< Remaining number of bytes in the current block
		S_UINT64						m_nCurrentBlock;			///< Current block index

		S_UINT64						m_nMaxLoadBlock;			///< Max loaded block

		bool							m_bIsEof;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef MemoryBlockFile_MethodB		MemoryBlockFile;

}//namespace SDICOS

#endif