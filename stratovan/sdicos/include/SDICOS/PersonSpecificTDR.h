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
#ifndef _STRATOVAN_DICOS_PERSON_SPECIFIC_TDR_H_
#define _STRATOVAN_DICOS_PERSON_SPECIFIC_TDR_H_

#include "SDICOS/CommonSpecificTDR.h"
#include "SDICOS/BodyZonesAIT.h"
#include "SDICOS/Point3D.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class PersonSpecificTDR
/// \brief Implements Person-Specific TDR Details Macro
/// SPECREF V03 Section 12.5.2, Table 72
///
///	PersonSpecificTDR is a single item sequence : Tag (4010, 1037), VR = SQ [required if "TDR Type", tag (4010, 1027), is "MACHINE"]
///
class PersonSpecificTDR
{
public:
	/// Constructor
	PersonSpecificTDR();
	/// Copy constructor
	PersonSpecificTDR(const PersonSpecificTDR &ptdr);
	/// Destructor
	~PersonSpecificTDR();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	PersonSpecificTDR& operator=(const PersonSpecificTDR &ptdr);
	/// Comparison operator
	bool operator==(const PersonSpecificTDR &ptdr)const;
	/// Comparison operator
	bool operator!=(const PersonSpecificTDR &ptdr)const;

	///
	/// \class AnomalyLocatorIndicator
	/// \brief Implements an item in Anomaly Locator Indicator Sequence
	///
	class AnomalyLocatorIndicator
	{
	public:
		/// Constructor
		AnomalyLocatorIndicator();

		/// Construct from three floats
		AnomalyLocatorIndicator(const float fX, const float fY, const float fZ);

		/// Construct from 3D Position
		AnomalyLocatorIndicator(const Point3D<float>& p);

		/// Copy constructor
		AnomalyLocatorIndicator(const AnomalyLocatorIndicator &anomaly);
		/// Destructor
		~AnomalyLocatorIndicator();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		AnomalyLocatorIndicator& operator=(const AnomalyLocatorIndicator &anomaly);
		/// Comparison operator
		bool operator==(const AnomalyLocatorIndicator &anomaly)const;
		/// Comparison operator
		bool operator!=(const AnomalyLocatorIndicator &anomaly)const;

		///
		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is missing or invalid
		///
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Copy the attributes from the module into the given AttributeManager
		///
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is not present.
		///
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

		///
		/// Set all required and optional attributes from the given AttributeManager
		///
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false if IsValid() returned false
		///
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Determine if all needed attributes (required and conditionally required) are set.
		///
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		///
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

		///
		/// Anomaly Locator Indicator : Tag (4010, 107A), VM = 3, VR = FL [required]
		/// Indicates the center coordinate of the anomaly in image space coordinates.
		/// For 2D images, fZ = 0.  For 3D volumes, the first frame is fZ = 1.
		///
		bool SetCenter(const float fX, const float fY, const float fZ);
		/// @see SetCenter
		Point3D<float>& GetCenter();
		/// @see SetCenter
		const Point3D<float>& GetCenter()const;
		/// Returns true if data is present
		bool HasCenter()const;
		/// Deletes data
		void DeleteCenter();

	protected:
		class ImplAnomalyLocatorIndicator;
		ImplAnomalyLocatorIndicator	*m_pImplAnomalyLocatorIndicator; ///< Internal implementation
	};

	///
	/// \class PTORepresentationSequenceItem
	/// Represents an item in PTO Representation Sequence
	/// 
	class PTORepresentationSequenceItem : public CommonSpecificTDR
	{
	public:
		/// Default Constructor
		PTORepresentationSequenceItem();

		/// Copy Constructor
		PTORepresentationSequenceItem(const PTORepresentationSequenceItem &item);

		/// Destructor
		virtual ~PTORepresentationSequenceItem();

		/// Release allocated resources
		virtual void FreeMemory();

		/// Assignment operator
		PTORepresentationSequenceItem& operator=(const PTORepresentationSequenceItem &item);

		/// Equality comparison operator
		bool operator==(const PTORepresentationSequenceItem &item)const;

		/// Inequality comparison operator
		bool operator!=(const PTORepresentationSequenceItem &item)const;

		/// Initialize the class attributes from the given AttributeManager
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Copy the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Anomaly Locator Indicator Sequence : Tag (4010, 1079), VR = SQ [required]
		bool SetAnomalyLocatorIndicator(const Array1D<AnomalyLocatorIndicator> &arrayAnomalyLocatorIndicator);
		/// @see SetAnomalyLocatorIndicator
		bool GetAnomalyLocatorIndicator(Array1D<AnomalyLocatorIndicator> &arrayAnomalyLocatorIndicator)const;
		/// @see SetAnomalyLocatorIndicator
		Array1D<AnomalyLocatorIndicator>& GetAnomalyLocatorIndicator();
		/// @see SetAnomalyLocatorIndicator
		const Array1D<AnomalyLocatorIndicator>& GetAnomalyLocatorIndicator()const;

		/// PTO Region Sequence : Tag (4010, 107B), VR = SQ [optional]
		bool SetRegion(const Array1D<AitBodyZones> &arrayZones);
		/// @see SetRegion
		bool GetRegion(Array1D<AitBodyZones> &arrayZones)const;
		/// @see SetRegion
		Array1D<AitBodyZones>& GetRegion();
		/// @see SetRegion
		const Array1D<AitBodyZones>& GetRegion()const;
		/// Returns true if data is present
		bool HasRegion()const;
		/// Delete PTO Region Sequence
		void DeleteRegion();

	private:
		class SequenceItemImpl;
		SequenceItemImpl *m_pSequenceItemImpl;
	};

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

	/// Returns PTO Representation Sequence items : Tag (4010, 1037), VR = SQ, VM = 1...n [Required if TDR Type is MACHINE]
	Array1D<PTORepresentationSequenceItem>& GetPTORepresentationSequenceItems();
	/// Returns PTO Representation Sequence items : Tag (4010, 1037), VR = SQ, VM = 1...n [Required if TDR Type is MACHINE]
	const Array1D<PTORepresentationSequenceItem>& GetPTORepresentationSequenceItems()const;
	/// Delete all items
	void DeletePTORepresentationSequenceItems();

protected:
	class ImplPersonSpecificTDR;
	ImplPersonSpecificTDR	*m_pImplPersonSpecificTDR; ///< Internal implementation
};

}//namespace TDRTypes
}//namespace SDICOS

#endif