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
//
// This example uses the SDICOS::DicosFileListing class to find all DICOS files in a folder and 
// only load specific AIT3D files using the SDICOS::DicosLoader class.
//
#include "SDICOS/DICOS.h" // DICOS include header
#include <iostream>

//
// This class derives from the callback interface and is used by the 
// DICOS loading object.
//
// Both versions of the OnReceiveDicosFileError(...) function must be overridden.
// Override the overloaded OnReceiveDicosFile(...) to receive callbacks when files are loaded.
//
class DicosLoadingCallback : public SDICOS::IRetrieveCallback
{
protected:
	virtual void OnReceiveDicosFileError(const SDICOS::Filename &filename, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFileError(const SDICOS::Array1D<SDICOS::Filename> &vfilenames, const SDICOS::ErrorLog &errorlog);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog);
};

int main(int argc, char* argv[])
{
	SDICOS::DicosLoader			dcsloader;		// DICOS loading class
	DicosLoadingCallback		dcscallback;	// Callback interface for passing loaded files
	SDICOS::DicosFileListing	dFileListing;	// Finds DICOS files
	SDICOS::Array1D<SDICOS::DicosFileListing::SopInstanceFiles> vFiles; // Organized DICOS files from SDICOS::DicosFileListing
	const SDICOS::DicosFileListing::SopInstanceFiles *pSOP = NULL; // SOP instance reference
	SDICOS::Folder				folder;			// Target folder to find DICOS files
	SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLog;	// List of DICOS files with errors

	if (1 == argc)
	{
		// Set the folder with DICOS files.
		// When compiled, this file is at ..\TSA\DICOS\Examples\DicosListingAndLoadingExample\DicosListingAndLoadingExample.cpp
		// And the data files are at ..\TSA\DICOS\Examples\DataFiles
		SDICOS::Filename thisFile(__FILE__);
		folder = thisFile.GetFullFolder();
		folder.Set(folder.GetFullFolder() + "../../DataFiles");
		std::cout << "Searching for DICOS files under " << folder.GetFullFolder() << std::endl;
	}
	else
	{
		folder.Set(std::string(argv[1]));
		std::cout << "Searching for DICOS files under " << folder.GetFullFolder() << std::endl;
	}

	// Find all DICOS files in the target folder and its sub folders. Any files DICOS files excluded from
	// the listing due to errors will populate the third parameter.  
	// By default, this will only check files
	// with no extension or a '*.dcs' extension. To list DICOS files with other extensions, pass a set
	// of case sensitive extensions (ie. ".dicos") to the fourth parameter.
	// To list non-DICOS files that share the same format, like DICOM, set the fifth parameter to 'true'.
	if(!dFileListing.FindDicosFiles(folder, true, vErrorLog))
	{
		std::cout<<"\nNo DICOS files found in "<<folder.GetFullFolder()<<std::endl;
		return 0;
	}

	// Print out error log of DICOS files that failed to be included in the listing
	for(SDICOS::S_UINT32 nError(0) ; nError < vErrorLog.GetSize() ; ++nError)
	{
		std::cout<<"Failed to list file \""<<vErrorLog[nError].first.GetName()<<"\"\n";
		std::cout<<"Error log:\n"<<vErrorLog[nError].second<<std::endl;
	}

	if (0 != vErrorLog.GetSize())
		return 2;

	// Set the preferred callback handler. User-Level API is set by default.
	// By default, this callback interface will only check files
	// with no extension or a '*.dcs' extension. To load DICOS files with other extensions, call
	// DicosLoadingCallback::IncludeFileExtension with a case sensitive extension (ie. ".dicos").
	// To load non-DICOS files that share the same format, like DICOM, add the override 
	// function "virtual bool OnLoadOnlyDICOS()const" to the callback interface and set 
	// the function to return 'false'.
	dcsloader.SetCallback(&dcscallback);
		
	// Set the preferred callback API. User-Level API is set by default.
	dcsloader.PreferUserLevelAPI();

	// Get a list of all DICOS files organized in a hierarchy of OOI > Scan > Series > SOP Class
	dFileListing.GetSopInstanceFiles(vFiles);

	if (0 == vFiles.GetSize())
	{
		return 3;
	}

	// Print out information about each SOP instance found in the target folder
	pSOP = vFiles.GetBuffer();
	for(SDICOS::S_UINT32 nSopInstance(0) ; nSopInstance < vFiles.GetSize() ; ++nSopInstance, ++pSOP)
	{
		std::cout<<"\n-------------------";
		std::cout<<"\nOOI ID: "<<pSOP->m_dsOOIID.Get();
		std::cout<<"\nScan Instance UID: "<<pSOP->m_dsScanInstanceUID.Get();
		std::cout<<"\nSeries Instance UID: "<<pSOP->m_dsSeriesInstanceUID.Get();
		std::cout<<"\nSOP Class UID: "<<pSOP->m_dsSopClassUID.Get();
		std::cout<<"\nSOP Instance UID: "<<pSOP->m_dsSopInstanceUID.Get();
		std::cout<<"\nModality: "<<pSOP->m_dsModality.Get();
		std::cout<<"\nNumber of Files: "<<pSOP->m_vFilenames.GetSize();
		for(SDICOS::S_UINT32 nSopInstanceFile(0); nSopInstanceFile < pSOP->m_vFilenames.GetSize(); ++nSopInstanceFile)
			std::cout<<"\n	"<<pSOP->m_vFilenames[nSopInstanceFile].GetFullPath().c_str();
		std::cout<<std::endl;
	}

	// Example code showing how to load files by ids.
	// The callback handler type is DicosLoadingCallback which is defined at the top of this file.
	//
	// Load all AIT3D DICOS files in SDICOS::DicosFileListing with 
	//		OOI ID = "001"
	//		Scan Instance UID = "1.1.1",
	//		Series instance UID = "2.2.2".
	if(dcsloader.Load(dFileListing, "001", "1.1.1", "2.2.2", SDICOS::SOPClassUID::GetAIT3D()))
	{
		std::cout << "\nSuccessfully loaded AIT3D DICOS files with OOI ID = 001, scan instance UID = 1.1.1 and series instance UID = 2.2.2" << std::endl;
	}

	return 0;
}

// This function is called when a DICOS file failed to load. The parameter 'filename' contains the file name
// of the file that failed to load. The parameter 'errorlog' contains all the errors and warnings encountered
// while loading the file.
void DicosLoadingCallback::OnReceiveDicosFileError(const SDICOS::Filename &filename, const SDICOS::ErrorLog &errorlog)
{
	// Print the name of the file name
	std::cout<<"\n-------------------";
	std::cout<<"\nError loading file "<<filename.GetFullPath();
	std::cout<<"\nError Log:\n";
	std::cout<<errorlog<<std::endl;

}

// This function is called when a set of DICOS files failed to load. This is invoked when the User-Level API
// is used by the DICOS loader. The parameter 'filename' contains the file name of the file that failed
// to load. The parameter 'errorlog' contains all the errors and warnings encountered while loading the file.
void DicosLoadingCallback::OnReceiveDicosFileError(const SDICOS::Array1D<SDICOS::Filename> &vfilenames, const SDICOS::ErrorLog &errorlog)
{
	SDICOS::S_UINT32 n(0);

	std::cout<<"\n-------------------";
	std::cout<<"\nError loading files: "<<std::endl;

	for(n = 0 ; n < vfilenames.GetSize() ; ++n)
		std::cout<<vfilenames[n].GetFullPath()<<std::endl;

	std::cout<<"\nError Log:\n";
	std::cout<<errorlog<<std::endl;
}

//
// The 'OnReceiveDicosFile()' functions serve as callback functions for passing in the loaded DICOS data as a parameter
//
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a CT DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ct->SendOverNetwork().
	SDICOS::ErrorLog errorlogNetwork;
	ct->SendOverNetwork(1000, "1.2.3", "SourceApp", "DestApp", errorlogNetwork);

	// Gain ownership of the CT object by calling ct.TakeOwnership()
	// and passing a pointer to a CT object.
	SDICOS::CT *pct = S_NULL;
	ct.TakeOwnership(pct);
	DELETE_POINTER(pct);
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a DX DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using dx->SendOverNetwork().
	// Gain ownership of the DX object by calling dx.TakeOwnership()
	// and passing a pointer to a DX object.
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a AIT2D DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ait->SendOverNetwork().
	// Gain ownership of the AIT2D object by calling ait.TakeOwnership()
	// and passing a pointer to a AIT2D object.
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a AIT3D DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ait->SendOverNetwork().
	// Gain ownership of the AIT3D object by calling ait.TakeOwnership()
	// and passing a pointer to a AIT3D object.
	std::cout << "OnReceiveDicosFile(SDICOS::AIT3D) SopInstanceUID: " << ait->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a QR DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using qr->SendOverNetwork().
	// Gain ownership of the QR object by calling qr.TakeOwnership()
	// and passing a pointer to a QR object.
	std::cout << "OnReceiveDicosFile(SDICOS::QR) SopInstanceUID: " << qr->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a TDR DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using tdr->SendOverNetwork().
	// Gain ownership of the TDR object by calling tdr.TakeOwnership()
	// and passing a pointer to a TDR object.
	std::cout << "OnReceiveDicosFile(SDICOS::TDR) SopInstanceUID: " << tdr->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
