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
#ifndef _STRATOVAN_DICOS_DICOS_FILE_H_
#define _STRATOVAN_DICOS_DICOS_FILE_H_

#include "SDICOS/File.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/ErrorLog.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/MemoryFile.h"
#include "SDICOS/Utils.h"
#include <set>

namespace SDICOS
{

	typedef bool (*PFN_PROGRESS_CALLBACK)(int nPos, int nMax, const char *pstrStatus, void *pHint);

///
/// \class DicosFileListing
/// \brief Searches for DICOS files and sorts them according to the hierarchy: "Object Of Inspection > Scan > Series"
///
class DicosFileListing
{
public:

	///
	/// \class SopInstance
	/// \brief Stores file names associated with a SOP Instance UID
	///
	class SopInstance
	{
	public:
		/// Initialize with default values
		SopInstance();
		/// Initialize with another SopInstance
		SopInstance(const SopInstance &instance);
		/// Destructor
		~SopInstance();

		/// Copy operator
		SopInstance& operator=(const SopInstance& instance);

		/// Comparison operator
		bool operator==(const SopInstance& instance)const;
		/// Comparison operator
		bool operator!=(const SopInstance& instance)const;

		/// Bracket operator to access file names
		const Filename& operator[](S_UINT64 n)const;

		/// Reset to default values
		void FreeMemory();

		/// Returns true if the SOP instance has a CT class UID
		bool IsCT()const;

		/// Returns true if the SOP instance has a DX class UID
		bool IsDX()const;

		/// Returns true if the SOP instance has a AIT2D class UID
		bool IsAIT2D()const;

		/// Returns true if the SOP instance has a AIT3D class UID
		bool IsAIT3D()const;

		/// Returns true if the SOP instance has a QR class UID
		bool IsQR()const;

		/// Returns true if the SOP instance has a TDR class UID
		bool IsTDR()const;

		/// Return the OOI Image Characteristic if the Modality supports Image-Type attributes
		/// @return Return enumUnknownOOIImageCharacteristics if the Modality does not support Image Type 
		DcsString GetOOIImageCharacteristic() const;

		///
		/// Matches SOP Instance UID (0008, 0018)
		///
		/// @param filename DICOS file name
		/// @param attribManager Manager with the attributes from the file 'filename'
		///
		bool AddFile(const Filename &filename, const AttributeManager &attribManager);

		/// Get file names associated with this SOP instance
		bool GetFilenames(Array1D<Filename> &arrayFilenames)const;

		/// Returns true if file is part of this SOP instance
		bool HasFile(const Filename &filename)const;

		/// Returns the number of file names
		S_UINT64 GetNumberOfFilenames()const;

		/// Get the SOP class UID (0008, 0016)
		DcsString GetSopClassUID()const;

		/// Get the SOP Instance UID (0008, 0018)
		DcsString GetUID()const;
	protected:
		class SopInstanceImpl;
		SopInstanceImpl *m_pSopInstanceImpl;
	};

	///
	/// \class Series
	/// \brief Stores file names associated with a series
	///
	class Series
	{
	public:
		///
		/// Initialize with default values
		///
		Series();

		///
		/// Initialize with another Series
		///
		Series(const Series &series);

		///
		/// Destructor
		///
		~Series();

		///
		/// Copy operator
		///
		Series& operator=(const Series& series);

		///
		/// Comparison operator
		///
		bool operator==(const Series& series)const;
		///
		/// Comparison operator
		///
		bool operator!=(const Series& series)const;

		///
		/// Bracket operator to access SOP Instance
		///
		const SopInstance& operator[](S_UINT64 n)const;

		///
		/// Reset to default values
		///
		void FreeMemory();

		////
		/// Matches Series Instance UID (0020, 000E)
		///
		/// @param filename DICOS file name
		/// @param attribManager Manager with the attributes from the file 'filename'
		///
		bool AddFile(const Filename &filename, const AttributeManager &attribManager);

		///
		/// Get SOP instances associated with this scan
		///
		bool GetInstances(Array1D<SopInstance> &arrayInstances)const;

		///
		/// Returns the number of SOP Instances
		///
		S_UINT32 GetNumberOfInstances()const;

		/// Returns true if the series contains a file with CT modality
		bool HasCT()const;
		/// Returns true if the series contains a file with DX modality
		bool HasDX()const;
		/// Returns true if the series contains a file with AIT 2D modality
		bool HasAIT2D()const;
		/// Returns true if the series contains a file with AIT 3D modality
		bool HasAIT3D()const;
		/// Returns true if the series contains a file with QR modality
		bool HasQR()const;
		/// Returns true if the series contains a file with TDR modality
		bool HasTDR()const;

		/// Structure for grouping files based on SOP instance UID
		typedef struct  
		{
			Array1D<Filename>	m_vFilenames;		///< Files associated with the SOP Instance UID
			DcsString			m_dsSopInstanceUID;	///< SOP Instance UID
			DcsString			m_dsSopClassUID;	///< SOP Class UID
		}SopInstanceFiles;

		/// Structure for grouping files based on SOP Class UID
		typedef struct
		{
			Array1D<SopInstanceFiles>	m_vSopInstances;	///< SOP Instances
			DcsString					m_dsSopClassUID;	///< SOP Class UID of all the SOP Instances in m_vSopInstances
			DcsString					m_dsModality;		///< Modality: CT, DX (Presentation), DX (Processing), AIT2D, AIT3D, QR, TDR
		}ModalityFiles;

		/// Get an array of file names organized by SOP Class UID
		void GetModalityFiles(Array1D<ModalityFiles> &vModalityFiles)const;

		/// Return the Modality in a human readable string
		/// @return the modality as a string or UNKNOWN
		DcsString GetModality() const;

		/// Get the series instance UID (0020, 000E)
		DcsString GetUID()const;

		/// Get the series date (0008, 0021)
		DcsString GetDate()const;

		/// Get the series time (0008, 0031)
		DcsString GetTime()const;

		/// Get the series description (0020, 103E)
		DcsString GetDescription()const;

	protected:
		class ImplSeries;
		ImplSeries	*m_pImplSeries; ///< Internal implementation
	};

	///
	/// \class Scan
	/// \brief Stores series associated with a scan
	///
	class Scan
	{
	public:
		///
		/// Initialize with default values
		///
		Scan();

		///
		/// Initialize with another Scan
		///
		Scan(const Scan &scan);

		///
		/// Destructor
		///
		~Scan();

		///
		/// Copy operator
		///
		Scan& operator=(const Scan& scan);

		///
		/// Comparison operator
		///
		bool operator==(const Scan& scan)const;
		///
		/// Comparison operator
		///
		bool operator!=(const Scan& scan)const;
		
		///
		/// Bracket operator to access series
		///
		const Series& operator[](S_UINT64 n)const;

		///
		/// Reset to default values
		///
		void FreeMemory();

		///
		/// Matches to the scan instance UID (0020, 000D), then to a series and adds the file name to it. If no match is found, a new series is created
		///
		/// @param filename DICOS file name
		/// @param attribManager Manager with the attributes from the file 'filename'
		///
		bool AddFile(const Filename &filename, const AttributeManager &attribManager);

		///
		/// Get series associated with this scan
		///
		bool GetSeries(Array1D<Series> &arraySeries)const;

		///
		/// Returns the number of series
		///
		S_UINT64 GetNumberOfSeries()const;

		///
		/// Returns the number of DICOS files with this Scan Instance UID
		/// All unique SOP Instance UIDs under the associated Series Ids
		///
		S_UINT64 GetNumberOfFiles()const;

		/// Get the scan instance UID (0020, 000D)
		DcsString GetUID()const;

		/// Get the scan description attribute (0008, 1030)
		DcsString GetScanDescription()const;

		/// Get the human readable scan ID (0020, 0010)
		DcsString GetID()const;

		/// Get the scan date (0008, 0020)
		DcsString GetDate()const;

		/// Get the scan time (0008, 0030)
		DcsString GetTime()const;


		/// Structure for grouping files based on Series Instance UID
		typedef struct
		{
			Array1D<Series::ModalityFiles>	m_vSeries;				///< Files organized by SOP Class UID
			DcsString						m_dsSeriesInstanceUID;	///< Series Instance UID
		}SeriesFiles;

		/// Get an array of file names organized by Series Instance UID
		void GetSeriesFiles(Array1D<SeriesFiles> &vSeriesFiles)const;
	protected:
		class ImplScan;
		ImplScan	*m_pImplScan; ///< Internal implementation
	};

	///
	/// \class ObjectOfInspection
	/// \brief Stores scans associated with an object of inspection
	///
	class ObjectOfInspection
	{
	public:
		///
		/// Initialize with default values
		///
		ObjectOfInspection();

		///
		/// Initialize with another ObjectOfInspection
		///
		ObjectOfInspection(const ObjectOfInspection &ooi);

		///
		/// Destructor
		///
		~ObjectOfInspection();

		///
		/// Copy operator
		///
		ObjectOfInspection& operator=(const ObjectOfInspection& ooi);

		///
		/// Comparison operator
		///
		bool operator==(const ObjectOfInspection& ooi)const;
		///
		/// Comparison operator
		///
		bool operator!=(const ObjectOfInspection& ooi)const;
		
		///
		/// Bracket operator to access scans
		///
		const Scan& operator[](S_UINT64 n)const;

		///
		/// Reset to default values
		///
		void FreeMemory();

		///
		/// Matches the OOI ID (0010, 0020), then to a scan and adds the file name to it. If no match is found, a new scan is created
		///
		bool AddFile(const Filename &filename, const AttributeManager &attribManager);

		///
		/// Get scans associated with this object of inspection
		///
		bool GetScans(Array1D<Scan> &arrayScans)const;

		///
		/// Returns the number of scans
		///
		S_UINT64 GetNumberOfScans()const;

		///
		/// Returns the number of files
		///
		S_UINT64 GetNumberOfFiles()const;

		///
		/// Returns the OOI ID (0010, 0020)
		///
		DcsString GetUID()const;

		///
		/// Returns the OOI Type (4010, 1042)
		///
		DcsString GetOOIType()const;

		/// Structure for grouping files based on Scan Instance UID
		typedef struct
		{
			Array1D<Scan::SeriesFiles>	m_vScan;				///< Files organized by Series Instance UID and SOP Class UID
			DcsString					m_dsScanInstanceUID;	///< Scan Instance UID
		}ScanFiles;

		/// Get an array of file names organized by Scan Instance UID, Series Instance UID, and SOP Class UID
		void GetScanFiles(Array1D<ScanFiles> &vScanFiles)const;
	protected:
		class ImplObjectOfInspection;
		ImplObjectOfInspection	*m_pImplObjectOfInspection; ///< Internal implementation
	};

	///
	/// Initialize with default values
	///
	DicosFileListing();
	///
	/// Initialize with another DicosFileListing object
	///
	DicosFileListing(const DicosFileListing &filelisting);
	///
	/// Destructor
	///
	~DicosFileListing();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Cancel searching
	///
	void Cancel();

	///
	/// Copy operator
	///
	DicosFileListing& operator=(const DicosFileListing &filelisting);

	///
	/// Comparison operator
	///
	bool operator==(const DicosFileListing &filelisting)const;
	///
	/// Comparison operator
	///
	bool operator!=(const DicosFileListing &filelisting)const;

	///
	/// Bracket operator to access ObjectOfInspection objects
	///
	const ObjectOfInspection& operator[](S_UINT64 n)const;

	///
	/// Find DICOS files from the array provided
	///
	/// @param arrayFilenames Array of file names to examine
	/// @param arrayErrorLog Array of DICOS files omitted from the listing with their associated error log
	/// @param setIncludeFileExtensions Set of file extensions to include in search. By default files with no extension or files with ".dcs" or ".dicos" extensions are searched.
	/// @param bExcludeDicosVerification Set to true to exclude an attribute lookup for DICOS verification
	/// @param bFromOpticalDrive Whether or not the files are coming from an optical drive, default to false.
	/// @param pfnProgress Function pointer for progress callback, default to NULL
	/// @param pHint Pointer to hint, parameter for pfnProgress, default to NULL
	bool FindDicosFiles(const Array1D<Filename> &arrayFilenames, 
						Array1D<std::pair<Filename, ErrorLog> > &arrayErrorLog,
						const std::set<std::string> &setIncludeFileExtensions = std::set<std::string>(),
						const bool bExcludeDicosVerification = false,
						const bool bFromOpticalDrive = false,
						PFN_PROGRESS_CALLBACK pfnProgress = NULL, void *pHint = NULL);

	///
	/// Find DICOS files in a folder and subfolders
	///
	/// @param folder Folder to search
	/// @param bSearchSubfolders true: Search subfolders for DICOS files
	/// @param arrayErrorLog Array of DICOS files omitted from the listing with their associated error log
	/// @param setIncludeFileExtensions Set of file extensions to include in search. By default files with no extension or files with ".dcs" or ".dicos" extensions are searched.
	/// @param bExcludeDicosVerification Set to true to exclude an attribute lookup for DICOS verification
	/// @param bFromOpticalDrive Whether or not the files are coming from an optical drive, default to false.
	/// @param pfnProgress Function pointer for progress callback, default to NULL
	/// @param pHint Pointer to hint, parameter for pfnProgress, default to NULL
	bool FindDicosFiles(const Folder &folder, const bool bSearchSubfolders, 
						Array1D<std::pair<Filename, ErrorLog> > &arrayErrorLog,
						const std::set<std::string> &setIncludeFileExtensions = std::set<std::string>(),
						const bool bExcludeDicosVerification = false,
						const bool bFromOpticalDrive = false,
						PFN_PROGRESS_CALLBACK pfnProgress = NULL, void *pHint = NULL);

	///
	/// Get all the objects of inspection
	///
	bool GetObjectsOfInspection(Array1D<ObjectOfInspection> &arrayObjects)const;

	/// Get number of objects of inspection
	S_UINT64 GetNumberOfObjectOfInspections()const;

	typedef struct  
	{
		Filename	m_filename;

		DcsString	m_dsSopInstanceUID;
		DcsString	m_dsSopClassUID;
		DcsString	m_dsSeriesInstanceUID;
		DcsString	m_dsScanInstanceUID;
		DcsString	m_dsOOIInstanceUID;
	}FileInfo;

	/// Get the number of files
	S_UINT32 GetNumberOfFiles()const;

	/// Get array of information for each file
	/// @return Returns true if one or more files were found.
	bool GetFileInfo(Array1D<FileInfo> &arrayFiles)const;

	/// Structure for grouping files based on OOI ID
	typedef struct
	{
		Array1D<ObjectOfInspection::ScanFiles>	m_vOOI;		///< Files organized by Scan Instance UID, Series Instance UID, and SOP Class UID
		DcsString					m_dsOOIID;				///< Object of Inspection ID
	}OOIFiles;

	/// Get an array of file names organized by OOI ID, Scan Instance UID, Series Instance UID, and SOP Class UID
	void GetOOIFiles(Array1D<OOIFiles> &vOOIFiles)const;

	/// Structure for holding files of the same SOP Instance and
	/// includes all other hierarchical UID's
	typedef struct  
	{
		Array1D<Filename>	m_vFilenames;	///< Files associated with SOP Instance

		DcsString	m_dsSopInstanceUID;		///< SOP Instance UID
		DcsString	m_dsSopClassUID;		///< SOP Class UID
		DcsString	m_dsModality;			///< Modality
		DcsString	m_dsSeriesInstanceUID;	///< Series Instance UID
		DcsString	m_dsScanInstanceUID;	///< Scan Instance UID
		DcsString	m_dsOOIID;				///< OOI ID
	}SopInstanceFiles;

	/// Get an array of SOP Instance Files
	void GetSopInstanceFiles(Array1D<SopInstanceFiles> &vSopInstances);

	/// Returns the SOP Instance UID of the scan that contains the specified filename
	bool GetSopInstanceUID(const SDICOS::Filename &filename, DcsString &dsSopInstanceUID)const;

protected:
	class ImplDicosFileListing;
	ImplDicosFileListing *m_pImplDicosFileListing; ///< Internal implementation
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///
/// \class DicosFile
/// \brief Writes/Reads DICOS file
///
class DicosFile
{
public:
	/// Enumerations for transfer syntaxes
	typedef enum
	{
		enumLittleEndianExplicit, ///< No compression. [Little endian explicit VR (1.2.840.10008.1.2.1)]
		enumLittleEndianExplicitExtended, ///< No compression. Supports storing pixel data over 4GB. [Little endian explicit VR Extended (1.2.840.10008.1.2.1.64)]
		enumLittleEndianImplicit, ///< No compression. [Little endian implicit VR (1.2.840.10008.1.2)]
		enumLosslessJPEG, ///< Lossless compression. [Little endian explicit, JPEG Lossless Compression, Non-Hierarchical, First-Order Prediction, Process 14, Selection Value 1 (1.2.840.10008.1.2.4.70)]
		enumLosslessRLE, ///< Lossless RLE compression. [Little endial explicit, RLE lossless compression as described in DICOM Part 5 Chapter G. (1.2.840.10008.1.2.5)]
	}TRANSFER_SYNTAX;

	/// Returns the DICOS file extension ".dcs"
	static const char* GetExtension();

	/// Get a transfer syntax
	/// @param nSyntax Transfer syntax enumeration
	/// @param str Output transfer syntax
	/// @return Returns true if transfer syntax enumeration is valid
	static bool GetTransferSyntax(const DicosFile::TRANSFER_SYNTAX nSyntax, DcsUniqueIdentifier &str);

	///
	/// Read a DICOS file
	///
	/// @param filename File name of DICOS file
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param bEndOnPixelData true: Stop reading file once pixel data is found
	/// @param bExcludeDicosVerification Set to true to exclude an attribute lookup for DICOS verification
	/// 
	static bool Read(const Filename &filename, ErrorLog &errorlog, 
					AttributeManager& attribmanager, const bool bEndOnPixelData = false, 
					const bool bExcludeDicosVerification = false);

	///
	/// Read a DICOS file from buffer
	///
	/// @param membuffer Memory buffer with DICOS data
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param bEndOnPixelData true: Stop reading file once pixel data is found
	/// @param bExcludeDicosVerification Set to true to exclude an attribute lookup for DICOS verification
	/// 
	static bool Read(MemoryBuffer &membuffer, ErrorLog &errorlog, 
					AttributeManager& attribmanager, const bool bEndOnPixelData = false, 
					const bool bExcludeDicosVerification = false);

	///
	/// Read a DICOS file from buffer
	///
	/// @param memfile Memory file with DICOS data. Length() should equal the exact size of the buffer containing the DICOS data
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param bEndOnPixelData true: Stop reading file once pixel data is found
	/// @param bExcludeDicosVerification Set to true to exclude an attribute lookup for DICOS verification
	/// 
	static bool Read(MemoryFile &memfile, ErrorLog &errorlog, 
					AttributeManager& attribmanager, const bool bEndOnPixelData = false, 
					const bool bExcludeDicosVerification = false);

	///
	/// Read a DICOS file from an optical drive.
	///
	/// @param filename File name of DICOS file
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param bIsForFileListing Whether or not to read for file listing, default to false
	static bool ReadFromOpticalDrive(const Filename &filename, ErrorLog &errorlog, AttributeManager& attribmanager, const bool bIsForFileListing = false);

	///
	/// Partially read a DICOS file until enough data is found for the DicosFileListing class
	///
	/// @param file File pointer to DICOS file
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	///
	static bool ReadForFileListing(IFile &file, ErrorLog &errorlog, AttributeManager& attribmanager);

	///
	/// Read a DICOS file from buffer in format for DICOS network protocol (i.e. C-Store)
	///
	/// @param membuffer Memory buffer with DICOS data
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param strTransferSyntax Transfer syntax of DICOS data
	/// 
	static bool ReadForNetworkProtocol(MemoryFile &membuffer, ErrorLog &errorlog, AttributeManager& attribmanager, const DcsString &strTransferSyntax);

	///
	/// Write a DICOS file.  Sets extensions to ".dcs" if needed.
	///
	/// @param filename File name of DICOS file
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param nSyntax Specify the transfer syntax to use.  Defaults to JPEG lossless compression.
	/// 
	static bool Write(const Filename &filename, ErrorLog &errorlog, AttributeManager& attribmanager, const DicosFile::TRANSFER_SYNTAX nSyntax = enumLosslessJPEG);
	
	///
	/// Write a DICOS file to a memory buffer
	///
	/// @param membuffer Output memory buffer
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param nSyntax Specify the transfer syntax to use.  Defaults to JPEG lossless compression.
	/// 
	static bool Write(MemoryBuffer &membuffer, ErrorLog &errorlog, AttributeManager& attribmanager, const DicosFile::TRANSFER_SYNTAX nSyntax = enumLosslessJPEG);

	///
	/// Write a DICOS file to a memory file
	///
	/// @param memfile Output memory file
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param nSyntax Specify the transfer syntax to use.  Defaults to JPEG lossless compression.
	/// 
	static bool Write(MemoryFile &memfile, ErrorLog &errorlog, AttributeManager& attribmanager, const DicosFile::TRANSFER_SYNTAX nSyntax = enumLosslessJPEG);

	///
	/// Write DICOS data to a memory buffer for DICOS network protocol (i.e. C-Store)
	///
	/// @param membuffer Output memory buffer
	/// @param errorlog Error log
	/// @param attribmanager Output attribute manager
	/// @param nSyntax Specify the transfer syntax to use.  Defaults to JPEG lossless compression.
	/// 
	static bool WriteForNetworkProtocol(MemoryFile &membuffer, ErrorLog &errorlog, AttributeManager& attribmanager, const DicosFile::TRANSFER_SYNTAX nSyntax = enumLosslessJPEG);

	///
	/// Returns true if DICOS version is V02
	///
	static bool IsSupportedDicosVersion(const AttributeManager& attribmanager);
	
	/// Returns true if the Class UID is CT
	static bool IsCT(const DcsString &strSopClassUID);
	/// Returns true if the Class UID is DX
	static bool IsDX(const DcsString &strSopClassUID);
	/// Returns true if the Class UID is QR
	static bool IsQR(const DcsString &strSopClassUID);
	/// Returns true if the Class UID is TDR
	static bool IsTDR(const DcsString &strSopClassUID);
	/// Returns true if the Class UID is AIT2D
	static bool IsAIT2D(const DcsString &strSopClassUID);
	/// Returns true if the Class UID is AIT3D
	static bool IsAIT3D(const DcsString &strSopClassUID);

protected:
	static bool SetupMetaInfo(AttributeManager &attribmanager, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CTModule;		///< Forward declaration
class DXModule;		///< Forward declaration
class AIT2DModule; 	///< Forward declaration
class AIT3DModule; 	///< Forward declaration
class QRModule;		///< Forward declaration
class TDRModule;	///< Forward declaration

class CT; 		///< Forward declaration
class DX; 		///< Forward declaration
class AIT2D; 	///< Forward declaration
class AIT3D; 	///< Forward declaration
class QR; 	///< Forward declaration
class TDR;		///< Forward declaration

/// \class IRetrieveCallback
/// \brief	Callback interface for loading DICOS files. Override the overloaded OnReceiveDicosFile(...) and 
///			OnReceiveDicosFileError(...) functions to receive callbacks.
class IRetrieveCallback
{
public:
	/// Called after a file fails to load
	void ReceiveDicosFileError(const Filename &filename, const ErrorLog &errorlog); 
	/// Called after a set of files fail to load
	void ReceiveDicosFileError(const Array1D<Filename> &vfilenames, const ErrorLog &errorlog); 

	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<AttributeManager> &manager, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<CTModule> &ct, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<DXModule> &dx, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<AIT2DModule> &ait2d, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<AIT3DModule> &ait3d, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<QRModule> &qr, const ErrorLog &errorlog); 
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<TDRModule> &tdr, const ErrorLog &errorlog); 

	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<CT> &ct, const ErrorLog &errorlog);
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<DX> &dx, const ErrorLog &errorlog);
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<AIT2D> &ait, const ErrorLog &errorlog);
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<AIT3D> &ait, const ErrorLog &errorlog);
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<QR> &qr, const ErrorLog &errorlog);
	/// Called after loading a DICOS file
	void ReceiveDicosFile(Utils::DicosData<TDR> &tdr, const ErrorLog &errorlog);

	/// Determine if loaded files must be DICOS
	bool LoadOnlyDICOS()const;

	/// Include a file extension to use while searching for files to load
	/// @param strExtension Notation used: ".extension"
	bool IncludeFileExtension(const std::string &strExtension);
	/// Returns true if the file extension is included
	/// @see IncludeFileExtension
	bool IsExtensionIncluded(const std::string &strExtension)const;

	std::set<std::string> m_setIncludeFileExtensions; ///< Add file extensions to include as potential DICOS files. Use ".extension" notation. 
protected:

	/// Override for callback function when errors occur and client session completes
	virtual void OnReceiveDicosFileError(const Filename &filename, const ErrorLog &errorlog) = 0;
	/// Override for callback function when a set of files fail to load
	virtual void OnReceiveDicosFileError(const Array1D<Filename> &vfilenames, const ErrorLog &errorlog) = 0; 

	/// [Tag-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AttributeManager> &manager, const ErrorLog &errorlog); 

	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<CTModule> &ct, const ErrorLog &errorlog); 
	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<DXModule> &dx, const ErrorLog &errorlog);
	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT2DModule> &ait2d, const ErrorLog &errorlog);
	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT3DModule> &ait3d, const ErrorLog &errorlog);
	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<QRModule> &qr, const ErrorLog &errorlog);
	/// [Module-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<TDRModule> &tdr, const ErrorLog &errorlog);

	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<CT> &ct, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<DX> &dx, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT2D> &ait, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT3D> &ait, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<QR> &qr, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<TDR> &tdr, const ErrorLog &errorlog);

	/// Default returns true. Override to return false and allow loading non-DICOS files.
	/// These files must have the same tag structure as DICOS
	virtual bool OnLoadOnlyDICOS()const;
};

class IODCommon;

/// \class SimpleRetrieveCallback
/// Store DICOS files by filename for later retrieval.
/// Only the [User-Level API] is supported.
/// QR is not supported
class SimpleRetrieveCallback : public IRetrieveCallback
{
public:
	SimpleRetrieveCallback();
	virtual ~SimpleRetrieveCallback();

	/// Get Original DICOS Data by filename
	/// @param pFilename Path to the loaded DICOS file used by the DICOS loader
	SDICOS::IODCommon* GetDICOSData(const char* pFilename);

	/// Get Original DICOS Data by filename
	/// @param pFilename Path to the loaded DICOS file used by the DICOS loader
	const SDICOS::IODCommon* GetDICOSData(const char* pFilename) const;

	/// Number of loaded files
	SDICOS::S_UINT32 GetNumDICOSFiles()const;

	/// Get original DICOS data by index
	/// @param iIndex Number in [0, GetNumDICOSiles())
	/// @return NULL if index is out of range
	SDICOS::IODCommon* GetDICOSData(const SDICOS::S_UINT32 iIndex);

	/// Get original DICOS data by index
	/// @param iIndex Number in [0, GetNumDICOSiles())
	/// @return NULL if index is out of range
	const SDICOS::IODCommon* GetDICOSData(const SDICOS::S_UINT32 iIndex)const;
	
protected:
	/// Override for callback function when errors occur and client session completes
	virtual void OnReceiveDicosFileError(const Filename &filename, const ErrorLog &errorlog);
	/// Override for callback function when a set of files fail to load
	virtual void OnReceiveDicosFileError(const Array1D<Filename> &vfilenames, const ErrorLog &errorlog);

	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<CT> &ct, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<DX> &dx, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT2D> &ait, const ErrorLog &errorlog);
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<AIT3D> &ait, const ErrorLog &errorlog);
	
	/// [User-Level API] Override for callback function when data is loaded 
	virtual void OnReceiveDicosFile(Utils::DicosData<TDR> &tdr, const ErrorLog &errorlog);

private:
	class SimpleRetrieveCallbackImpl;
	SimpleRetrieveCallbackImpl* m_pImpl;
};

/// \class DicosLoader
/// \brief Loads DICOS files from disk and returns loaded data through the callback interface
class DicosLoader
{
public:
	/// Constructor
	DicosLoader();
	/// Destructor
	~DicosLoader();

	/// Set the callback interface
	/// If the preferred API is set to Module-Level or User-Level API, the original Tag-Level (excluding pixel data) 
	/// data can be retrieved with DicosData::GetOriginalData() or DicosData::TakeOwnershipOriginal().
	void SetCallback(IRetrieveCallback *pcallback);

	/// Prefer User-Level API callback function. This is the default preference.
	void PreferUserLevelAPI();
	/// Prefer Module-Level API callback function
	void PreferModuleLevelAPI();
	/// Prefer Tag-Level API callback function
	void PreferTagLevelAPI();

	/// Load DICOS data using filename or folder
	/// Attempt to load as file and then folder
	/// @return true/false false if load fails as file and folder
	bool Load(const std::string& strFilenameOrFolder, const bool bSearchSubFolders = false, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a file name
	bool Load(const Filename &filename, const bool bFromOpticalDrive = false);
	/// Load DICOS data using an array of file names
	bool Load(const Array1D<Filename> &vfilenames, const bool bFromOpticalDrive = false);
	/// Load DICOS data from a folder and sub folders
	/// @param folder Folder to find DICOS files
	/// @param bSearchSubfolders true: Search sub folders for DICOS files
	/// @param bFromOpticalDrive Whether or not the file is coming from an optical drive, default to false
	bool Load(const Folder &folder, const bool bSearchSubfolders, const bool bFromOpticalDrive = false);

	/// Load DICOS data using a DicosFileListing::SopInstance object
	bool Load(const DicosFileListing::SopInstance &sopinstance, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::Series object
	bool Load(const DicosFileListing::Series &series, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::Scan object
	bool Load(const DicosFileListing::Scan &scan, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::ObjectOfInspection object
	bool Load(const DicosFileListing::ObjectOfInspection &ooi, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing object
	bool Load(const DicosFileListing &dfilelisting, const bool bFromOpticalDrive = false);

	/// Load DICOS data using a DicosFileListing::Series::SopInstanceFiles object
	bool Load(const DicosFileListing::Series::SopInstanceFiles &instancefiles, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::Series::ModalityFiles object
	bool Load(const DicosFileListing::Series::ModalityFiles &modfiles, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::Scan::SeriesFiles object
	bool Load(const DicosFileListing::Scan::SeriesFiles &seriesfiles, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::ObjectOfInspection::ScanFiles object
	bool Load(const DicosFileListing::ObjectOfInspection::ScanFiles &scanfiles, const bool bFromOpticalDrive = false);
	/// Load DICOS data using a DicosFileListing::OOIFiles object
	bool Load(const DicosFileListing::OOIFiles &ooi, const bool bFromOpticalDrive = false);

	/// Load DICOS data using a DicosFileListing object and specify through ID's and UID's the data to load. 
	/// Set ID strings to filter the data to load. To ignore an ID for loading, set it to an empty string.
	/// Example: Load(dfilelisting, "1.1.1", "", "3.3.3") will load all files with OOI ID "1.1.1" and series instance UID "3.3.3".
	/// Example: Load(dfilelisting, "", "", "", "4.4.4") will load all files with a SOP class UID "4.4.4".
	/// @param dfilelisting List of all DICOS files
	/// @param dsOOIID Object of inspection ID of data to load. Load all object of inspections by leaving the string empty.
	/// @param dsScanInstanceUID Scan instance UID of data to load. Load all scans by leaving the string empty.
	/// @param dsSeriesInstanceUID Series instance UID of data to load. Load all series by leaving the string empty.
	/// @param dsSopClassUID SOP class UID of data to load. Load all SOP class UID's by leaving the string empty.
	/// @param dsSopInstanceUID SOP instance UID of data to load. Load all SOP instances by leaving the string empty.
	/// @param bFromOpticalDrive Whether or not the file is coming from an optical drive, default to false
	bool Load(	const DicosFileListing &dfilelisting, 
		const DcsString &dsOOIID, 
		const DcsString &dsScanInstanceUID = "",
		const DcsString &dsSeriesInstanceUID = "",
		const DcsString &dsSopClassUID = "",
		const DcsString &dsSopInstanceUID = "", 
		const bool bFromOpticalDrive = false);

	/// Load DICOS data using a DicosFileListing::OOIFiles object and specify through ID's and UID's
	/// the data to load. 
	/// Set ID strings to filter the data to load. To ignore an ID for loading, set it to an empty string.
	/// Example: Load(vOOIFiles, "1.1.1", "", "3.3.3") will load all files with OOI ID "1.1.1" and series instance UID "3.3.3".
	/// Example: Load(vOOIFiles, "", "", "", "4.4.4") will load all files with a SOP class UID "4.4.4".
	/// @param vOOIFiles List of all DICOS files
	/// @param dsOOIID Object of inspection ID of data to load. Load all object of inspections by leaving the string empty.
	/// @param dsScanInstanceUID Scan instance UID of data to load. Load all scans by leaving the string empty.
	/// @param dsSeriesInstanceUID Series instance UID of data to load. Load all series by leaving the string empty.
	/// @param dsSopClassUID SOP class UID of data to load. Load all SOP class UID's by leaving the string empty.
	/// @param dsSopInstanceUID SOP instance UID of data to load. Load all SOP instances by leaving the string empty.
	/// @param bFromOpticalDrive Whether or not the file is coming from an optical drive, default to false	
	bool Load(	const Array1D<DicosFileListing::OOIFiles> &vOOIFiles, 
				const DcsString &dsOOIID, 
				const DcsString &dsScanInstanceUID = "",
				const DcsString &dsSeriesInstanceUID = "",
				const DcsString &dsSopClassUID = "",
				const DcsString &dsSopInstanceUID = "", 
				const bool bFromOpticalDrive = false);

	/// Load DICOS data using a memory buffer. The memory buffer must only contain a single DICOS file.
	/// @param memfile Memory buffer to read from
	bool Load(MemoryFile &memfile);

	/// Provide allocator functions for custom Module-Level or User-Level API
	/// @param apiAllocators Set of pointers to allocation functions
	void SetCustomAllocators(const SDICOS::Utils::APIAllocators &apiAllocators);

	/// Provide a memory manager for allocating & deallocating memory for the pixel data.
	/// The DICOS library will internally use the memory manager's allocator for each slice. When the pixel
	/// data is to be deleted, the SDK will use the memory manager's deallocator for each slice.
	void SetMemoryManager(IMemoryManager *pMemMgr);
	/// @see SetMemoryManager
	IMemoryManager* GetMemoryManager();
protected:
	/// Disabled
	DicosLoader(const DicosLoader &loader);

	/// Disabled
	DicosLoader& operator=(const DicosLoader &loader);

	class DicosLoaderImpl;
	DicosLoaderImpl	*m_pDicosLoaderImpl;
};

}//namespace SDICOS

#endif
