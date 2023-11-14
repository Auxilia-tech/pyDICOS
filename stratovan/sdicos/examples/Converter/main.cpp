//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2018 Stratovan Corporation. All Rights Reserved.
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
/*

Example Overview
------------------
This example shows how to create a simple DICOS V03 converter to convert older DICOS files up to V02 for all modalities
using User-Level API within a callback class

 */

#include "SDICOS/DICOS.h" //Include for DICOS library
#include <iostream>

/*

The callback class for loading DICOS files. Loading the file into Module-Level or User-Level API automatically updates the
DICOS data to V03, which only leaves writing the file back out with *.dcs extension if it does not already have it.

*/
class Converter : public SDICOS::IRetrieveCallback
{
protected:

	// Error encountered while loading the file
	virtual void OnReceiveDicosFileError(const SDICOS::Filename &filename, const SDICOS::ErrorLog &errorlog)
	{
		//Print out file name and error log
		std::cout << "Error reading file: " << filename.GetFullPath() << std::endl << errorlog << std::endl;
	}

	// Error encountered while loading files
	virtual void OnReceiveDicosFileError(const SDICOS::Array1D<SDICOS::Filename> &vfilenames, const SDICOS::ErrorLog &errorlog)
	{
		std::cout << "Error reading files: " << std::endl;

		//Print out all file names
		for (SDICOS::S_UINT32 nFile(0); nFile < vfilenames.GetSize(); ++nFile)
			std::cout << vfilenames[nFile].GetFullPath() << std::endl;
		
		//Print out error log
		std::cout << errorlog << std::endl;
	}

	// Unknown modality encountered. Automatic conversion not possible.
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
	{
		std::cout << "Unable to determine modality of file: " << manager.GetOriginalDataFilename(0).GetFullPath() << std::endl;
	}

	// Templatized common write procedure for SDICOS::Utils::DicosData<> variables.
	// Sets the file extension to .dcs, then writes the file.
	template<typename DICOS_DATA>
	void WriteFile(DICOS_DATA &dcsData, const SDICOS::DicosFile::TRANSFER_SYNTAX nTransferSyntax)
	{
		SDICOS::Filename filename(dcsData.GetOriginalDataFilename(0)); //Copy original file name
		SDICOS::ErrorLog errorlog; //Error log for write function call

		filename.SetExtension(".dcs"); //Set DICOS file extension. Writing will fail if it is not present
		
		//Write file
		if (dcsData->Write(filename, errorlog, nTransferSyntax))
			std::cout << "Converted file saved to " << filename.GetFullPath() << std::endl;
		else
			std::cout << "Failed to save " << filename.GetFullPath() << std::endl << errorlog << std::endl;
	}

	//Saves converted file with lossless compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(ct, SDICOS::DicosFile::enumLosslessJPEG);
	}

	//Saves converted file with no compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(dx, SDICOS::DicosFile::enumLittleEndianExplicit);
	}

	//Saves converted file with no compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait2d, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(ait2d, SDICOS::DicosFile::enumLittleEndianExplicit);
	}

	//Saves converted file with lossless compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait3d, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(ait3d, SDICOS::DicosFile::enumLosslessJPEG);
	}

	//Saves converted file with no compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(qr, SDICOS::DicosFile::enumLittleEndianExplicit);
	}

	//Saves converted file with no compression
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
	{
		WriteFile(tdr, SDICOS::DicosFile::enumLittleEndianExplicit);
	}
};

/*

Converter function uses the converter callback class to convert an older DICOS file to a V03 DICOS file

*/
bool ConvertToV03()
{
	SDICOS::DicosLoader dcsLoader; //Variable for loading DICOS files with a provided callback class
	Converter converter; //Converter callback class
	SDICOS::Filename filename("../DataFiles/V02_Data/CT/CTUserAPI.dcs"); //Set the older DICOS file's name

	dcsLoader.SetCallback(&converter); //Set the callback class

	dcsLoader.PreferUserLevelAPI(); //Tell the loader to use the User-Level API callback functions (This is the default setting)

	return dcsLoader.Load(filename); //Load the file. The loader calls the overridden functions in the Converter class
}

int main()
{
	if(ConvertToV03())
		return 0;
	else
		return 1;
}