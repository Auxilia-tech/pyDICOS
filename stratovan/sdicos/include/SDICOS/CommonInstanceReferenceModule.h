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
#ifndef _STRATOVAN_DICOS_COMMON_INSTANCE_REFERENCE_MODULE_H_
#define _STRATOVAN_DICOS_COMMON_INSTANCE_REFERENCE_MODULE_H_

#include "SDICOS/Array1D.h"
#include "SDICOS/String.h"
#include "SDICOS/ReferencedSeries.h"

namespace SDICOS
{

///
/// \class CommonInstanceReferenceModule
/// \brief Implements Common Instance Reference Module
/// SPECREF V03 Section 14.5, Table 101
///
class CommonInstanceReferenceModule
{
public:
	/// Constructor
	CommonInstanceReferenceModule();
	/// Copy constructor
	CommonInstanceReferenceModule(const CommonInstanceReferenceModule &commoninstancereferencemodule);
	/// Desstructor
	~CommonInstanceReferenceModule();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CommonInstanceReferenceModule& operator=(const CommonInstanceReferenceModule &commoninstancereferencemodule);
	/// Comparison operator
	bool operator==(const CommonInstanceReferenceModule &commoninstancereferencemodule)const;
	/// Comparison operator
	bool operator!=(const CommonInstanceReferenceModule &commoninstancereferencemodule)const;

	///
	/// \class ReferencedSeriesFromOtherScan
	/// \brief Implements a sequence item for referencing series in other scans
	///
	class ReferencedSeriesFromOtherScan
	{
	public:
		/// Constructor
		ReferencedSeriesFromOtherScan();
		/// Copy constructor
		ReferencedSeriesFromOtherScan(const ReferencedSeriesFromOtherScan &referencedseriesfromotherscan);
		/// Desstructor
		~ReferencedSeriesFromOtherScan();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		ReferencedSeriesFromOtherScan& operator=(const ReferencedSeriesFromOtherScan &referencedseriesfromotherscan);
		/// Comparison operator
		bool operator==(const ReferencedSeriesFromOtherScan &referencedseriesfromotherscan)const;
		/// Comparison operator
		bool operator!=(const ReferencedSeriesFromOtherScan &referencedseriesfromotherscan)const;
		
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

		/// Set Referenced Scan Instance UID : Tag (0020, 000D), VR = UI [required]
		bool SetScanInstanceUID(const DcsUniqueIdentifier &strScanInstanceUID);
		/// @see SetScanInstanceUID
		DcsString GetScanInstanceUID()const;

		/// Set Referenced Series Sequence : Tag (0008, 1115) [required]
		bool SetReferencedSeries(const ReferencedSeriesSequence &referencedseries); 
		/// @see SetReferencedSeries
		bool GetReferencedSeries(ReferencedSeriesSequence &referencedseries)const; 
		/// @see SetReferencedSeries
		ReferencedSeriesSequence& GetReferencedSeries(); 
		/// @see SetReferencedSeries
		const ReferencedSeriesSequence& GetReferencedSeries()const; 
		
	protected:

		class ImplReferencedSeriesFromOtherScan;
		ImplReferencedSeriesFromOtherScan	*m_pImplReferencedSeriesFromOtherScan; ///< Internal implementation
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

	/// Set Referenced Series Sequence : Tag (0008, 1115) [required if references are used]
	/// List of series that contain references. All series must be in the same scan.
	bool SetReferencedSeries(const ReferencedSeriesSequence &referencedseries); 
	/// @see SetReferencedSeries
	bool GetReferencedSeries(ReferencedSeriesSequence &referencedseries)const; 
	/// Allocate Referenced Series
	void AllocateReferencedSeries();
	/// Get the referenced series
	ReferencedSeriesSequence* GetReferencedSeries(); 
	/// @see SetReferencedSeries
	const ReferencedSeriesSequence* GetReferencedSeries()const; 
	/// Delete Referenced Series
	void DeleteReferencedSeries();

	/// Set Scan Containing Referenced Instances Sequence : Tag (0008, 1200), VR = SQ [required if referenced scan instances are used]
	/// List of referenced series in other scans
	bool SetReferencedSeriesFromOtherScans(const Array1D<ReferencedSeriesFromOtherScan> &arrayReferencedSeriesFromOtherScans);
	/// @see SetReferencedSeriesFromOtherScans
	bool GetReferencedSeriesFromOtherScans(Array1D<ReferencedSeriesFromOtherScan> &arrayReferencedSeriesFromOtherScans)const;
	/// @see SetReferencedSeriesFromOtherScans
	Array1D<ReferencedSeriesFromOtherScan>& GetReferencedSeriesFromOtherScans();
	/// @see SetReferencedSeriesFromOtherScans
	const Array1D<ReferencedSeriesFromOtherScan>& GetReferencedSeriesFromOtherScans()const;
	/// Delete Scan Containing Referenced Instances Sequence
	void DeleteReferencedSeriesFromOtherScans();

protected:

	class ImplCommonInstanceReference;
	ImplCommonInstanceReference	*m_pImplCommonInstanceReference; ///< Internal implementation
};

}//namespace SDICOS

#endif
