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
#ifndef _STRATOVAN_DICOS_AIT_2D_SERIES_H_
#define _STRATOVAN_DICOS_AIT_2D_SERIES_H_

#include "SDICOS/GeneralSeriesModule.h"

namespace SDICOS
{
namespace AIT2DTypes
{

///
/// \class AIT2DSeries
/// \brief Implements 2D AIT Series
/// SPECREF V03 Section 9.2.3.1, Table 41
///
class AIT2DSeries : public GeneralSeriesModule
{
public:
	/// Constructor
	AIT2DSeries();
	/// Copy constructor
	AIT2DSeries(const AIT2DSeries &ait);
	/// Destructor
	~AIT2DSeries();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AIT2DSeries& operator=(const AIT2DSeries &ait);
	/// Comparison operator
	bool operator==(const AIT2DSeries &ait)const;
	/// Comparison operator
	bool operator!=(const AIT2DSeries &ait)const;

	/// Presentation Intent Type enumerations
	typedef enum
	{
		enumUnknownPresentationIntentType, ///< Unknown enumeration

		enumPresentation,	//< "FOR PRESENTATION"
		enumProcessing		//< "FOR PROCESSING"

	}PRESENTATION_INTENT_TYPE;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Presentation Intent Type : Tag (0008, 0068), VR = CS [required]
	bool SetPresentationIntentType(const PRESENTATION_INTENT_TYPE nType);
	/// @see SetPresentationIntentType
	PRESENTATION_INTENT_TYPE GetPresentationIntentType()const;
	/// @see SetPresentationIntentType
	DcsString GetPresentationIntentTypeAsString()const;

	/// Convert a string to PRESENTATION_INTENT_TYPE
	static PRESENTATION_INTENT_TYPE PresentationIntentTypeFromString(const DcsString& s);
	
	/// Convert a PRESENTATION_INTENT_TYPE to a DcsString
	static DcsString PresentationIntentTypeToString(PRESENTATION_INTENT_TYPE p);
protected:
	class ImplAIT2DSeries;
	ImplAIT2DSeries *m_pImplAIT2DSeries; ///< Internal implementation

	/// Internally set to AIT
	virtual bool SetModality(const MODALITY nModality);	
};

}//AIT2DTypes
}//namespace SDICOS

#endif
