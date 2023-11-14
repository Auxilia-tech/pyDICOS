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
#ifndef _STRATOVAN_DICOS_IMEMORYFILE_H__
#define _STRATOVAN_DICOS_IMEMORYFILE_H__

#include "SDICOS/IFile.h"
//#include "MD5.h"

namespace SDICOS
{

	class IMemoryFile	: public IFile
	{
	public:
		IMemoryFile()			{}
		virtual ~IMemoryFile()	{}

		virtual bool		OpenReading(const std::string &strLabel)					{ return Open(Filename(strLabel), IFile::enumReading); }
		virtual bool		OpenWriting(const std::string &strLabel)					{ return Open(Filename(strLabel), IFile::enumWriting); }
		virtual bool		OpenReadingWriting(const std::string &strLabel)				{ return Open(Filename(strLabel), IFile::enumReadingWriting); }

		virtual bool		GrowToSafe(S_UINT64 nSize) = 0;	// Preserves contents in the current buffer...
		virtual bool		IsBuffered()const						{return true;}

		typedef enum
		{
			enumBlockVersion1		= 0x100,
			enumCurrentBlockVersion	= enumBlockVersion1,
		}BLOCKVERSION;

		virtual bool	CompressByBlock(IMemoryFile &output, S_UINT64 nRecommendedBlockSize = 2<<24)const								= 0;	///< Compress this object (nMaxBlockSize bytes at a time) and places the results in output
		virtual bool	UncompressByBlock(IMemoryFile &output, int nOutputSize = -1)const	= 0;	///< Uncompress this object (nMaxBlockSize bytes at a time) and place the results in output, if the output size is known (saved using some other mechanism) please specify it here, otherwise a -1 indicates that a memory buffer of at least twice the size as the input buffer will be allocated (and possibly re-allocated if it's too small, which could slow things down).

		virtual bool	WriteInto(IFile &file)const						= 0;
		virtual bool	ReadFrom(IFile &file, S_UINT64 nLength)	= 0;

		//virtual bool	ComputeMD5(MD5 &md5)const				= 0;	///< Computes the md5 hash on the whole memory file

		virtual int		Compare(IMemoryFile &memfile);

	protected:

		// Hide copying...
		IMemoryFile(const IMemoryFile &obj) : IFile(obj)	{}
		IMemoryFile(const IFile &obj)		: IFile(obj)	{}
		IMemoryFile& operator=(const IFile &obj)			{if(this == &obj)return *this; IFile::operator=(obj); return *this;}
		IMemoryFile& operator=(const IMemoryFile &obj)		{if(this == &obj)return *this; IFile::operator=(obj); return *this;}

		virtual void	Flush()																		{}
	};

}	// namespace SDICOS


#endif

///	\file
/// Use for memory-resident files.
///








