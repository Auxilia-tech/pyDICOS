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
#include "SDICOS/DICOS.h"

void NewBaseClassTags()
{
	SDICOS::AIT3DModule ait;

	//OOI Owner Module
	{
		ait.AllocateObjectOfInspectionOwner();
		SDICOS::ObjectOfInspectionOwnerModule *pOOIOwner = ait.GetObjectOfInspectionOwner();

		//OOI Owner Risk Score - A new optional tag to set a OOI Owner's risk score
		{
			SDICOS::S_INT16 nRiskScore(5);

			//Set the risk score
			pOOIOwner->SetOwnerRiskScore(nRiskScore);

			//Get the risk score
			nRiskScore = pOOIOwner->GetOwnerRiskScore();

			//Remove the Risk Score
			pOOIOwner->DeleteOwnerRiskScore();

			//Check if a risk score is present in ObjectOfInspectionOwnerModule. This is primarily
			//used after loading a DICOS file or receiving a DICOS file from a network transfer.
			if (pOOIOwner->HasOwnerRiskScore())
			{
				//Tag is present
				nRiskScore = pOOIOwner->GetOwnerRiskScore();
			}
			else
			{
				//Tag is not present
			}
		}
	}

	//Image Module
	{
		SDICOS::AIT3DTypes::AIT3DImage &image = ait.GetImage();

		//Image Origin - a new required tag to set the image's origin
		{
			//Set the image origin
			//Valid values are enumMachine, enumAugmented, and enumSynthetic
			//"MACHINE", "AUGMENTED", and "SYNTETHIC"
			SDICOS::ImageCommon::IMAGE_ORIGIN nOrigin(SDICOS::ImageCommon::enumMachine);
			image.SetImageOrigin(nOrigin);

			//Get the image origin
			nOrigin = image.GetImageOrigin();

			//Get the image origin as a string
			SDICOS::DcsString strOrigin = image.GetImageOriginAsString();
		}

		//Coordinate System - a new required tag to set the image's coordinate system
		{
			//Set the coordinate system
			//Valid values are enumLHS and enumRHS
			//"LHS" and "RHS"
			SDICOS::ImageCommon::IMAGE_COORDINATE_SYSTEM nCoordinateSystem(SDICOS::ImageCommon::enumLHS);
			image.SetCoordinateSystem(nCoordinateSystem);

			//Get the coordinate system
			nCoordinateSystem = image.GetCoordinateSystem();

			//Get the coordinate system as a string
			SDICOS::DcsString strCoordinateSystem = image.GetCoordinateSystemAsString();
		}
	}
}
///EndNewBaseClassTags

void TipImageFeatures()
{
	SDICOS::AIT3DModule ait;
	ait.AllocateTipImage();
	SDICOS::TipImage* tipImage = ait.GetTipImage();

	/*
	* TIP Library Name - a new optional tag to set the TIP library name
	*/
	{
		//Set the library name
		tipImage->SetTipLibraryName("EXAMPLE LIBRARY NAME");
		
		//Check if the library name is set, if it is get it
		if(tipImage->HasTipLibraryName())
		{
			SDICOS::DcsShortText strLibraryName;
			strLibraryName = tipImage->GetTipLibraryName();	
		}

		//Delete the library name
		tipImage->DeleteTipLibraryName();
	}

	/*
	* TIP Image Identifier - a new optional tag to set the TIP Image Identifier
	*/
	{
		//Set the image identifier
		tipImage->SetTipImageIdentifier("EXAMPLE IMAGE IDENTIFIER");
		
		//Check if the image identifier is set, if it is get it
		if(tipImage->HasTipImageIdentifier())
		{
			SDICOS::DcsShortText strImageIdentifier;
			strImageIdentifier = tipImage->GetTipImageIdentifier();	
		}

		//Delete the library name
		tipImage->DeleteTipImageIdentifier();
	}

	/*
	* TIP Library Date - a new optional tag to set the TIP Library Date
	*/
	{
		SDICOS::DcsDateTime dtLibraryDate;
		dtLibraryDate.SetNow();

		//Set the library date
		tipImage->SetTipLibraryDate(dtLibraryDate);

		//Check if the library date is set, if it is get it
		if(tipImage->HasTipLibraryDate())
		{
			dtLibraryDate = tipImage->GetTipLibraryDate();
		}

		//Delete the library date
		tipImage->DeleteTipLibraryDate();
	}
}

int main()
{
	//New functions for setting SOP Common values
	NewBaseClassTags();

	//New functions for SDICOS::TipImage
	TipImageFeatures();

	return 0;
}
