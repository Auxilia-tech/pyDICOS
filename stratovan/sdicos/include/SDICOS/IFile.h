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
#ifndef _STRATOVAN_DICOS_IFILE_H_
#define _STRATOVAN_DICOS_IFILE_H_

#include <string>
#include <map>

#include "SDICOS/FileSystem.h"
#include "SDICOS/Types.h"
#include "SDICOS/MemoryBuffer.h"

namespace SDICOS
{

	///
	/// \class IFile
	/// Describes an interface for reading and writing to files
	///
	class IFile
	{
	public:
		IFile();
		virtual ~IFile();

		typedef unsigned int	FORMAT_HANDLE;				///< Used for format instrumentation...
		typedef unsigned int	FORMAT_VALUE_HANDLE;		///< Used for format instrumentation...

		/// Enumeration for Opening files
		typedef enum
		{
			enumUnknown			= 0x0,		///< An un-initialized state, cannot pass to Open(), but may be returned by GetOpenType()
			enumReading			= 0x1,		///< Open a file for read-only access
			enumWriting			= 0x2,		///< Open a file for write-only access
			enumReadingWriting	= 0x3		///< Open a file for read-write access
		}OPEN_TYPE;
		virtual bool		Open(const Filename &filename, OPEN_TYPE nType);				///< Opens a file for the specified access
		virtual bool		Close();															///< Close the file
		OPEN_TYPE			GetOpenType()const;													///< What access is available?
		inline bool			CanRead()const			{return (m_nOpenType & enumReading) != 0;}	///< Can one read from the file?
		inline bool			CanWrite()const			{return (m_nOpenType & enumWriting) != 0;}	///< Can one write to the file?
		virtual bool		MakeCompatible(IFile *pFile)const;									///< This makes pFile use the same endian translation settings and also copies version information set using SetVersionType(), this is primarily used for creating memory buffers that can then be written directly to file...

		inline const Filename& GetFilename() const { return m_Filename; }

		/// Enumeration for Endian types
		typedef enum
		{
			enumLittleEndian,	///< Use(s) little endian data translation
			enumBigEndian		///< Use(s) big endian data translation
		}ENDIAN;
		void				SetFileEndian(ENDIAN nEndian);													///< Set a specified endian translation for this file
		ENDIAN				GetFileEndian()const;															///< Retrieve the current endian translation setting
		static ENDIAN		GetMachineEndian();																///< What endian is the particular machine we're using?
		virtual bool		ReadEndianData();																///< Reads the data written by WriteEndianData() and sets the internal state based on what's read and its relation to the machine were on
		virtual bool		WriteEndianData(const std::string &str, FORMAT_HANDLE *pEndianHandle = NULL);	///< Writes 4-bytes into the file 0x04030201 which, when read later on, can be used to determine what endian setting was used to write the file

		///////////////////////////////////////////
		// Versioning...
		virtual bool		SetVersionType(const std::string &strType, int nVersion);		///< Keeps track of version numbers for the specified object type.
		virtual void		RemoveVersionType(const std::string &strType);					///< Removes version info for the specified object type.
		virtual int			GetVersion(const std::string &strType)const;					///< Retrieve the version number for the given object type, returns -1 on error

		///////////////////////////////////////////
		// Reading/writing...
		bool Read(bool &Data);
		bool Read(char &Data);
		bool Read(S_UINT8 &Data);
		bool Read(S_INT8 &Data);
		bool Read(S_UINT16 &Data);
		bool Read(S_INT16 &Data);
		bool Read(S_UINT32 &Data);
		bool Read(S_INT32 &Data);
		bool Read(S_INT64 &Data);
		bool Read(S_UINT64 &Data);
		bool Read(float &Data);
		bool Read(double &Data);
		//bool Read(std::string &Data, int nMaxExpectedLength = -1);	///< nMaxExpectedLength refers to maximum expected size of string to detect length error in the file, -1 indicates to skip the error detection
		bool Read(char pData[], S_UINT64 nLen);
		bool Read(S_INT8 pData[], S_UINT64 nLen);
		bool Read(S_UINT8 pData[], S_UINT64 nLen);
		bool Read(bool pData[], S_UINT64 nLen);
		bool Read(S_INT16 pData[], S_UINT64 nLen);
		bool Read(S_UINT16 pData[], S_UINT64 nLen);
		bool Read(S_INT32 pData[], S_UINT64 nLen);
		bool Read(S_UINT32 pData[], S_UINT64 nLen);
		bool Read(S_INT64 pData[], S_UINT64 nLen);
		bool Read(S_UINT64 pData[], S_UINT64 nLen);
		bool Read(float pData[], S_UINT64 nLen);
		bool Read(double pData[], S_UINT64 nLen);

		bool Write(const char &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT8 &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT8 &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const bool &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT16 &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT16 &Data,				const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT32 &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL, FORMAT_VALUE_HANDLE hValueMap = 0);
		bool Write(const S_UINT32 &Data,				const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT64 &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT64 &Data,				const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const float &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const double &Data,					const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		//bool Write(const std::string &Data,				const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const char pData[],					S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT8 pData[],				S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT8 pData[],			S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const bool pData[],					S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT16 pData[],				S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT16 pData[],	S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT32 pData[],					S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT32 pData[],			S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_INT64 pData[],				S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const S_UINT64 pData[],				S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const float pData[],					S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);
		bool Write(const double pData[],				S_UINT64 nLen, const std::string &strDesc, FORMAT_HANDLE hLenHandle = 0, FORMAT_HANDLE *pHandle = NULL);

		////////////////////////////////////////////
		///  Primitive Vector
		template < typename TYPE > bool Read(std::vector< TYPE > &vData);
		template < typename TYPE > bool Write(const std::vector< TYPE > &vData,	const std::string &strDesc, FORMAT_HANDLE *phLenHandle = NULL, FORMAT_HANDLE *pHandle = NULL);
		
		///////////////////////////////////////////
		/// Text based IO
		bool ReadWord(std::string &strWord);					///< Assumes a "normal" word, i.e. separated by whitespace...
		bool ReadWord(std::string &strWord, char chSpace);		///< chSpace is the word separation character...this can be used for reading fields separated by some arbitrary char
		bool ReadLine(std::string &strLine);

		bool WriteWord(const std::string &strWord, const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);								///< word separation character is a space ' '
		bool WriteWord(const std::string &strWord, char chSpace, const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL);				///< chSpace is the word separation character...default is a space ' '
		bool WriteLine(const std::string &strLine, const std::string &strDesc, FORMAT_HANDLE *pHandle = NULL, bool bTerminateForPC = true);	///< bTerminateForPC ends the line with "\r\n" for PC and "\n" otherwise (i.e., MAC, UNIX, etc.)

		/// Enumeration for file seek options
		typedef enum
		{
			enumSet,
			enumEnd,
			enumCur
		}SEEK;
		virtual bool			Seek(S_INT64 nPos, SEEK nType)		= 0;
		virtual bool			SeekSet(S_INT64 nPos)				{return Seek(nPos, enumSet);}
		virtual bool			SeekFront()							{return Seek(0, enumSet);}
		virtual bool			SeekBack()							{return Seek(0, enumEnd);}
		virtual bool			SeekFromCurrent(S_INT64 nOffset)	{return Seek(nOffset, enumCur);}
		virtual S_UINT64		Tell()const							= 0;	///< Tell the position/offset of the file pointer
		virtual bool			IsEof()								= 0;	///< Whether or not we're at the end of the file. Has similar behavior to feof(). Returns a true after the first read operation that attempts to read past the end of the file. It returns false if the current position is not end of file.
		virtual S_UINT64		Length()const						= 0;	///< returns the length of the file...
		virtual bool			ChangeSize(S_UINT64 nSize)			= 0;	///< Lengthens or shortens the file to the specified size...use with caution
		virtual bool			IsBuffered()const					= 0;	///< Return true if this object is a "memory" object. This is/can-be used internally to decide whether or not to make a temporary buffer for reading and writing more quickly...

		/// Format Instrumentation... see UnitTestExampleWrite() example below.
		/// These methods are used to instrument reading/writing code
		/// to allow a file format object to capture the file format
		/// automatically.
		typedef enum
		{
			enumChar,
			enumUnsignedChar,
			enumBool,
			enumShortInt,
			enumUnsignedShortInt,
			enumInt,
			enumUnsignedInt,
			enumLong,
			enumUnsignedLong,
			enumFloat,
			enumDouble,
			enumInt64,
			enumUnsignedInt64
		}FORMAT_TYPE;
		virtual void WriteInstrumentation(FORMAT_TYPE nType, const std::string &str, FORMAT_HANDLE *pHandle, FORMAT_VALUE_HANDLE hValueMap);
		virtual void WriteInstrumentationArray(FORMAT_TYPE nType, S_UINT64 nLen, const std::string &str, FORMAT_HANDLE hLenHandle, FORMAT_HANDLE *pHandle);
		virtual void BeginSection(const std::string &str, FORMAT_HANDLE *pSectionHandle = NULL);
		virtual void EndSection(FORMAT_HANDLE hSectionHandle = 0);
		virtual void BeginLoop(const std::string &str, FORMAT_HANDLE hCountHandle, FORMAT_HANDLE *pLoopHandle = NULL);
		virtual void EndLoop(FORMAT_HANDLE hLoopHandle = 0);
		virtual void BeginLoopIteration(int nIteration = 0, FORMAT_HANDLE *pLoopIterationHandle = NULL);
		virtual void EndLoopIteration(FORMAT_HANDLE hLoopIterationHandle = 0);
		virtual void BeginObject(const std::string &str, FORMAT_HANDLE *pObjectHandle = NULL);
		virtual void EndObject(FORMAT_HANDLE hObjectHandle = 0);

		virtual bool IsFormatObject()const	{return false;}	// To determine if the object is capturing file format information...

		/// These methods are used to create a map of possible
		/// values for an integer written into the file.
		/// Useful for listing the possible enumerations of a value
		/// Note that these can only be used in conjunction with
		/// writing a single integer, see Write(int ...) above.
		/// The following create methods returns false if the specified identifier has already been created.
		virtual bool CreateIntegerValueMap(const std::string &strUniqueIdentifier, FORMAT_VALUE_HANDLE *pValueMap);			// Create an integer (how it's displayed) type map
		virtual bool CreateHexadecimalValueMap(const std::string &strUniqueIdentifier, FORMAT_VALUE_HANDLE *pValueMap);		// Create an hexadecimal (how it's displayed) type map
		virtual void AppendValueMap(FORMAT_VALUE_HANDLE hHandle, int nValue, const std::string &strDesc);

		virtual bool ReadIntoBuffer(IFile &buffer, S_UINT64 nLen)const;			///< Read into a buffer
		virtual bool WriteFromBuffer(IFile &buffer);							///< Seeks to the front of buffer then writes everything (buffer.Length() bytes) to this object. Bypasses file format capture
		virtual bool ReadIntoBuffer(S_UINT8 pBuffer[], S_UINT64 nLen)const;			///< Read into a buffer
		virtual bool WriteFromBuffer(const S_UINT8 pBuffer[], S_UINT64 nLen);	///< Bypasses file format capture

		//static bool UnitTestExampleRead(IFile &file);
		//static bool UnitTestExampleWrite(IFile &file);

	protected:

		///////////////////////////////////////////
		/// Byte swapping.
		typedef S_UINT8	(*PFNCONVERT1BYTE)(const S_UINT8 &nData);
		typedef S_UINT16	(*PFNCONVERT2BYTE)(const S_UINT16 &nData);
		typedef S_UINT32	(*PFNCONVERT4BYTE)(const S_UINT32 &nData);
		typedef S_UINT64	(*PFNCONVERT8BYTE)(const S_UINT64 &nData);
		typedef void	(*PFNCONVERT1BYTEREF)(S_UINT8 &nData);
		typedef void	(*PFNCONVERT2BYTEREF)(S_UINT16 &nData);
		typedef void	(*PFNCONVERT4BYTEREF)(S_UINT32 &nData);
		typedef void	(*PFNCONVERT8BYTEREF)(S_UINT64 &nData);

		///////////////////////////////////////////
		/// Reading/writing.
		virtual bool ReadInternal(S_UINT8  pData[], S_UINT64 nLen) = 0;
		virtual bool WriteInternal(const S_UINT8  pData[], S_UINT64 nLen) = 0;
		virtual void Flush() = 0;	// Mostly for enumReadingWriting to handle flushing data streams properly...

		/// Enumeration for file operations. Read/write files -- opened for both operations...
		typedef enum
		{
			enumUnkownOperation,
			enumReadOperation,
			enumWriteOperation
		}OPERATION;
		OPERATION	m_nLastOperation;
		void CheckFlush(OPERATION nCurrentOp);

		/// Hide copying.
		IFile(const IFile &obj){*this = obj;}
		IFile& operator=(const IFile &);

		OPEN_TYPE			m_nOpenType;
		Filename		m_Filename;
		ENDIAN				m_nFileEndian;

		std::map< std::string, int >	m_mapTypeVersion;

		bool					m_bNeedConvert;
		PFNCONVERT1BYTE			m_pfnConvert1Byte;
		PFNCONVERT2BYTE			m_pfnConvert2Byte;
		PFNCONVERT4BYTE			m_pfnConvert4Byte;
		PFNCONVERT8BYTE			m_pfnConvert8Byte;
		PFNCONVERT1BYTEREF		m_pfnConvert1ByteRef;
		PFNCONVERT2BYTEREF		m_pfnConvert2ByteRef;
		PFNCONVERT4BYTEREF		m_pfnConvert4ByteRef;
		PFNCONVERT8BYTEREF		m_pfnConvert8ByteRef;

		MemoryBuffer			m_TempBuffer;
	};

	class SaveFilePointer
	{
	public:
		SaveFilePointer(const IFile &file)
		{
			m_pFile		= &file;
			m_nAt		= file.Tell();
		}
		~SaveFilePointer()
		{
			if(m_pFile)
			const_cast< IFile* >(m_pFile)->SeekSet(m_nAt);
		}

	protected:
		SaveFilePointer(const SaveFilePointer &){}
		const IFile		*m_pFile;
		S_UINT64			m_nAt;
	};

	template < typename TYPE > bool IFile::Read(std::vector< TYPE > &vData)
	{
		bool			bRes(true);
		S_UINT64	nLen;
		vData.clear();

		bRes = bRes && Read(nLen);
		
		if(!bRes)		return false;
		if(0 == nLen)	return true;

		vData.resize(unsigned(nLen));
		for(S_UINT64 n(0) ; bRes && n < nLen ; ++n)
			bRes = bRes && Read(vData[(size_t)n]);

		return bRes;
	}

	template < typename TYPE > bool IFile::Write(const std::vector< TYPE > &vData,	const std::string &strDesc, FORMAT_HANDLE *phLenHandle, FORMAT_HANDLE *pHandle)
	{
		bool	bRes(true);
		const	S_UINT64 nLen(vData.size());

		BeginSection(strDesc, pHandle);
		bRes = Write(nLen, "Vector Length", phLenHandle) && bRes;
		for(S_UINT64 n(0) ; n < nLen ; ++n)
			bRes = Write(vData[(size_t)n], "Vector Item", NULL) && bRes;
		EndSection((NULL != pHandle) ? *pHandle : 0);

		return bRes;
	}

	///
	/// \class DummyFile
	/// Strictly for tallying the number of bytes written to a file. This class can only handle a straight sequence of write operations and tallys the number of bytes that would be written...
	///
	class DummyFile : public IFile
	{
	public:
		DummyFile()
		{
			m_nLen = m_nAt = 0;
			OpenWriting("");
		}

		void Reset()
		{
			m_nLen = m_nAt = 0;
		}
	
		virtual bool OpenWriting(const std::string &strLabel)					{ return Open(Filename(strLabel), IFile::enumWriting); }

		virtual bool ReadInternal(S_UINT8  pData[], S_UINT64 nLen)
		{
			S_ASSERT(0);
			return false;
		}

		virtual bool WriteInternal(const S_UINT8  pData[], S_UINT64 nLen) 
		{
			m_nAt	+= nLen;
			m_nLen	= (m_nAt > m_nLen) ? m_nAt : m_nLen;
			return true;
		}

		virtual void Flush()
		{
		}

		virtual bool			Seek(S_INT64 nPos, SEEK nType)
		{
			switch(nType)
			{
			default:
			case enumSet:	m_nAt = nPos; break;
			case enumEnd:	m_nAt = m_nLen + nPos; break;
			case enumCur:	m_nAt += nPos; break;
			}
			m_nLen	= (m_nAt > m_nLen) ? m_nAt : m_nLen;
			return true;
		}
		virtual S_UINT64		Tell()const
		{
			return m_nAt;
		}
		virtual bool			IsEof()
		{
			S_ASSERT(0);
			return false;
		}
		virtual S_UINT64		Length()const
		{
			return m_nLen;
		}
		virtual bool			ChangeSize(S_UINT64 nSize)
		{
			S_ASSERT(0);
			return false;
		}
		virtual bool			IsBuffered()const
		{
			S_ASSERT(0);
			return false;
		}

		S_UINT64	GetNumberOfBytesWritten()const	{ return m_nLen; }

	protected:
		S_UINT64 m_nAt, m_nLen;
	};

}// namespace SDICOS

#endif

///	\file
/// File interface supporting a variety of useful file-related things.
///








