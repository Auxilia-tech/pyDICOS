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
#ifndef _STRATOVAN_DICOS_QR_MEASUREMENTS_H_
#define _STRATOVAN_DICOS_QR_MEASUREMENTS_H_

#include "SDICOS/ChemicalCodeSequence.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/Point3D.h"

namespace SDICOS
{
namespace QRTypes
{
	
///
/// \class QRMeasurements
/// \brief Implements QR Measurements
/// SPECREF V03 Section 10.3.2, Table 61
///
class QRMeasurements
{
public:
	/// Constructor
	QRMeasurements();
	/// Copy Constructor
	QRMeasurements(const QRMeasurements &qrm);
	/// Destructor
	~QRMeasurements();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	QRMeasurements& operator=(const QRMeasurements &qrm);
	/// Comparison operator
	bool operator==(const QRMeasurements &qrm)const;
	/// Comparison operator
	bool operator!=(const QRMeasurements &qrm)const;

	///
	/// \class MeasurementsItem
	/// \brief Implements an item in QR Measurements Sequence
	///
	class MeasurementsItem
	{
	public:
		/// Constructor
		MeasurementsItem();
		/// Copy Constructor
		MeasurementsItem(const MeasurementsItem &item);
		/// Destructor
		~MeasurementsItem();
	
		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		MeasurementsItem& operator=(const MeasurementsItem &item);
		/// Comparison operator
		bool operator==(const MeasurementsItem &item)const;
		/// Comparison operator
		bool operator!=(const MeasurementsItem &item)const;

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

		/// Target Material Sequence (Single Item Sequence) : Tag (4010, 1072), VR = SQ [required]
		bool SetTargetMaterial(const ChemicalCodeSequence &chemicalcodesequence);
		/// @see SetTargetMaterial
		bool GetTargetMaterial(ChemicalCodeSequence &chemicalcodesequence)const;
		/// @see SetTargetMaterial
		ChemicalCodeSequence& GetTargetMaterial();
		/// @see SetTargetMaterial
		const ChemicalCodeSequence& GetTargetMaterial()const;

		/// Signal-to-Noise Ratio : Tag (0022, 0155), VR = FL [required]
		bool SetSignalToNoiseRatio(const float fRatio);
		/// @see SetSignalToNoiseRatio
		float GetSignalToNoiseRatio()const;

		/// SNR Threshold : Tag (4010, 1073), VR = FD [required]
		bool SetSnrThreshold(const double fThreshold);
		/// @see SetSnrThreshold
		double GetSnrThreshold()const;

		///
		/// Bounding Polygon : Tag (4010, 101D), VR = FL [required]
		/// If only 2 points are defined, the points specify the opposite corners of a bounding box
		///
		bool SetBoundingPolygon(const Array1D< Point3D<float> > &arrayBounds);
		/// @see SetBoundingPolygon
		bool GetBoundingPolygon(Array1D< Point3D<float> > &arrayBounds)const;
		/// @see SetBoundingPolygon
		Array1D< Point3D<float> >& GetBoundingPolygon();
		/// @see SetBoundingPolygon
		const Array1D< Point3D<float> >& GetBoundingPolygon()const;

	protected:
		class ImplMeasurementsItem;
		ImplMeasurementsItem	*m_pImplMeasurementsItem; ///< Internal implementation
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

	/// Instance Number : Tag (0020, 0013), VR = IS [required]
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);
	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;
	/// @see SetInstanceNumber
	DcsString GetInstanceNumberAsString()const;

	///
	/// Content Date and Time
	/// @param strDate Content Date : Tag (0008, 0023), VR = DA [required]
	/// @param strTime Content Time : Tag (0008, 0033), VR = TM [required]
	///
	bool SetContentTimeAndDate(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetContentTimeAndDate
	DcsTime GetContentTime()const;
	/// @see SetContentTimeAndDate
	DcsDate GetContentDate()const;

	/// QR Measurements Sequence : Tag (4010, 1071), VR = SQ [required]
	bool SetMeasurementsSequence(const Array1D<MeasurementsItem> &arrayMeasurements);
	/// @see SetMeasurementsSequence
	bool GetMeasurementsSequence(Array1D<MeasurementsItem> &arrayMeasurements)const;
	/// @see SetMeasurementsSequence
	Array1D<MeasurementsItem>& GetMeasurementsSequence();
	/// @see SetMeasurementsSequence
	const Array1D<MeasurementsItem>& GetMeasurementsSequence()const;

protected:
	class ImplQRMeasurements;
	ImplQRMeasurements	*m_pImplQRMeasurements; ///< Internal implementation
};

}//namespace QRTypes
}//namespace SDICOS

#endif