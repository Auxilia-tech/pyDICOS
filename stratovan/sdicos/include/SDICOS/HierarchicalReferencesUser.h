//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_HIERARCHICAL_REFERENCES_USER_H_
#define _STRATOVAN_DICOS_HIERARCHICAL_REFERENCES_USER_H_

#include "SDICOS/HierarchicalReferences.h"

namespace SDICOS
{ 
	namespace HierarchicalReferences
	{
		///
		/// \class SopInstance
		///  Reference an SopInstance
		///
		class  SopInstance
		{
		public:
			/// Constructor
			SopInstance();

			/// Copy Constructor
			SopInstance(const SopInstance& rhs);

			// Destructor
			~SopInstance();

			/// Assignment operator
			SopInstance& operator=(const SopInstance& rhs);

			/// Equality operator
			bool operator==(const SopInstance& rhs)const;

			/// Inequality operator
			bool operator!=(const SopInstance& rhs)const;

			/// Read from SDICOS::HierarchicalSeriesReference::SopInstanceReferenceSequenceItem
			bool Read(const SDICOS::HierarchicalSeriesReference::SopInstanceReferenceSequenceItem& sopInstanceReference, ErrorLog& el);

			/// Write into SDICOS::HierarchicalSeriesReference::SopInstanceReferenceSequenceItem
			bool Write(SDICOS::HierarchicalSeriesReference::SopInstanceReferenceSequenceItem& sopInstanceReference, ErrorLog& el) const;

			/// Are the SOP Class UID and Sop Instance UID valid
			/// @return true/false
			bool IsValid() const;

			/// Set Class UID and Instance UID
			/// @param strClassUID		Class UID
			/// @param strInstanceUID	Instance UID
			/// @return true/false
			bool SetSopInstance(const DcsUniqueIdentifier& strClassUID, const DcsUniqueIdentifier& strInstanceUID);

			/// Set Class UID and Instance UID
			/// @param sopInstanceRef Sop Class UID and Instance UID
			/// @return true/false
			bool SetSopInstance(const SDICOS::SopInstanceReference& sopInstanceRef);

			/// Get Class UID
			/// @return DcsUniqueIdentifier
			DcsUniqueIdentifier GetClassUID() const;

			/// Sop Instance UID
			/// @return DcsUniqueIdentifier
			DcsUniqueIdentifier GetSopInstanceUID() const;

			/// Information for the purpose of adding this reference
			class ReferencePurpose
			{
			public:

				bool operator==(const ReferencePurpose& rhs) const;
				bool operator!=(const ReferencePurpose& rhs) const;

				DcsShortString m_strPurposeCode;		///< Code indicating reference's purpose
				DcsShortString m_strPurposeCodeScheme;	///< Schema used for the code
				DcsLongString m_strPurposeCodeMeaning;	///< Human readable meaning for the code
			};

			/// Set Purpose of Reference Code Sequence : Tag (0040, A170), VR = SQ [optional]
			/// @param arrayPurposeOfReference Purpose of Reference objects for Referenced SOP Sequence
			/// @return true/false false of CodeSequence objects are not valid
			bool SetPurposeOfReference(const Array1D<ReferencePurpose>& arrayPurposeOfReference);

			/// @see SetPurposeOfReference
			bool AddPurposeOfReference(const ReferencePurpose& refPur);

			/// @see SetPurposeOfReference
			bool GetPurposeOfReference(Array1D<ReferencePurpose>& arrayPurposeOfReference)const;

		private:

			class SopInstanceImpl;
			SopInstanceImpl* m_pSopInstanceImpl;
		};

		///
		/// \class SeriesInstance
		/// Implements Hierarchical Series Reference (Table 92)
		///
		class SeriesInstance
		{
		public:

			/// Constructor
			SeriesInstance();

			/// Copy Constructor
			SeriesInstance(const SeriesInstance& rhs);

			/// Destructor
			~SeriesInstance();

			/// Assignment operator
			SeriesInstance& operator=(const SeriesInstance& rhs);

			/// Equality operator
			bool operator==(const SeriesInstance& rhs)const;

			/// Inequality operator
			bool operator!=(const SeriesInstance& rhs)const;

			/// Read from HierarchicalSeriesReference
			bool Read(const HierarchicalSeriesReference& seriesInstance, ErrorLog& el);

			/// Write into HierarchicalSeriesReference
			bool Write(HierarchicalSeriesReference& seriesInstance, ErrorLog& el) const;

			/// Check if all required parameters have valid values
			/// @return true/false
			bool IsValid() const;

			/// Set Series Instance UID 
			/// @param strID Series Instance UID. 
			///              Unique Identifier of a Series that contains the referenced Composite Object(s)
			/// @return true/false false if the unique identifier is not valid
			bool SetSeriesInstanceUID(const DcsUniqueIdentifier& strID);

			/// @see SetSeriesInstanceUID
			DcsUniqueIdentifier GetSeriesInstanceUID()const;

			/// Set the Retrieve AE Title. 
			/// Title of the DICOS v03 Application Entity where the Composite Object(s) 
			/// may be retrieved on the network. 
			/// @param arrayNames Application Entity Name 
			///	                  Name of DICOS application holding the "Composite Objects"
			/// @return true/false false if the AE strings are not valid
			bool SetApplicationNames(const Array1D<DcsApplicationEntity>& arrayNames);

			/// @see SetApplicationNames
			bool GetApplicationNames(Array1D<DcsApplicationEntity>& arrayNames)const;
			/// Delete application names so that the attribute is not written to the DICOS file
			void DeleteApplicationNames();

			/// Set Storage Media File-Set ID 
			///	@param strID Storage Media File-Set ID
			///	             Human readable identifier for the storage media that holds the Composite Object(s)
			/// @return true/false false if the unique identifier is not valid
			bool SetStorageMediaID(const DcsShortString& strID);

			/// SetStorageMediaID
			DcsShortString GetStorageMediaID()const;

			/// Delete the 'Storage Media File-Set Id' attribute so that it is not written to the DICOS file
			void DeleteStorageMediaID();

			/// Set Storage Media File-Set UID
			///	@param strUID Storage Media File-Set UID
			///	              Uniquely identifies the Storage Media with the Composite Object(s)
			/// @return true/false false if the unique identifier is not valid
			bool SetStorageMediaUID(const DcsUniqueIdentifier& strUID);

			/// SetStorageMediaUID
			DcsUniqueIdentifier GetStorageMediaUID()const;

			/// Delete the 'Storage Media File-Set UID' attribute so that it is not written to the DICOS file
			void DeleteStorageMediaUID();

			/// Set Referenced SOP Sequence
			/// @param arrayReferences  SOP Instance Reference Sequence Item
			/// @return true/false false if sequence item objects are not valid
			bool SetSopInstanceReference(const Array1D<SopInstance>& arrayReferences);

			/// @see SetSopInstanceReference
			bool GetSopInstanceReference(Array1D<SopInstance>& arrayReferences)const;

		private:
			class SeriesInstanceImpl;
			SeriesInstanceImpl* m_pSeriesInstanceImpl;
		};

		///
		/// \class ScanInstance
		///
		class ScanInstance
		{
		public:
			/// Default constructor
			ScanInstance();

			/// Copy Constructor
			ScanInstance(const ScanInstance& rhs);

			/// Destructor
			~ScanInstance();

			/// Assignment operator
			ScanInstance& operator=(const ScanInstance& rhs);

			/// Equality operator
			bool operator==(const ScanInstance& rhs)const;

			/// Inequality operator
			bool operator!=(const ScanInstance& rhs)const;

			/// Read From HierarchicalSopInstanceReference
			/// @param hierarchicalSopInstanceReference Object to read from
			/// @param el Error log object
			/// @return true/false
			bool Read(const HierarchicalSopInstanceReference& hierarchicalSopInstanceReference, ErrorLog& el);
			
			/// Write into HierarchicalSopInstanceReference
			/// @param hierarchicalSopInstanceReference Object to write to
			/// @param el Error log object
			/// @return true/false
			bool Write(HierarchicalSopInstanceReference& hierarchicalSopInstanceReference, ErrorLog& el) const;

			/// Set Scan Instance UID
			/// @param strID Scan Instance UID 
			bool SetScanInstanceUID(const DcsUniqueIdentifier& strID);

			/// @see SetScanInstanceUID
			DcsUniqueIdentifier GetScanInstanceUID()const;

			/// Set Referenced Series Sequence 
			/// @param arrayReferences Array of Hierarchical Series Reference objects
			/// @return true/false false if the HierarchicalSeriesReference objects are not valid
			bool SetReferencedSeries(const Array1D<SeriesInstance>& arrayReferences);

			/// @see SetReferencedSeries
			bool GetReferencedSeries(Array1D<SeriesInstance>& arrayReferences)const;

		private:
			class ScanInstanceImpl;
			ScanInstanceImpl* m_pScanInstanceImpl;
		};
	} // namespace HierarchicalReferences
}//namespace SDICOS

#endif 