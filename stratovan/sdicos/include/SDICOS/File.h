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
#ifndef _STRATOVAN_DICOS_FILE_H_
#define _STRATOVAN_DICOS_FILE_H_

#include "SDICOS/IFile.h"
#include "SDICOS/FileSystem.h"
#include "SDICOS/Types.h"

namespace SDICOS
{

///
/// \class File
/// \brief Object for reading/writing a file on disk.
///
/// This version uses the low-level unbuffered file io interface, i.e., open, seek, etc. This
/// version CAN access files larger than 2GB
///
class File	: public IFile
{
public:
	File();
	virtual ~File();

	virtual bool		Open(const Filename &filename, OPEN_TYPE nType);
	virtual bool		OpenReading(const Filename &filename)	{ return Open(filename, IFile::enumReading); }
	virtual bool		OpenWriting(const Filename &filename)	{ return Open(filename, IFile::enumWriting); }
	virtual bool		OpenReadingWriting(const Filename &filename)	{ return Open(filename, IFile::enumReadingWriting); }
	virtual bool		Close();

	virtual bool		Seek(S_INT64 nPos, SEEK nType);
	virtual S_UINT64	Tell()const;
	virtual bool		IsEof();
	virtual S_UINT64	Length()const;
	virtual bool		ChangeSize(S_UINT64 nSize);
	virtual bool		IsBuffered()const				{return false;}

	int		GetFileHandle()	{return m_nFile;}

protected:

	/// Hide copying...
	File(const File&) : IFile() {}
	File(const IFile &) : IFile() {}

	/// Hide assignment
	void operator=(const IFile &){}
	void operator=(const File &){}

	virtual bool ReadInternal(S_UINT8  pData[], S_UINT64 nLen);
	virtual bool WriteInternal(const S_UINT8  pData[], S_UINT64 nLen);
	virtual void Flush();	// Mostly for enumReadingWriting to handle flushing data streams properly...

	int		m_nFile;
	bool	m_bIsEof;			///< End of file flag
};

}	// namespace SDICOS

#endif // _STRATOVAN_DICOS_FILE_H_









