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
#ifndef _STRATOVAN_DICOS_TAGDEFINES_H_
#define _STRATOVAN_DICOS_TAGDEFINES_H_

#include "SDICOS/Tag.h"
#include "SDICOS/TagInfo.h"

// Meta Data (DICOM) Tags

#define TAG_META_DATA_LENGTH			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0000), "Meta Data Length", "UL")
#define TAG_META_INFO_VERSION			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0001), "Meta Info Version", "OB")
#define TAG_META_SOP_CLASS_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0002), "Meta SOP Class UID", "UI")
#define TAG_META_SOP_INSTANCE_UID		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0003), "Meta SOP Instance UID", "UI")
#define TAG_META_DICOS_VERSION			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0004), "Meta DICOS Version", "CS")
#define TAG_TRANSFER_SYNTAX				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0010), "Transfer Syntax", "UI")
#define TAG_IMPLEMENTATION_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0012), "Implementation UID", "UI")
#define TAG_IMPLEMENTATION_VERSION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0013), "Implementation Version", "SH")
#define TAG_META_SOURCE_APP_TITLE		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0016), "Meta Source Application Title", "AE")
#define TAG_PRIVATE_CREATOR_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0100), "Private Creator UID", "UI")
#define TAG_PRIVATE_INFO				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0002, 0x0102), "Private Info", "OB")


// Common Tags for attributes used in multiple mlocations
#define TAG_CONTENT_DATE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0023), "Content Date", "DA")
#define TAG_CONTENT_TIME				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0033), "Content Time", "TM")


// Sequence Tags
#define TAG_SEQ_ITEM_HEADER				SDICOS::Tags::TagInfo(SDICOS::Tag(0xFFFE, 0xE000), "Sequence Item Header", "")
#define TAG_SEQ_ITEM_DELIMITER			SDICOS::Tags::TagInfo(SDICOS::Tag(0xFFFE, 0xE00D), "Sequence Item Delimiter", "")
#define TAG_ATTRIBUTE_SEQ_DELIMITER		SDICOS::Tags::TagInfo(SDICOS::Tag(0xFFFE, 0xE0DD), "Attribute Sequence Delimiter", "")


// Series Tags
#define TAG_PRESENTATION_INTENT_TYPE	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0068), "Presentation Intent Type", "CS")
#define TAG_SERIES_MODALITY				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0060), "Modality", "CS")


// Object of Inspection Module 
#define TAG_OOI_MASS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x1030), "OOI Mass", "DS")
#define TAG_GENDER						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x0040), "Gender", "CS")
#define TAG_OOI_ALTERNATE_IDS			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x1002), "Other OOI IDs", "SQ")
#define TAG_ALGORITHM_ROUTING_CODE		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1064), "Algorithm Routing Code", "SQ")
#define TAG_OOI_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1042), "OOI Type", "CS")
#define TAG_OOI_TYPE_DESCRIPTOR			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1068), "OOI Type Descriptor", "LT")
#define TAG_OOI_SIZE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1043), "Size", "DS")
#define TAG_BAG_DESCRIPTION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x0022), "Bag Description", "LT")
#define TAG_OOI_ID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x0020), "OOI ID", "LO")
#define TAG_OOI_ID_ASSIGNING_AUTHORITY	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x0021), "OOI ID Assigning Authority", "LO")
#define TAG_OOI_ID_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0010, 0x0022), "OOI ID Type", "CS")


// General Scan Module 
#define TAG_SCAN_INSTANCE_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x000D), "Scan Instance UID", "UI")
#define TAG_SCAN_DESCRIPTION			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1030), "Scan Description", "LO")
#define TAG_SCAN_DATE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0020), "Scan Date", "DA")
#define TAG_SCAN_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0030), "Scan Time", "TM")
#define TAG_SCAN_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1048), "Scan Type", "CS")
#define TAG_REFERENCED_SCANS			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1110), "ReferencedScans Sequence", "SQ")
#define TAG_SCAN_ID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0010), "Scan ID", "SH")
#define TAG_SCAN_NUMBER_OF_VIEWS		SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0028), "Number Of Views in Scan", "US")
#define TAG_SCAN_NUMBER_OF_ENERGIES		SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0032), "Number Of Energies in Scan", "US")


// General Series Module 
// IS in DICOM, changed ot SL in DICOS V02A, changed to IS in V03
#define TAG_SERIES_INSTANCE_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x000E), "Series Instance UID", "UI")
#define TAG_SERIES_DATE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0021), "Series Date", "DA")
#define TAG_SERIES_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0031), "Series Time", "TM")
#define TAG_SERIES_NUMBER				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0011), "Series Number", "IS") 
#define TAG_SERIES_VIEW					SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0024), "Series View", "US")
#define TAG_SERIES_VIEW_DESCRIPTION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0026), "Series View Description", "LO")
#define TAG_SERIES_ACQUISITION_STATUS	SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1044), "Series Acquisition Status", "CS")
#define TAG_SERIES_DESCRIPTION			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x103E), "Series Description", "LO")
#define TAG_SERIES_TEST_ARTICLE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1046), "Test Article", "CS")
#define TAG_SERIES_ENERGY				SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0030), "Series Energy", "US")
#define TAG_SERIES_ENERGY_DESCRIPTION	SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x0031), "Series Energy Description", "LO")


// Additional Inspection Selection Criteria 
#define TAG_ADDITIONAL_SCREENING_PERFORMED				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x106D), "Additional Screening Performed", "CS")
#define TAG_ADDITIONAL_INSPECTION_SELECTION_CRITERIA	SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x106E), "Additional Inspection Selection Criteria", "CS")
#define TAG_ADDITIONAL_INSPECTION_METHOD_SEQ			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x106F), "Additional Inspection Method Sequence", "SQ")


// Threat Detection Report Module Attributes
#define TAG_TDR_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1027), "TDR Type", "CS")
#define TAG_OPERATOR_IDENTIFICATION_SEQ				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1072), "Operator Identification Sequence", "SQ")
#define TAG_IMAGE_SCALE_REPRESENTATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1075), "Image Scale Representation", "FD")
#define TAG_ALARM_DECISION_TIME						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x102B), "Alarm Decision Time", "DT")
#define TAG_ALARM_DECISION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1031), "Alarm Decision", "CS")
#define TAG_ABORT_FLAG								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1024), "Abort Flag", "CS")
#define TAG_ABORT_REASON							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1021), "Abort Reason", "CS")
#define TAG_THREAT_DETECTION_ALGORITHM_VERSION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1029), "Threat Detection Algorithm And Version", "LO")
#define TAG_NUMBER_OF_TOTAL_OBJECTS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1033), "Number of Total Objects", "US")
#define TAG_NUMBER_OF_ALARM_OBJECTS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1034), "Number of Alarm Objects", "US")
#define TAG_TOTAL_PROCESSING_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1069), "Total Processing Time", "FL")

// Threat Sequence Module Attributes
#define TAG_THREAT_SEQ								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1011), "Threat Sequence", "SQ")
#define TAG_REFERENCED_PTO_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1076), "Referenced PTO Sequence", "SQ")
#define TAG_ORIGINATING_TDR_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1027), "Originating TDR Type", "CS")
#define TAG_POTENTIAL_THREAT_OBJECT_ID				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1010), "Potential Threat Object ID", "US")
#define TAG_REFERENCED_TDR_INSTANCE_SEQ				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1077), "Referenced TDR Instance Sequence", "SQ")
#define TAG_PROCESSING_START						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1080), "Start time for analyzing PTO", "DT")
#define TAG_PROCESSING_END							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1081), "End Time for analyzing PTO", "DT")
#define TAG_THREAT_ITEM_TOTAL_PROCESSING_TIME		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1082), "Total Time for analyzing Threat Item PTO in milliseconds", "FL")
#define TAG_INSPECTION_SELECTION_CRITERIA			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x107C), "Inspection Selection Criteria", "CS")
#define TAG_SECONDARY_INSPECTION_METHOD				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x107D), "Secondary Inspection Method", "SQ")

#define TAG_ITINERARY_ID							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1051), "Itinerary ID", "LO")
#define TAG_ITINERARY_ID_TYPE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1052), "Itinerary ID Type", "SH")
#define TAG_ITINERARY_ID_ASSIGNING_AUTHORITY		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1053), "Itinerary ID Assigning Authority", "LO")

#define TAG_ROUTE_SEGMENT_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x100A), "Route Segment Sequence", "SQ")
#define TAG_ROUTE_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1054), "Route Segment Sequence Route ID", "SH")
#define TAG_ROUTE_ID_ASSIGNING_AUTHORITY			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1055), "Route Segment Sequence Route ID Assigning Authority", "SH")
#define TAG_INBOUND_ARRIVAL_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1056), "Inbound Arrival Type", "CS")
#define TAG_ROUTE_SEGMENT_ID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1007), "Route Segment ID", "SH")
#define TAG_CARRIER_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1058), "Carrier ID", "SH")
#define TAG_CARRIER_ID_ASSIGNING_AUTHORITY			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1059), "Carrier ID Assigning Authority", "CS")
#define TAG_BOARDING_PASS_ID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101A), "Boarding Pass ID", "SH")
#define TAG_ROUTE_SEGMENT_START_LOCATION_ID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101E), "Route Segment Start Location ID", "SH")
#define TAG_ROUTE_SEGMENT_END_LOCATION_ID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101F), "Route Segment End Location ID", "SH")
#define TAG_ROUTE_SEGMENT_LOCATION_ID_TYPE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1020), "Route Segment Location ID Type", "CS")
#define TAG_ROUTE_SEGMENT_START_TIME				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1025), "Route Segment Start Time", "DT")
#define TAG_ROUTE_SEGMENT_END_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1026), "Route Segment End Time", "DT")
#define TAG_ASSIGNED_LOCATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x102A), "Assigned Location", "SH")
#define TAG_INTERNATIONAL_ROUTE_SEGMENT				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1028), "International Route Segment", "CS")
#define TAG_OWNER_SEQ								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1047), "OOI Owner Sequence", "SQ")
#define TAG_OWNER_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1009), "OOI Owner Type", "CS")
#define TAG_OWNER_CREATION_TIME						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1041), "OOI Owner Creation Time", "DT")
#define TAG_OWNER_IDENTITY_REMOVED					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0012, 0x0062), "OOI Owner Identity Removed", "CS")
#define TAG_OWNER_DEIDENTIFICATION_METHOD			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0012, 0x0063), "OOI Owner De-identification Method", "LO")
#define TAG_DEIDENTIFICATION_METHOD_CODE_SEQ		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0012, 0x0064), "De-identification Method Code Sequence", "SQ")
#define TAG_TRANSPORT_CLASSIFICATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1067), "Transport Classification", "CS")
#define TAG_OOI_OWNER_RISK_SCORE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1022), "OOI Owner Risk Score", "SS")

#define TAG_IMAGE_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0008), "Image Type", "CS")
#define TAG_BASIS_MATERIALS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1045), "Basis Materials Code Sequence", "SQ")
#define TAG_SAMPLES_PER_PIXEL						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0002), "Samples Per Pixel", "US")
#define TAG_PHOTOMETRIC_INTERPRETATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0004), "Photometric Interpretation", "CS")
#define TAG_BITS_ALLOCATED							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0100), "Bits Allocated", "US")
#define TAG_BITS_STORED								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0101), "Bits Stored", "US")
#define TAG_HIGH_BIT								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0102), "High Bit", "US")
#define TAG_BURNED_IN_ANNOTATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0301), "Burned in Annotation", "CS")
#define TAG_PRESENTATION_LUT_SHAPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x2050, 0x0020), "Presentation LUT Shape", "CS")
#define TAG_ACQUISITION_DATE_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x002A), "Acquisition Date Time", "DT")
#define TAG_ACQUISITION_DURATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9073), "Acquisition Duration", "FD")
#define TAG_ACQUISITION_NUMBER						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0012), "Acquisition Number", "IS")
#define TAG_REFERENCED_RAW_DATA						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9121), "Referenced Raw Data Sequence", "SQ")
#define TAG_REFERENCED_IMAGE_EVIDENCE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9092), "Referenced Image Evidence Sequence", "SQ")
#define TAG_SOURCE_IMAGE_EVIDENCE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9154), "Source Image Evidence Sequence", "SQ")
#define TAG_REFERENCED_PRESENTATION_STATE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9237), "Referenced Presentation State", "SQ")
#define TAG_IMAGE_COMMENTS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x4000), "Image Comments", "LT")
#define TAG_ICON_IMAGE_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0088, 0x0200), "Icon Image Sequence", "SQ")

#define TAG_PIXEL_REPRESENTATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0103), "Pixel Representation", "US")
#define TAG_PIXEL_VALUE_RESCALE_INTERCEPT			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1052), "Pixel Value Rescale Intercept", "DS")
#define TAG_PIXEL_VALUE_RESCALE_SLOPE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1053), "Pixel Value Rescale Slope", "DS")
#define TAG_DATA_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0012), "SDI/CDI Data Type", "CS")
#define TAG_PIXEL_VALUE_RESCALE_TYPE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1054), "Pixel Value Rescale Type", "LO")
#define TAG_PIXEL_VALUE_TRANSFORMATION_SEQ			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x9145), "Pixel Value Transformation Sequence", "SQ")


#define TAG_GANTRY_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1008), "Gantry Type", "CS")

#define TAG_VOI_LUT_SEQ								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3010), "VOI LUT Sequence", "SQ")
#define TAG_LUT_DESCRIPTOR							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3002), "LUT Descriptor", "US/SS")
#define TAG_LUT_EXPLANATION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3003), "LUT Explanation", "LO")
#define TAG_LUT_DATA								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3006), "LUT Data", "OW")

#define TAG_WINDOW_CENTER							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1050), "Window Center", "DS")
#define TAG_WINDOW_WIDTH							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1051), "Window Width", "DS")
#define TAG_WINDOW_CENTER_AND_WIDTH_EXPLANATION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1055), "Window Center and Width Explanation", "LO")
#define TAG_LUT_FUNCTION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1056), "LUT Function", "CS")


// Image Pixel Module
#define TAG_PIXEL_PADDING_RANGE_LIMIT_16			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0121), "Pixel Padding Range Limit 16bit", "US/SS")
#define TAG_PIXEL_PADDING_RANGE_LIMIT_32			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1121), "Pixel Padding Range Limit 32bit", "UL/SL")
#define TAG_PIXEL_PADDING_RANGE_LIMIT_64			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2121), "Pixel Padding Range Limit 64bit", "UD/SD")
#define TAG_PIXEL_PADDING_RANGE_LIMIT_32FLOAT		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3121), "Pixel Padding Range Limit 32bit float", "FL")

// Image Pixel Macro
#define TAG_PIXEL_DATA								SDICOS::Tags::TagInfo(SDICOS::Tag(0x7FE0, 0x0010), "Pixel Data", "OB/OW")
#define TAG_PIXEL_DATA_32BIT						SDICOS::Tags::TagInfo(SDICOS::Tag(0x7FE0, 0x0011), "Pixel Data 32Bit", "OL")
#define TAG_PIXEL_DATA_64BIT						SDICOS::Tags::TagInfo(SDICOS::Tag(0x7FE0, 0x0012), "Pixel Data 64Bit", "OD")
#define TAG_PIXEL_DATA_32BIT_FLOAT					SDICOS::Tags::TagInfo(SDICOS::Tag(0x7FE0, 0x0013), "Pixel Data 32Bit Float", "OF")
#define TAG_PLANAR_CONFIGURATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0006), "Planar Configuration", "US")
#define TAG_NUMBER_OF_ROWS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0010), "Number of Rows", "US")
#define TAG_NUMBER_OF_COLUMNS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0011), "Number of Columns", "US")
#define TAG_PIXEL_ASPECT_RATIO						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0034), "Pixel Aspect Ratio", "IS")
#define TAG_ICC_PROFILE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2000), "ICC Profile", "OB")

#define TAG_SMALLEST_IMAGE_PIXEL_VALUE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0106), "Smallest Image Pixel Value 16Bit", "US/SS")
#define TAG_LARGEST_IMAGE_PIXEL_VALUE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0107), "Largest Image Pixel Value 16Bit", "US/SS")

#define TAG_SMALLEST_IMAGE_PIXEL_VALUE32			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1106), "Smallest Image Pixel Value 32Bit", "UL/SL")
#define TAG_LARGEST_IMAGE_PIXEL_VALUE32				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1107), "Largest Image Pixel Value 32Bit", "UL/SL")

#define TAG_SMALLEST_IMAGE_PIXEL_VALUE64			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2106), "Smallest Image Pixel Value 64Bit", "UD/SD")
#define TAG_LARGEST_IMAGE_PIXEL_VALUE64				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2107), "Largest Image Pixel Value 64Bit", "UD/SD")

#define TAG_SMALLEST_IMAGE_PIXEL_VALUE_32FLOAT		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3106), "Smallest Image Pixel Value 32Bit Float", "FL")
#define TAG_LARGEST_IMAGE_PIXEL_VALUE_32FLOAT		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3107), "Largest Image Pixel Value 32Bit Float", "FL")

#define TAG_RED_PALETTE_COLOR_LUT_DESCRIPTOR		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1101), "Red Palette Color Lookup Table Descriptor", "US/SS")
#define TAG_GREEN_PALETTE_COLOR_LUT_DESCRIPTOR		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1102), "Green Palette Color Lookup Table Descriptor", "US/SS")
#define TAG_BLUE_PALETTE_COLOR_LUT_DESCRIPTOR		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1103), "Blue Palette Color Lookup Table Descriptor", "US/SS")

#define TAG_RED_PALETTE_COLOR_LUT_DATA				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1201), "Red Palette Color Lookup Table Data", "OW")
#define TAG_GREEN_PALETTE_COLOR_LUT_DATA			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1202), "Green Palette Color Lookup Table Data", "OW")
#define TAG_BLUE_PALETTE_COLOR_LUT_DATA				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1203), "Blue Palette Color Lookup Table Data", "OW")

#define TAG_PIXEL_DATA_PROVIDER_URL					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x7FE0), "Pixel Data Provider URL", "UT")


//DX X-Ray Image Module
#define TAG_REPORTED_PIXEL_SPACING					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x0026), "Reported Pixel Spacing", "FL")
#define TAG_ACQ_DEVICE_PROCESSING_DESCRIPTION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1400), "Acquisition Device Processing Description", "LO")
#define TAG_ACQ_DEVICE_PROCESSING_CODE				SDICOS::Tags::TagInfo(SDICOS::Tag(0X0018, 0x1401), "Acquisition Device Processing Code", "LO")
#define TAG_CALIBRATION_IMAGE						SDICOS::Tags::TagInfo(SDICOS::Tag(0X0050, 0X0004), "Calibration Image", "CS")


//DX Detector Module
#define TAG_BIN_NUMBER								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0003), "Bin Number", "SL")
#define TAG_HIGHER_ENERGY							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0007), "Higher Energy", "SL")
#define TAG_LOWER_ENERGY							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0005), "Lower Energy", "SL")
#define TAG_ENERGY_RESOLUTION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0006), "Energy Resolution", "SL")
#define TAG_DETECTOR_TYPE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7004), "Detector Type", "CS")
#define TAG_DETECTOR_CONFIGURATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7005), "Detector Configuration", "CS")
#define TAG_DETECTOR_DESCRIPTION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7006), "Detector Description", "LT")
#define TAG_DETECTOR_MODE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7008), "Detector Mode", "LT")
#define TAG_DETECTOR_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x700A), "Detector ID", "SH")
#define TAG_CALIBRATION_DATE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x700C), "Calibration Date", "DA")
#define TAG_CALIBRATION_TIME						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x700E), "Calibration Time", "TM")
#define TAG_DETECTOR_CALIBRATION_DATA				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x106C), "Detector Calibration Data", "OB")
#define TAG_EXPOSURES_SINCE_CALIBRATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7010), "Exposures Since Calibration", "IS")
#define TAG_EXPOSURES_SINCE_MANUFACTURED			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7011), "Exposures Since Manufactured", "IS")
#define TAG_TIME_SINCE_EXPOSURE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7012), "Time Since Exposure", "DS")
#define TAG_DETECTOR_BINNING						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x701A), "Detector Binning", "DS")
#define TAG_DETECTOR_MANUFACTURER_NAME				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x702A), "Detector Manufacturer Name", "LO")
#define TAG_DETECTOR_MANUFACTURER_MODEL				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x702B), "Detector Manufacturer Model", "LO")
#define TAG_DETECTOR_NOMINAL_FLAG					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7000), "Detector Nominal Flag", "CS")
#define TAG_DETECTOR_TEMPERATURE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7001), "Detector Temperature", "DS")
#define TAG_SENSITIVITY								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x6000), "Sensitivity", "DS")
#define TAG_DETECTOR_ELEMENT_PHYSICAL_SIZE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7020), "Detector Element Physical Size", "DS")
#define TAG_DETECTOR_ELEMENT_SPACING				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7022), "Detector Element Spacing", "DS")
#define TAG_LOW_ENERGY_DETECTORS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0001), "Low Energy Detectors", "CS")
#define TAG_HIGH_ENERGY_DETECTORS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0002), "High Energy Detectors", "CS")


// DX/X-Ray Positioning, Section 8.2.2.5, Table 37
#define TAG_BELT_SPEED								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9309), "Belt Speed", "FD")
#define TAG_BELT_HEIGHT								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1062), "Belt Height", "FL")
#define TAG_DETECTOR_GEOMETRY_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x0004), "Detector Geometry Sequence", "SQ")
#define TAG_DISTANCE_SOURCE_TO_DETECTOR				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1110), "Distance Source to Detector", "DS")
#define TAG_SOURCE_ORIENTATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1060), "Source Orientation", "FL")
#define TAG_SOURCE_POSITION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1061), "Source Position", "FL")


// AIT Modality 
#define TAG_AIT_DEVICE_TYPE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1070), "AIT Device Type", "CS")


// CT Modality
#define TAG_BASIS_MATERIALS_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1045), "Basis Materials Code Sequence", "SQ")


// QR Modality
#define TAG_QR_MEASUREMENTS_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1071), "QR Measurements Sequence", "SQ")
#define TAG_QR_TARGET_MATERIAL_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1072), "Target Material Sequence", "SQ")
#define TAG_QR_SNR_RATIO							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0022, 0x0155), "Signal to Noise Ratio", "FL")
#define TAG_QR_SNR_THRESHOLD						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1073), "Signal To Noise Ratio Threshold", "FD")


// Tags use by multiple modalities
#define TAG_FRAME_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9007), "Frame Type", "CS")
#define TAG_IMAGE_FRAME_TYPE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9329), "Image Frame Type Sequence", "SQ")


// Image Histogram Module Attributes Section 12.2.6, Table 78
#define TAG_HISTOGRAM_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3000), "Histogram Sequence", "SQ")
#define TAG_HISTOGRAM_NUMBER_OF_BINS				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3002), "Histogram Number of Bins", "US")

#define TAG_HISTOGRAM_FIRST_BIN_VALUE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3004), "Histogram First Bin Value", "US/SS")
#define TAG_HISTOGRAM_LAST_BIN_VALUE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3006), "Histogram Last Bin Value", "US/SS")
#define TAG_HISTOGRAM_FIRST_BIN_VALUE_32			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x4004), "Histogram First Bin Value", "UL/SL")
#define TAG_HISTOGRAM_LAST_BIN_VALUE_32				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x4006), "Histogram Last Bin Value", "UL/SL")
#define TAG_HISTOGRAM_FIRST_BIN_VALUE_64			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x5004), "Histogram First Bin Value", "UD/SD")
#define TAG_HISTOGRAM_LAST_BIN_VALUE_64				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x5006), "Histogram Last Bin Value", "UD/SD")
#define TAG_HISTOGRAM_FIRST_BIN_VALUE_32FLOAT		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x6004), "Histogram First Bin Value", "FL")
#define TAG_HISTOGRAM_LAST_BIN_VALUE_32FLOAT		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x6006), "Histogram Last Bin Value", "FL")

#define TAG_HISTOGRAM_BIN_WIDTH						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3008), "Histogram Bin Width", "US")
#define TAG_HISTOGRAM_EXPLANATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3010), "Histogram Explanation", "LO")
#define TAG_HISTOGRAM_DATA							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x3020), "Histogram Data", "UL")

//Real World Value Mapping
#define TAG_REAL_WORLD_VALUE_MAPPING_SEQ			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9096), "Real World Value Mapping Sequence", "SQ")
#define TAG_MAPPED_VALUE_REPRESENTATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7006), "Mapped Value Representation", "US")
#define TAG_REAL_WORLD_VALUE_FIRST_VALUE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9216), "Real World Value First Value Mapped", "US/SS")
#define TAG_REAL_WORLD_VALUE_LAST_VALUE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9211), "Real World Value Last Value Mapped", "US/SS")
#define TAG_REAL_WORLD_VALUE_SLOPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9225), "Real World Value Slope", "FD")
#define TAG_REAL_WORLD_VALUE_INTERCEPT				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9224), "Real World Value Intercept", "FD")
#define TAG_REAL_WORLD_LUT_DATA						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9212), "Real World Value LUT Data", "FD")
#define TAG_REAL_WORLD_LUT_LABEL					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x9210), "Real World Value LUT Label", "SH")


#define TAG_ACQ_CONTEXT_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x0555), "Acquisition Context Sequence", "SQ")
#define TAG_VALUE_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA040), "Value Type", "CS")
#define TAG_CONCEPT_NAME_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA043), "Concept Name Code Sequence", "SQ")
#define TAG_REF_FRAME_NUMBERS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA136), "Referenced Frame Numbers", "US")
#define TAG_NUMERIC_VALUE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA30A), "Numeric Value", "DS")
#define TAG_MEASUREMENT_UNITS_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x08EA), "Measurement Units Code Sequence", "SQ")
#define TAG_DATE									SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA121), "Date", "DA")
#define TAG_TIME									SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA122), "Time", "TM")
#define TAG_PERSON_NAME								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA123), "Person Name", "PN")
#define TAG_TEXT_VALUE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA160), "Text Value", "UT")
#define TAG_CONCEPT_SEQ								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA168), "Concept Code Sequence", "SQ")
#define TAG_ACQ_CONTEXT_DESCRIPTION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x0556), "Acquisition Context Description", "ST")

#define TAG_SCHEME_DESIGNATOR						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0102), "Scheme Designator", "SH")
#define TAG_SCHEME_VERSION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0103), "Scheme Version", "SH")
#define TAG_CONTEXT_IDENTIFIER						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x010F), "Context Identifier", "CS")
#define TAG_MAPPING_RESOURCE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0105), "Mapping Resource", "CS")
#define TAG_GROUP_VERSION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0106), "Group Version", "DT")
#define TAG_EXTENSION_FLAG							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x010B), "Extension Flag", "CS")
#define TAG_GROUP_LOCAL_VERSION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0107), "Group Local Version", "DT")
#define TAG_EXTENSION_CREATOR						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x010D), "Extension Creator", "UI")

#define TAG_CODE_VALUE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0100), "Code Value", "SH")
#define TAG_CODE_MEANING							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0104), "Code Meaning", "LO")
#define TAG_EXTENDED_CODE_VALUE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0101), "Extended Code Value", "LO")
#define TAG_EXTENDED_CODE_MEANING					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0108), "Extended Code Meaning", "LT")

#define TAG_NUMBER_OF_FRAMES						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0008), "Number Of Frames", "US")

#define TAG_TIP_TYPE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1039), "TIP Type", "CS")
#define TAG_TIP_LIBRARY_NAME						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x2041), "TIP Library Name", "ST")
#define TAG_TIP_LIBRARY_DATE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x2043), "TIP Library Date", "DT")
#define TAG_TIP_IMAGE_IDENTIFIER					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x2045), "TIP Image Identifier", "ST")

#define TAG_SOP_CLASS_UID							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0016), "SOP Class UID", "UI")
#define TAG_SOP_INSTANCE_UID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0018), "SOP Instance UID", "UI")
#define TAG_SPECIFIC_CHARACTER_SET					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0005), "Specific Character Set", "CS")
#define TAG_INSTANCE_CREATION_DATE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0012), "Instance Creation Date", "DT")
#define TAG_INSTANCE_CREATION_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0013), "Instance Creation Time", "TM")
#define TAG_INSTANCE_CREATOR_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0014), "Instance Creator UID", "UI")
#define TAG_RELATED_GENERAL_SOP_CLASS_UID			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x001A), "Related General SOP Class UID", "UI")
#define TAG_SPECIALIZED_SOP_CLASS_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x001B), "Original Specialized SOP Class UID", "UI")
#define TAG_DICOS_VERSION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x103A), "DICOS Version", "CS")
#define TAG_TIME_ZONE_UTC_OFFSET					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0201), "Timezone Offset From UTC", "SH")
#define TAG_INSTANCE_NUMBER							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0013), "Instance Number", "IS")
#define TAG_SOP_INSTANCE_STATUS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0100, 0x0410), "SOP Instance Status", "CS")

// General Equipment Module
#define TAG_PIXEL_PADDING_VALUE_16					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0120), "Pixel Padding Value 16bit", "US/SS")
#define TAG_PIXEL_PADDING_VALUE_32					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1120), "Pixel Padding Value 32bit", "UL/SL")
#define TAG_PIXEL_PADDING_VALUE_64					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2120), "Pixel Padding Value 64bit", "UD/SD")
#define TAG_PIXEL_PADDING_VALUE_32FLOAT				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x3120), "Pixel Padding Value 32bit float", "FL")
#define TAG_CLUSTER_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7012), "Cluster ID", "US")
#define TAG_BAG_RAW_PATH							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7014), "Bag Raw Path", "SS")
#define TAG_BAG_IMAGE_PATH							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7016), "Bag Image Path", "SS")
#define TAG_FEED_MODE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7018), "Feed Mode", "CS")
#define TAG_DATA_COLLECTION_MODE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7020), "Data Collection Mode", "CS")
#define TAG_HOLD_MODE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7022), "Hold Mode", "SH")
#define TAG_OPERATION_MODE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7024), "Operation Mode", "CS")
#define TAG_SHOW_MODE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7026), "Show Mode", "SH")
#define TAG_TIMEOUT_MODE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7028), "Timeout Mode", "CS")
#define TAG_OPERATOR_TIMEOUT						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7030), "Operator Timeout", "US")
#define TAG_MACHINE_TIMEOUT							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7032), "Machine Timeout", "US")
#define TAG_PRINTER_NAME							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7034), "Printer Name", "LO")
#define TAG_BARCODE_TYPE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7036), "Bar Code Type", "SH")
#define TAG_SCANNER_IP_PORT							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7038), "Scanner IP and Port", "LO")

// SOP Common Module 
// Contributing Equipment Sequence
#define TAG_CONTRIBUTING_EQUIPMENT_SEQ				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0xA001), "Contributing Equipment Sequence", "SQ")
#define TAG_PURPOSE_OF_REF_CODE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0xA170), "Purpose of Reference Code Sequence", "SQ")
#define TAG_MANUFACTURER							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0070), "Manufacturer", "LO")
#define TAG_MACHINE_LOCATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0080), "Machine Location", "LO")
#define TAG_MACHINE_ADDRESS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0081), "Machine Address", "ST")
#define TAG_MACHINE_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1010), "Machine ID", "SH")
#define TAG_MACHINE_SUBLOCATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1040), "Machine Sub-Location", "LO")
#define TAG_MANUFACTURER_MODEL_NAME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1090), "Manufacturer's Model Name", "LO")
#define TAG_DEVICE_SERIAL_NUMBER					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1000), "Device Serial Number", "LO")
#define TAG_SOFTWARE_VERSIONS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1020), "Software Versions", "LO")
#define TAG_SPATIAL_RESOLUTION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1050), "Spatial Resolution", "DS")
#define TAG_DATE_OF_CALIBRATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1200), "Date of Calibration", "DA")
#define TAG_TIME_OF_CALIBRATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1201), "Time of Calibration", "TM")
#define TAG_CONTRIBUTION_DATE_TIME					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0xA002), "Contribution DateTime", "DT")
#define TAG_CONTRIBUTION_DESCRIPTION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0xA003), "Contribution Description", "ST")

// SOP Common Module
// Original Attributes Sequence
#define TAG_ORIGINAL_ATTRIBUTE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0561), "Original Attributes Sequence", "SQ")
#define TAG_PREVIOUS_VALUES_SOURCE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0564), "Source of Previous Values", "CS")
#define TAG_ATTRIBUTE_MODIFICATION_DATE_TIME		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0562), "Attribute Modification DateTime", "DT")
#define TAG_MODIFYING_SYSTEM						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0563), "Modifying System", "LO")
#define TAG_ATTRIBUTE_MODIFICATION_REASON			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0565), "Attribute Modification Reason", "CS")
#define TAG_MODIFIED_ATTRIBUTE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0400, 0x0550), "Modified Attributes Sequence", "SQ")

// Person Identification Macro
#define TAG_PERSON_ID_CODE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x1101), "Person Identification Code Sequence", "SQ")
#define TAG_PERSON_ADDRESS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x1102), "Person's Address", "ST")
#define TAG_PERSON_PHONE_NUMBERS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0040, 0x1103), "Person's Telephone Numbers", "LO")
#define TAG_ORGANIZATION_NAME						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0080), "Organization Name", "LO")
#define TAG_ORGANIZATION_ADDRESS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0081), "Organization Address", "ST")
#define TAG_ORGANIZATION_CODE_SEQ				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0082), "Organization Code Sequence", "SQ")

// Frame of Reference Module Attributes Table 107
#define TAG_FRAME_OF_REFERENCE_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0052), "Frame Of Reference UID", "UI")
#define TAG_POSITION_REFERENCE_INDICATOR			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x1040), "Position Reference Indicator", "LO")

// Overlay Plane Attributes Table 75 (Group is set to 6000 for these variables)
#define TAG_OVERLAY_ROWS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0010), "Overlay Rows", "US")
#define TAG_OVERLAY_COLUMNS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0011), "Overlay Columns", "US")
#define TAG_OVERLAY_TYPE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0040), "Overlay Type", "CS")
#define TAG_OVERLAY_ORIGIN							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0050), "Overlay Origin", "SS")
#define TAG_OVERLAY_BITS_ALLOCATED					SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0100), "Overlay Bits Allocated", "US")
#define TAG_OVERLAY_BIT_POSITION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0102), "Overlay Bit Position", "US")
#define TAG_OVERLAY_DATA							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x3000), "Overlay Data", "OB")
#define TAG_OVERLAY_DESCRIPTION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0022), "Overlay Description", "LO")
#define TAG_OVERLAY_SUBTYPE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x0045), "Overlay Subtype", "LO")
#define TAG_OVERLAY_LABEL							SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x1500), "Overlay Label", "LO")
#define TAG_ROI_AREA								SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x1301), "ROI Area", "IS")
#define TAG_ROI_MEAN								SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x1302), "ROI Mean", "DS")
#define TAG_OVERLAY_STANDARD_DEVIATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x6000, 0x1303), "Overlay Standard Deviation", "DS")

// Threat Sequence Module
#define TAG_THREAT_CATEGORY							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1012), "Threat Category", "CS")
#define TAG_THREAT_CATEGORY_DESCRIPTION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1013), "Threat Category Description", "LT")
#define TAG_ABILITY_ASSESSMENT						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1014), "Ability Assessment", "CS")
#define TAG_ASSESSMENT_FLAG							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1015), "Assessment Flag", "CS")
#define TAG_ASSESSMENT_PROBABILITY					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1016), "Assessment Probability", "FL")
#define TAG_ASSESSMENT_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1038), "Assessment Sequence", "SQ")
#define TAG_SIGNAL_GENERATION_SOFTWARE_VERSIONS		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7008), "Signal Generation Software Versions", "LO")
#define TAG_DYNAMIC_SCREENING_FLAG					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0060, 0x7010), "Dynamic Screening Flag", "CS")

// Shared Baggage Specific TDR and Person Specific TDR
#define TAG_PTO_REPRESENTATION_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1037), "PTO Presentation Sequence", "SQ")
#define TAG_BOUNDING_POLYGON						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101D), "Bounding Polygon", "FL")
#define TAG_PTO_LOCATION_DESCRIPTION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1078), "PTO Location Description", "ST")
#define TAG_CENTER_OF_PTO							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101C), "Center of PTO", "FL")

// Baggage Specific TDR
#define TAG_BOUNDING_BOX_RESOLUTION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1147), "Bounding Box Resolution", "CS")
#define TAG_AGGREGATED_METHOD_FOR_BOUNDING_BOX		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1149), "Aggrregated Method for Bounding Box", "LT")
#define TAG_ROI_RESOLUTION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1247), "ROI Resolution", "CS")
#define TAG_AGGREGATED_METHOD_OF_ROI_RESOLUTION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1249), "Aggregated Method of ROI Resolution", "LT")
#define TAG_CENTER_OF_MASS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x101B), "Center Of Mass", "FL")
#define TAG_MASS_OF_PTO								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1017), "Mass of PTO", "FL")
#define TAG_DENSITY_OF_PTO							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1018), "Density of PTO", "FL")
#define TAG_ZEFFECTIVE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1019), "ZEffective", "FL")
#define TAG_VOLUME_OF_PTO							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1023), "Volume of PTO", "FL")
#define TAG_RHO										SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x8000), "Rho", "FL")
#define TAG_ZEFF_ALTERNATIVE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x6100, 0x8002), "Zeff Alternative", "FL")


//Person Specific TDR
#define TAG_ANOMALY_LOCATOR_INDICATOR_SEQ			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1079), "Anomaly Locator Indicator Sequence", "SQ")
#define TAG_PTO_REGION_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x107B), "PTO Region Sequence", "SQ")
#define TAG_ANOMALY_LOCATOR_INDICATOR				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x107A), "Anomaly Locator Indicator", "FL")


// Tags for Threat ROI Voxel Sequence
#define TAG_THREAT_ROI_VOXEL_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1001), "Threat ROI Voxel Sequence", "SQ")
#define TAG_THREAT_ROI_BASE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1004), "Threat ROI Base", "FL")
#define TAG_THREAT_ROI_EXTENTS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1005), "Threat ROI Extents", "FL")
#define TAG_THREAT_ROI_BITMAP						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x1006), "Threat ROI Bitmap", "OB")

//External References Macro
#define TAG_EXTERNAL_REFERENCES						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x2000), "External References Macro", "ST")

// Tags for attributes that are used by CT, DX, AIT2D, and AIT3D Image Modules
#define TAG_IMAGE_ORIGIN							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x0118), "Image Origin", "CS")
#define TAG_COORDINATE_SYSTEM						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x2108), "Coordinate System", "CS")

//Explosive Trace Detector
#define TAG_SAMPLING_METHOD							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0312), "Sampling Method", "ST")
#define TAG_SAMPLE_TRAP_MEDIA						SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0314), "Sample Trap Media", "ST")
#define TAG_SAMPLE_STATE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0316), "Sample State", "ST")
#define TAG_SAMPLING_WAND_PRESSURE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0318), "Sampling Wand Pressure", "ST")
#define TAG_TYPE_OF_ETD								SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0308), "Type Of ETD", "LT")
#define TAG_MODE_OF_OPERATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0310), "Mode Of Operation", "ST")
#define TAG_DETECTION_ALGORITHMS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0320), "Detection Algorithms", "LO")
#define TAG_ALARM_RESPONSE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0322), "Alarm Response", "ST")
#define TAG_CLEAR_RESPONSE							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0324), "Clear Response", "ST")
#define TAG_ECODES									SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0326), "E-Codes", "ST")
#define TAG_IONIZATION_SOURCE_IMS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0328), "Ionization Source IMS", "ST")
#define TAG_PLASMAGRAM								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0330), "Plasmagram", "ST")
#define TAG_PLASMAGRAM_PEAK_HEIGHT					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0332), "Peak Height", "SL")
#define TAG_PLASMAGRAM_PEAK_WIDTH					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0334), "Peak Width", "SL")
#define TAG_PLASMAGRAM_PEAK_SLOPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0336), "Peak Slope", "SL")
#define TAG_PLASMAGRAM_PEAK_LOCATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0338), "Peak Location", "SL")
#define TAG_PLASMAGRAM_PEAK_THRESHOLD				SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0340), "Peak Threshold", "SL")
#define TAG_MODE_POLARITY							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0342), "Mode Polarity", "SH")
#define TAG_IONIZATION_SOURCE_MS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0344), "Ionization Source MS", "ST")
#define TAG_MASS_SPECTRUM_MS						SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0346), "Mass Spectrum MS", "SH")
#define TAG_MASS_TO_CHARGE_RATIO					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0348), "Mass To Charge Ratio", "SH")
#define TAG_PEAK_INTENSITY_AT_MASS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0350), "Peak Intensity at a Specific Mass", "SH")
#define TAG_SPECTRUM								SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0352), "Spectrum", "SH")
#define TAG_WAVE_NUMBER_IR							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0354), "Wavenumber IR Spectroscopy", "SL")
#define TAG_LASER_WAVE_LENGTH						SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0356), "Laser Wavelength", "SL")
#define TAG_RAMAN_SPECTRUM							SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0358), "Raman Spectrum", "SH")

//#define TAG_Electropherogra						SDICOS::Tags::TagInfo(SDICOS::Tag(0x3300, 0x0360), "Electopherogram", "LT")
//#define TAG_WavenumberRaman;//Spec Error: Same tag as g_tiRamanSpectrum (0x3300, 0x0358), ST

// XRay Equipment
#define TAG_EFFECTIVE_ENERGY						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0902), "Effective Energy", "FL")
#define TAG_TYPE_OF_G0								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0904), "Type of G0", "CS")
#define TAG_MASK_CHARACTERISTICS					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0906), "Mask Characteristics", "ST")
#define TAG_DISTANCE_G0_FROM_XRAY_SOURCE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0908), "Distance G0 from XRay Source", "FL")
#define TAG_TYPE_OF_G1								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0910), "Type of G1", "CS")
#define TAG_DISTANCE_G1_FROM_XRAY_SOURCE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0912), "Distance G1 from XRay Source", "FL")
#define TAG_TYPE_OF_G2								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0914), "Type of G2", "CS")
#define TAG_DISTANCE_G2_FROM_XRAY_SOURCE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0916), "Distance G2 from XRay Source", "FL")
#define TAG_G0_ABSORPTION_PERIOD					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0918), "G0 Absorption Period", "FL")
#define TAG_G1_PHASE_PERIOD							SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0920), "G1 Phase Period", "FL")
#define TAG_G2_ANALYZER_PERIOD						SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0922), "G2 Analyzer Period", "FL")
#define TAG_VISIBILITY								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0924), "Visibility", "FL")
#define TAG_ABSORPTION_XRAY_DETECTOR_SIZE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0926), "Absorption XRay Detector Size", "FL")
#define TAG_ABSORPTION_RECONSTRUCTION_VOXEL_SIZE	SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0928), "Absorption Reconstruction Voxel Size", "FL")
#define TAG_PHASE_XRAY_DETECTOR_SIZE				SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0930), "Phase XRay Detector Size", "FL")
#define TAG_PHASE_RECONSTRUCTION_VOXEL_SIZE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0932), "Phase Reconstruction Voxel Size", "FL")
#define TAG_DARK_IMAGE_XRAY_DETECTOR_SIZE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0934), "Dark Image XRay Detector Size", "FL")
#define TAG_DARK_IMAGE_RECONSTRUCTION_VOXEL_SIZE	SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0936), "Dark Image Reconstruction Voxel Size", "FL")
#define TAG_PHASE_IMAGE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0938), "Reconstruction Algorithm for Phase Image", "CS")
#define TAG_DARK_IMAGE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x4300, 0x0940), "Reconstruction Algorithm for Dark Image", "CS")

// Plane Orientation
#define TAG_PLANE_ORIENTATION_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9116), "Plane Orientation Sequence", "SQ")

// Plane Position
#define TAG_PLANE_POSITION_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9113), "Plane Position Sequence", "SQ")


// AIT PRCS to RCS Transformation
#define TAG_PRCS_TO_RCS_ORIENTATION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x4010, 0x107E), "PRCS To RCS Orientation Vectors. (6 values).", "DS")


// General Image Moduke
#define TAG_REFERENCED_IMAGE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1140), "Referenced Image Sequence", "SQ")
#define TAG_DERIVATION_DESCRIPTION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x2111), "Derivation Description", "ST")
#define TAG_DERIVATION_CODE_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9215), "Derivation Code Sequence", "SQ")
#define TAG_SOURCE_IMAGE_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x2112), "Source Image Sequence", "SQ")
#define TAG_NUMBER_OF_IMAGES_IN_ACQUISITION			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x1002), "Number of Images in Acquisition", "IS")
#define TAG_QUALITY_CONTROL_IMAGE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0300), "Quality Control Image", "CS")
#define TAG_LOSSY_IMAGE_COMPRESSION					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2110), "Lossy Image Compression", "CS")
#define TAG_LOSSY_IMAGE_COMPRESSION_RATIO			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2112), "Lossy Image Compression Ratio", "DS")
#define TAG_LOSSY_IMAGE_COMPRESSION_METHOD			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x2114), "Lossy Image Compression Method", "CS")
#define TAG_SPATIAL_LOCATIONS_PRESERVED				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x135A), "Spatial Locations Preserved", "CS")


#define TAG_COMMAND_GROUP_LENGTH					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0000), "Command Group Length", "UL")
#define TAG_AFFECTED_SOP_CLASS_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0002), "Affected SOP Class UID", "UI")
#define TAG_COMMAND_FIELD							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0100), "Command Field", "US")
#define TAG_MESSAGE_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0110), "Message ID", "US")
#define TAG_PRIORITY								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0700), "Priority", "US")
#define TAG_DATASET									SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0800), "Data Set", "US")
#define TAG_STATUS									SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0900), "Status", "US")
#define TAG_WARNING_TAG_LIST						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0901), "Warning Tag List", "AT")
#define TAG_COMMENT									SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0902), "Comment", "LO")
#define TAG_ERROR_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x0903), "Error ID", "US")
#define TAG_AFFECTED_SOP_INSTANCE_UID				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x1000), "Affected SOP Instance UID", "UI")
#define TAG_UNKNOWN_TAG_LIST						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x1005), "Unknown Tag List", "AT")
#define TAG_MOVE_ORIGINATOR_AE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x1030), "Move Originator Application Entity", "AE")
#define TAG_MOVE_ORIGINATOR_ID						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0000, 0x1031), "Move Originator ID", "US")


// Multiframe Functional Groups
#define TAG_MFFG_SHARED_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x5200, 0x9229), "Shared Functional Group Sequence", "SQ")
#define TAG_MFFG_PER_FRAME_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x5200, 0x9230), "Per-Frame Functional Group Sequence", "SQ")
#define TAG_MFFG_CONCATENATION_FRAME_OFFSET_NUMBER	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9228), "Concatenation Frame Offset Number", "UL")
#define TAG_MFFG_REPRESENTATIVE_FRAME_NUMBER		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x6010), "Representative Frame Number", "US")
#define TAG_MFFG_CONCATENATION_SOURCE_SOP_INSTANCE_UID	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0242), "SOP Instance UID of Concatenation Source", "UI")
#define TAG_MFFG_CONCATENATION_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9161), "Concatenation UID", "UI")
#define TAG_MFFG_INCONCATENATION_NUMBER				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9162), "In-concatenation Number", "US")
#define TAG_MFFG_INCONCATENATION_TOTAL_NUMBER		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9163), "In-concatenation Total Number", "US")


// Pixel Spacing Calibration Macro
#define TAG_PIXEL_SPACING_CALIBRATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0030), "Pixel Spacing", "DS")
#define TAG_PIXEL_SPACING_CALIBRATION_TYPE			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0A02), "Pixel Spacing Calibration Type", "CS")
#define TAG_PIXEL_SPACING_CALIBRATION_DESCRIPTION	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0A04), "Pixel Spacing Calibration Description", "LO")


// Common Image Attributes
#define TAG_PIXEL_PRESENTATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9205), "Pixel Presentation", "CS")
#define TAG_VOLUMETRIC_PROPERTIES					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9206), "Volumetric Properties", "CS")
#define TAG_VOLUME_BASED_CALCULATION_TECHNIQUE		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9207), "Volume Based Calculation Technique", "CS")
#define TAG_PIXEL_INTENSITY_RELATIONSHIP			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1040), "Pixel Intensity Relationship", "CS")
#define TAG_PIXEL_INTENSITY_RELATIONSHIP_SIGN		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x1041), "Pixel Intensity Relationship Sign", "SS")


// XRay Generation
#define TAG_KVP										SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x0060), "KVP", "DS")
#define TAG_IMAGE_ORIENTATION						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0037), "Image Orientation Vectors. (6 values).", "DS")
#define TAG_IMAGE_POSITION							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x0032), "Image Position", "DS")
#define TAG_XRAY_TUBE_CURRENT						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x8151), "XRay Tube Current", "DS")
#define TAG_EXPOSURE_TIME							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x8150), "Exposure Time", "DS")
#define TAG_EXPOSURE								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1153), "Exposure", "IS")
#define TAG_EXPOSURE_CONTROL_MODE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7060), "Exposure Control Mode", "CS")
#define TAG_EXPOSURE_CONTROL_MODE_DESCRIPTION		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7062), "Exposure Control Mode Description", "LT")
#define TAG_EXPOSURE_STATUS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7064), "Exposure Status", "CS")
#define TAG_PHOTO_TIMER_SETTING						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7065), "Photo Timer Setting", "DS")
#define TAG_FOCAL_NOMINAL_SPOT_SIZE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1190), "Focal Nominal Spot Size", "DS")
#define TAG_ANODE_TARGET_MATERIAL					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1191), "Anode Target Material", "CS")
#define TAG_RECTIFICATION_TYPE						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1156), "Rectification Type", "CS")
#define TAG_GENERATOR_ID							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1005), "Generator ID", "LO")


// XRay Filtration
#define TAG_XRAY_FILTRATION_TYPE					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x1160), "XRay Filtration Type", "SH")
#define TAG_XRAY_FILTRATION_MATERIAL				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7050), "XRay Filtration Material", "CS")
#define TAG_XRAY_FILTRATION_THICKNESS_MIN			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7052), "XRay Filtration Thickness Min", "DS")
#define TAG_XRAY_FILTRATION_THICKNESS_MAX			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x7054), "XRay Filtration Thickness Max", "DS")


// CT XRay Details
#define TAG_CT_XRAY_DETAILS_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9325), "XRay Details Sequence", "SQ")


// Derivation Image Macro Attributes
#define TAG_DERIVATION_IMAGE_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x9124), "Derivation Image Sequence", "SQ")
#define TAG_DERIVATION_IMAGE_MACRO_DESCRIPTION		TAG_DERIVATION_DESCRIPTION
#define TAG_DERIVATION_IAMGE_MACRO_CODE_SEQ			TAG_DERIVATION_CODE_SEQ	


// Referenced Series
#define TAG_SOP_INSTANCE_REFERENCES_SEQ				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x114A), "SOP Instance References Sequence", "SQ")


// Pixel Intensity Relationship LUT Macro
#define TAG_PIXEL_INTENSITY_RELATIONSHIP_LUT_SEQ		SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x9422), "Pixel Intensity Relationship LUT Sequence", "SQ")
#define TAG_PIXEL_INTENSITY_RELATIONSHIP_LUT_FUNCTION	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x9474), "Pixel Intensity Relationship LUT Function", "CS")


// Pixel Measures Macro
#define TAG_PIXEL_MEASURES_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x9110), "Pixel Measures Sequence", "SQ")
#define TAG_PIXEL_MEASURES_SPACING					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0028, 0x0030), "Pixel Spacing", "DS")
#define TAG_PIXEL_MEASURES_SLICE_THICKNESS			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x0050), "Slice Thickness", "DS")


// Frame VOI LUT
#define TAG_FRAME_VOI_LUT_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0X0028, 0x9132), "Frame VOI LUT Sequence", "SQ")


// Common Instance Reference Module
#define TAG_OTHER_REFERENCED_INSTANCES_SEQ			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1200), "Scans Containing Other Referenced Instance Sequences", "SQ")


// Series and Instance Reference Macro
#define TAG_REFERENCED_SERIES_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1115), "Referenced Series Sequence", "SQ")


// SOP Instance Reference Macro
#define TAG_REFERENCED_SOP_CLASS_UID				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1150), "Referenced SOP Class UID", "UI")
#define TAG_REFERENCED_SOP_INSTANCE_UID				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1155), "Referenced SOP Instance UID", "UI")


// Frame Content Macro
#define TAG_FRAME_CONTENT_SEQ						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9111), "Frame Content Sequence", "SQ")
#define TAG_FRAME_ACQUISITION_NUMBER				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9156), "Frame Acquisition Number", "DT")
#define TAG_FRAME_REFERENCE_DATE_TIME				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9151), "Frame Reference Date Time", "DT")
#define TAG_FRAME_ACQUISITION_DATE_TIME				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9074), "Frame Acquisition Date Time", "DT")
#define TAG_FRAME_ACQUISITION_DURATION				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0018, 0x9220), "Frame Acquisition Duration", "FD")
#define TAG_DIMENSION_INDEX_VALUES					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9157), "Dimension Index Values", "UL")
#define TAG_TEMPORAL_POSITION_INDEX					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9128), "Temporal Position Index", "UL")
#define TAG_STACK_ID								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9056), "Stack ID", "SH")
#define TAG_IN_STACK_POSITION_NUMBER				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9057), "In Stack Position Number", "UL")
#define TAG_FRAME_COMMENTS							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9158), "Frame Comments", "LT")
#define TAG_FRAME_LABEL								SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9453), "Frame Label", "LO")


// Image SOP Instance Reference Macro
#define TAG_REFERENCED_FRAME_NUMBERS				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0008, 0x1160), "Referenced Frame Number", "IS")
#define TAG_REFERENCED_SEGMENT_NUMBERS				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0062, 0x000B), "Referenced Segment Number", "US")


// Multiframe Dimension Module
#define TAG_DIMENSION_ORGANIZATION_SEQ					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9221), "Dimension Organization Sequence", "SQ")
#define TAG_DIMENSION_ORGANIZATION_UID					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0X9164), "Dimension Organization UID", "UI")
#define TAG_DIMENSION_INDEX_SEQ							SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0X9222), "Dimension Index Sequence", "SQ")							 
#define TAG_DIMENSION_INDEX_POINTER						SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9165), "Dimension Index Pointer", "AT")
#define TAG_DIMENSION_INDEX_PRIVATE_CREATOR				SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9213), "Dimension Index Private Creator", "LO")
#define TAG_DIMENSION_FUNCTIONAL_GROUP_POINTER			SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9167), "Functional Group Pointer", "AT")
#define TAG_DIMENSION_FUNCTIONAL_GROUP_PRIVATE_CREATOR	SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9238), "Functional Group Private Creator", "LO")
#define TAG_DIMENSION_DESCRIPTION_LABEL					SDICOS::Tags::TagInfo(SDICOS::Tag(0x0020, 0x9421), "Dimension Description Label", "LO")

#endif /* _STRATOVAN_DICOS_TAGDEFINES_H_ */
