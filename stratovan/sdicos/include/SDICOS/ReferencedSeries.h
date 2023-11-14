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
#ifndef _STRATOVAN_DICOS_REFERENCED_SERIES_H_
#define _STRATOVAN_DICOS_REFERENCED_SERIES_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/SopInstanceReference.h"

namespace SDICOS
{

///
/// \class ReferencedSeriesSequence
/// \brief Implements Series and Instance Reference Macro
/// SPECREF V03 Section 14.7, Table 103
///
class ReferencedSeriesSequence
{
public:
	/// Constructor
	ReferencedSeriesSequence();
	/// Copy constructor
	ReferencedSeriesSequence(const ReferencedSeriesSequence &referencedseriessequence);
	/// Destructor
	virtual ~ReferencedSeriesSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	ReferencedSeriesSequence& operator=(const ReferencedSeriesSequence &referencedseriessequence);
	/// Comparison operator
	bool operator==(const ReferencedSeriesSequence &referencedseriessequence)const;
	/// Comparison operator
	bool operator!=(const ReferencedSeriesSequence &referencedseriessequence)const;

	///
	/// \class ReferencedSeries
	/// \brief Implements a sequence item
	///
	class ReferencedSeries
	{
	public:
		/// Constructor
		ReferencedSeries();
		/// Copy constructor
		ReferencedSeries(const ReferencedSeries &referencedseriessequence);
		/// Destructor
		~ReferencedSeries();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		ReferencedSeries& operator=(const ReferencedSeries &referencedseries);
		/// Comparison operator
		bool operator==(const ReferencedSeries &referencedseries)const;
		/// Comparison operator
		bool operator!=(const ReferencedSeries &referencedseries)const;

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

		/// Set Referenced Series Instance UID : Tag (0020, 000E), VR = UI [required]
		bool SetSeriesInstanceUID(const DcsUniqueIdentifier &strSeriesInstanceUID);
		/// @see SetSeriesInstanceUID
		DcsString GetSeriesInstanceUID()const;

		/// Set Referenced Instances : Tag (0008, 114A), VR = SQ [required]
		bool SetReferencedInstances(const Array1D<SopInstanceReference> &arraySopInstanceReferences);
		/// @see SetReferencedInstances
		bool GetReferencedInstances(Array1D<SopInstanceReference> &arraySopInstanceReferences)const;
		/// @see SetReferencedInstances
		Array1D<SopInstanceReference>& GetReferencedInstances();
		/// @see SetReferencedInstances
		const Array1D<SopInstanceReference>& GetReferencedInstances()const;

	protected:
		class ImplReferencedSeries;
		ImplReferencedSeries	*m_pImplReferencedSeries; ///< Internal implementation
	};

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

	/// Set Referenced Series : Tag (0008, 1115), VR = SQ [required]
	bool SetReferencedSeries(const Array1D<ReferencedSeries> &arrayReferencedSeries); 
	/// @see SetReferencedSeries
	bool GetReferencedSeries(Array1D<ReferencedSeries> &arrayReferencedSeries)const; 
	/// @see SetReferencedSeries
	Array1D<ReferencedSeries>& GetReferencedSeries(); 
	/// @see SetReferencedSeries
	const Array1D<ReferencedSeries>& GetReferencedSeries()const; 

protected:
	class ImplReferencedSeriesSequence;
	ImplReferencedSeriesSequence	*m_pImplReferencedSeriesSequence; ///< Internal implementation
};
}//namespace SDICOS

#endif