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
// This example scans a folder and all its sub folders for DICOS files, retrieves all the files in a hierarchy,
// then prints the retrieved information to screen
//
#include "SDICOS/DICOS.h" // DICOS include file
#include <iostream>

int main()
{
	SDICOS::DicosFileListing dFileListing;	// Finds DICOS files
	SDICOS::Array1D<SDICOS::DicosFileListing::SopInstanceFiles> vFiles; // Organized DICOS files from SDICOS::DicosFileListing
	const SDICOS::DicosFileListing::SopInstanceFiles *pSOP = NULL; // SOP instance reference
	SDICOS::Folder			folder;			// Folder object
	SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLog;	// List of DICOS files with errors
	bool bRes(true);

	// Set the folder with DICOS files
	folder.GetCurrentWorkingFolder();
	folder.Set(folder.GetFullFolder() + "../DataFiles");

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
		bRes = false;
	}

	// Get a list of all DICOS files organized in a hierarchy of OOI > Scan > Series > SOP Class
	dFileListing.GetSopInstanceFiles(vFiles);

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

	return (bRes ? 0 : 1);
}