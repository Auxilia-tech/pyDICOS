//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2020 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_ZIPARCHIVE_H__
#define _STRATOVAN_DICOS_ZIPARCHIVE_H__

#include "SDICOS/File.h"
#include "SDICOS/MemoryFile.h"

namespace SDICOS
{
	class ZipArchive
	{
	public:
		ZipArchive();
		virtual ~ZipArchive();

		bool	Open(const Filename &filename);	///< If the file exists, the zip archive will be opened. If the file does not exist, a new one will be created (which you can add files to).
		bool	Open(MemoryFile &file);

		IFile::OPEN_TYPE		GetOpenType()const;								///< What access is available? If the file cannot be opened for writing, then you can't add/remove files...

		typedef enum
		{
			enumNone			= 0x00,
			enumReadOnly		= 0x01,
			enumHidden			= 0x02,
			enumSystem			= 0x04,
			enumVolumeLabel		= 0x08,
			enumDirectory		= 0x10,
			enumArchive			= 0x20,
		}ATTRIBUTE_TYPE;

		int		GetNumberOfFiles()const;											///< Returns the number of files in the archive
		Filename GetFilename()const;											///< Gets zip archive's filename
		bool	GetFilename(int nFile, Filename &filename)const;				///< Gets the name of the file
		bool	IsFolder(int nFile)const;											///< Is this file a folder?
		bool	GetUncompressedFileSize(int nFile, int &nSizeUncompressed)const;	///< What's the uncompressed size of the file?
		bool	GetCompressedFileSize(int nFile, int &nSizeCompressed)const;		///< What's the compressed size of the file?
		bool	GetAttribute(int nFile, int &nAttr)const;							///< Retrieve the attribibutes for the file.

		bool	Get(int nFile, MemoryFile &memfile);											///< Uncompresses the file and puts the data into memfile
		bool	Add(MemoryFile &memfile, const Filename &filename, int nAttr = enumNone);	///< Adds a file to the archive. If the file already exists, it will be overwritten.
		bool	Remove(int nFile);
		int		Find(const Filename &filename)const;

		bool	ExtractAll(const Folder &folderOut);	///< Extract all files in archive to a folder.

		void	Close();

	protected:

		bool	ReadFileRecords();
		bool	WriteCentralDirectory();

		class ZipArchiveImpl;
		ZipArchiveImpl *m_pZipArchiveImpl;
	private:
		ZipArchive(const ZipArchive &za);
		ZipArchive& operator=(const ZipArchive &za);
	};
}


#endif

