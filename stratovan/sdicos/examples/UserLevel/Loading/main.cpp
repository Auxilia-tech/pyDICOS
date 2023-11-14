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
// StartDicosLoadingExample
//
// This example loads DICOS files from a folder using the DICOS loader and callback interface
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

int main()
{
	SDICOS::DicosLoader		dcsloader;		// DICOS loading class
	DicosLoadingCallback	dcscallback;	// Callback interface for passing loaded files
	SDICOS::Folder			folder;			// Folder object
	int retvar=0;

	// Set the folder with DICOS files
	folder.GetCurrentWorkingFolder();
	folder.Set(folder.GetFullFolder() + "../DataFiles/V03_Data/");

	// Set the callback function to use after each file is loaded.
	// By default, this callback interface will only check files
	// with no extension or a '*.dcs' extension. To load DICOS files with other extensions, call
	// DicosLoadingCallback::IncludeFileExtension with a case sensitive extension (ie. ".dicos").
	// To load non-DICOS files that share the same format, like DICOM, add the override 
	// function "virtual bool OnLoadOnlyDICOS()const" to the callback interface and set 
	// the function to return 'false'.
	dcsloader.SetCallback(&dcscallback);

	// Set the preferred callback API. User-Level API is set by default.
	dcsloader.PreferUserLevelAPI();

	std::cout << "Loading files from folder " << folder.GetFullFolder().c_str() << std::endl;
		
	// Find all the DICOS files in the target folder and all sub folders
	if(dcsloader.Load(folder, true))
	{
		std::cout<<"\nAll files loaded"<<std::endl;
	} else {
		std::cout<<"\nFailed to load all files"<<std::endl;
		retvar=1;
	}

	return retvar;
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
	std::cout << "OnReceiveDicosFile(SDICOS::CT) SopInstanceUID: " << ct->GetSopInstanceUID().Get() << " " << errorlog << std::endl;

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
	
	std::cout << "OnReceiveDicosFile(SDICOS::DX) SopInstanceUID: " << dx->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a AIT2D DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ait->SendOverNetwork().
	// Gain ownership of the AIT2D object by calling ait.TakeOwnership()
	// and passing a pointer to a AIT2D object.
	std::cout << "OnReceiveDicosFile(SDICOS::AIT2D) SopInstanceUID: " << ait->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
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
// EndDicosLoadingExample
