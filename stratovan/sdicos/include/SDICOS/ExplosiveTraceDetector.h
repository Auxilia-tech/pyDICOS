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
#ifndef _STRATOVAN_DICOS_EXPLOSIVE_TRACE_DETECTOR_H_
#define _STRATOVAN_DICOS_EXPLOSIVE_TRACE_DETECTOR_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class ExplosiveTraceDetector
/// \brief Implements Explosive Trace Detector Module
/// SPECREF V03 Section 11.2, Table 64
/// 
class ExplosiveTraceDetector
{
public:
	/// Constructor
	ExplosiveTraceDetector();
	/// Copy constructor
	/// @param rhs Initialize with this object
	ExplosiveTraceDetector(const ExplosiveTraceDetector& rhs);
	/// Destructor
	virtual ~ExplosiveTraceDetector();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	/// @param rhs Copy this object
	/// @return Reference to this object
	ExplosiveTraceDetector& operator=(const ExplosiveTraceDetector& rhs);
	/// Comparison operator
	/// @param rhs Compare to this object
	/// @return true/false
	bool operator==(const ExplosiveTraceDetector& rhs)const;
	/// Comparison operator
	/// @param rhs Compare to this object
	/// @return true/false
	bool operator!=(const ExplosiveTraceDetector& rhs)const;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager& attribManager, ErrorLog& errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager& attribManager, ErrorLog& errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager& attribManager, ErrorLog& errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager& attribManager, ErrorLog& errorlog)const;

	/// Sampling Method : Tag(3300, 0312), VR = ST [required]
	/// Method by which sample is acquired: hand sampling, wand, external device that collects the sample
	/// @param str Sampling Method
	/// @return true/false if value was set
	bool SetSamplingMethod(const DcsShortText &str);
	/// @return Sampling Method
	/// @see SetSamplingMethod
	DcsShortText GetSamplingMethod()const;

	/// Sample Trap Media : Tag(3300, 0314), VR = ST [required]
	/// Composition of sample trap:	nomex, paper, teflon, metal mesh, chemically enhanced trap
	/// @param str Sample Trap Media
	/// @return true/false if value was set
	bool SetSampleTrapMedia(const DcsShortText& str);
	/// @return Sample Trap Media
	/// @see SetSampleTrapMedia
	DcsShortText GetSampleTrapMedia()const;
	
	/// Sample State : Tag(3300, 0316), VR = ST [required]
	/// Sample state of explosive(s) or chemical substance(s) being analyzed, particle or vapor
	/// @param str Sample State
	/// @return true/false if value was set
	bool SetSampleState(const DcsShortText& str);
	/// @return Sample State
	/// @see SetSampleState
	DcsShortText GetSampleState()const;

	/// Sampling Wand Pressure : Tag(3300, 0318), VR = ST [required]
	/// Certain wands are built to measure pressure applied during sample collection 
	/// with a sample trap.
	/// @param str Sampling Wand Pressure
	/// @return true/false if value was set
	bool SetSamplingWandPressure(const DcsShortText& str);
	/// @return Sampling Wand Pressure
	/// @see SetSamplingWandPressure
	DcsShortText GetSamplingWandPressure()const;

	/// Type Of ETD : Tag(3300, 0308), VR = LT [required]
	/// Identifies the technology type of ETD
	/// @param str Sampling Wand Pressure
	/// @return true/false if value was set
	bool SetTypeOfETD(const DcsLongText& str);
	/// @return Type Of ETD
	/// @see SetTypeOfETD
	DcsLongText GetTypeOfETD()const;

	/// Mode Of Operation : Tag(3300, 0310), VR = ST [required]
	/// The mode of operation of the unit
	/// @param str Sampling Wand Pressure
	/// @return true/false if value was set
	bool SetModeOfOperation(const DcsShortText& str);
	/// @return Mode Of Operation
	/// @see SetModeOfOperation
	DcsShortText GetModeOfOperation()const;

	/// Detection Algorithms : Tag(3300, 0320), VR = LO [required]
	/// Separate Algorithm for each explosive or chemical substance.
	/// An algorithm consists of the requirements that must be met for 
	/// the system to give an alarm response for an explosive or chemical substance
	/// @param str Detection Algorithms
	/// @return true/false if value was set
	bool SetDetectionAlgorithms(const DcsLongString& str);
	/// @return Detection Algorithms
	/// @see SetDetectionAlgorithms
	DcsLongString GetDetectionAlgorithms()const;

	/// Alarm Response : Tag(3300, 0322), VR = ST [required]
	/// Indication that the system detected explosive(s) or 
	/// chemical substance(s).The requirements set out in the 
	/// algorithm(s) were met
	/// @param str Alarm Response
	/// @return true/false if value was set
	bool SetAlarmResponse(const DcsShortText& str);
	/// @return Alarm Response
	/// @see SetAlarmResponse
	DcsShortText GetAlarmResponse()const;

	/// Clear Response : Tag(3300, 0324), VR = ST [required]
	/// Indication that no explosive(s) or chemical substance(s) 
	/// were detected.The requirements in the algorithm(s) were not met
	/// @param str Clear Response
	/// @return true/false if value was set
	bool SetClearResponse(const DcsShortText& str);
	/// @return Clear Response
	/// @see SetClearResponse
	DcsShortText GetClearResponse()const;

	/// E-Codes : Tag(3300, 0326), VR = ST [required]
	/// E-Codes for the explosive(s) or chemical substance(s) 
	/// that the system alarmed on
	/// @param str E-Codes
	/// @return true/false if value was set
	bool SetECodes(const DcsShortText& str);
	/// @return E-Codes
	/// @see SetECodes
	DcsShortText GetECodes()const;

	/// Ionization Source IMS : Tag(3300, 0328), VR = ST [optional]
	/// The type of ionization source used to impart charge to 
	/// molecules to be analyzed in IMS
	/// @param str Ionization Source IMS
	/// @return true/false if value was set
	bool SetIonizationSourceIMS(const DcsShortText& str);
	/// @return Ionization Source IMS
	/// @see SetIonizationSourceIMS
	DcsShortText GetIonizationSourceIMS()const;
	/// @return true/false if attribute is present
	bool HasIonizationSourceIMS()const;
	/// Delete attribute
	void DeleteIonizationSourceIMS();

	/// Plasmagram : Tag(4300, 0330), VR = ST [optional]
	/// An intensity vs. time plot representing an IMS 
	/// analysis of an explosive or chemical substance.
	/// Hence, the mass plasmagram of a sample is a pattern 
	/// representing the distribution of ions by time to 
	/// arrive at the detector in a sample
	/// @param str Plasmagram
	/// @return true/false if value was set
	bool SetPlasmagram(const DcsShortText& str);
	/// @return Plasmagram
	/// @see SetPlasmagram
	DcsShortText GetPlasmagram()const;
	/// @return true/false if attribute is present
	bool HasPlasmagram()const;
	/// Delete attribute
	void DeletePlasmagram();

	/// Peak Height : Tag(3300, 0332), VR = SL [optional]
	/// Height of peak in the plasmagram
	/// @param nVal Peak Height
	/// @return true/false if value was set
	bool SetPlasmagramPeakHeight(const S_INT32 nVal);
	/// @return Peak Height
	/// @see SetPlasmagramPeakHeight
	S_INT32 GetPlasmagramPeakHeight()const;
	/// @return true/false if attribute is present
	bool HasPlasmagramPeakHeight()const;
	/// Delete attribute
	void DeletePlasmagramPeakHeight();

	/// Peak Width : Tag(3300, 0334), VR = SL [optional]
	/// Width of peak in the plasmagram
	/// @param nVal Peak Width
	/// @return true/false if value was set
	bool SetPlasmagramPeakWidth(const S_INT32 nVal);
	/// @return Peak Width
	/// @see SetPlasmagramPeakWidth
	S_INT32 GetPlasmagramPeakWidth()const;
	/// @return true/false if attribute is present
	bool HasPlasmagramPeakWidth()const;
	/// Delete attribute
	void DeletePlasmagramPeakWidth();

	/// Peak Slope : Tag(3300, 0336), VR = SL [optional]
	/// Peak Slope in the plasmagram
	/// @param nVal Peak Slope
	/// @return true/false if value was set
	bool SetPlasmagramPeakSlope(const S_INT32 nVal);
	/// @return Peak Slope
	/// @see SetPlasmagramPeakSlope
	S_INT32 GetPlasmagramPeakSlope()const;
	/// @return true/false if attribute is present
	bool HasPlasmagramPeakSlope()const;
	/// Delete attribute
	void DeletePlasmagramPeakSlope();

	/// Peak Location : Tag(3300, 0338), VR = SL [optional]
	/// Location of peak in the plasmagram (milliseconds).
	/// @param nVal Peak Location
	/// @return true/false if value was set
	bool SetPlasmagramPeakLocation(const S_INT32 nVal);
	/// @return Peak Location
	/// @see SetPlasmagramPeakLocation
	S_INT32 GetPlasmagramPeakLocation()const;
	/// @return true/false if attribute is present
	bool HasPlasmagramPeakLocation()const;
	/// Delete attribute
	void DeletePlasmagramPeakLocation();

	/// Peak Threshold : Tag(3300, 0340), VR = SL [optional]
	/// Peak Thresholds defined in the algorithm required for alarm response
	/// @param nVal Peak Threshold
	/// @return true/false if value was set
	bool SetPlasmagramPeakThreshold(const S_INT32 nVal);
	/// @return Peak Threshold
	/// @see SetPlasmagramPeakThreshold
	S_INT32 GetPlasmagramPeakThreshold()const;
	/// @return true/false if attribute is present
	bool HasPlasmagramPeakThreshold()const;
	/// Delete attribute
	void DeletePlasmagramPeakThreshold();

	/// Mode Polarity : Tag(3300, 0342), VR = SH [optional]
	/// Negative or Positive Mode (Negative or positive ions detected.) For IMS systems.
	/// @param str Mode Polarity
	/// @return true/false if value was set
	bool SetModePolarity(const DcsShortString& str);
	/// @return Mode Polarity
	/// @see SetModePolarity
	DcsShortString GetModePolarity()const;
	/// @return true/false if attribute is present
	bool HasModePolarity()const;
	/// Delete attribute
	void DeleteModePolarity();

	/// Ionization Source MS : Tag(3300, 0344), VR = ST [optional]
	/// The type of ionization source used to impart charge to 
	/// molecules to be analyzed in an MS
	/// @param str Ionization Source MS
	/// @return true/false if value was set
	bool SetIonizationSourceMS(const DcsShortText& str);
	/// @return Ionization Source MS
	/// @see SetIonizationSourceMS
	DcsShortText GetIonizationSourceMS()const;
	/// @return true/false if attribute is present
	bool HasIonizationSourceMS()const;
	/// Delete attribute
	void DeleteIonizationSourceMS();

	/// Mass Spectrum MS : Tag(3300, 0346), VR = SH [optional]
	/// An intensity vs. m/z (mass-to-charge ratio) plot representing 
	/// an MS analysis of an explosive or chemical substance.
	/// Hence, the mass spectrum of a sample is a pattern representing 
	/// the distribution of ions by mass (more correctly : mass-to-charge ratio) 
	/// in a sample
	/// @param vstr Mass Spectrum MS
	/// @return true/false if value was set
	bool SetMassSpectrumMS(const Array1D<DcsShortString>& vstr);
	/// Get Mass Spectrum MS
	/// @param vstr Mass Spectrum MS
	/// @return true/false if attribute is present
	/// @see SetMassSpectrumMS
	bool GetMassSpectrumMS(Array1D<DcsShortString>& vstr)const;
	/// @return Reference to attribute
	Array1D<DcsShortString>& GetMassSpectrumMS();
	/// @return Reference to attribute
	const Array1D<DcsShortString>& GetMassSpectrumMS()const;
	/// @return true/false if attribute is present
	bool HasMassSpectrumMS()const;
	/// Delete attribute
	void DeleteMassSpectrumMS();

	/// Mass To Charge Ratio : Tag(3300, 0348), VR = SH [optional]
	/// Mass to charge ratio of selected peaks in an MS spectrum.
	/// Plotted as a function of intensity.
	/// @param str Mass To Charge Ratio
	/// @return true/false if value was set
	bool SetMassToChargeRatio(const DcsShortString& str);
	/// @return Mass To Charge Ratio at a Specific Mass
	/// @see SetMassToChargeRatioAtMass
	DcsShortString GetMassToChargeRatio()const;
	/// @return true/false if attribute is present
	bool HasMassToChargeRatio()const;
	/// Delete attribute
	void DeleteMassToChargeRatio();

	/// Peak Intensity at a Specific Mass : Tag(3300, 0350), VR = SH [optional]
	/// Peak intensity at a specific mass to charge ratio in an MS spectrum.
	/// @param str Peak Intensity at a Specific Mass
	/// @return true/false if value was set
	bool SetPeakIntensityAtMass(const DcsShortString& str);
	/// @return Peak Intensity at a Specific Mass
	/// @see SetPeakIntensityAtMass
	DcsShortString GetPeakIntensityAtMass()const;
	/// @return true/false if attribute is present
	bool HasPeakIntensityAtMass()const;
	/// Delete attribute
	void DeletePeakIntensityAtMass();

	/// Spectrum : Tag(3300, 0352), VR = SH [optional]
	/// A transmittance vs. wavenumber(measured in 1/cm) plot 
	/// representing an IR analysis of an explosive or chemical 
	/// substance. Hence, the spectrum of a sample is a pattern 
	/// representing the distribution of molecules by wavenumber 
	/// in a sample
	/// @param vstr Spectrum
	/// @return true/false if value was set
	bool SetSpectrum(const Array1D<DcsShortString>& vstr);
	/// Get Spectrum
	/// @param vstr Spectrum
	/// @return true/false if attribute is present
	/// @see SetSpectrum
	bool GetSpectrum(Array1D<DcsShortString>& vstr)const;
	/// @return Reference to attribute
	Array1D<DcsShortString>& GetSpectrum();
	/// @return Reference to attribute
	const Array1D<DcsShortString>& GetSpectrum()const;
	/// @return true/false if attribute is present
	bool HasSpectrum()const;
	/// Delete attribute
	void DeleteSpectrum();

	/// Wavenumber (IR Spectroscopy) : Tag(3300, 0354), VR = SL [optional]
	/// Measured in 1/cm. Location of peak(s) in the IR Spectrum. Function 
	/// of transmittance
	/// @param nVal Wavenumber
	/// @return true/false if value was set
	bool SetWavenumberIR(const S_INT32 nVal);
	/// @return Wavenumber
	/// @see SetWavenumberIR
	S_INT32 GetWavenumberIR()const;
	/// @return true/false if attribute is present
	bool HasWavenumberIR()const;
	/// Delete attribute
	void DeleteWavenumberIR();

	/// Laser Wavelength : Tag(3300, 0356), VR = SL [optional]
	/// Wavelength of light used to interact with the sample. 
	/// Used for Raman Spectroscopy
	/// @param nVal Laser Wavelength
	/// @return true/false if value was set
	bool SetLaserWavelength(const S_INT32 nVal);
	/// @return Laser Wavelength
	/// @see SetLaserWavelength
	S_INT32 GetLaserWavelength()const;
	/// @return true/false if attribute is present
	bool HasLaserWavelength()const;
	/// Delete attribute
	void DeleteLaserWavelength();

	/// Raman Spectrum : Tag(3300, 0358), VR = SH [optional]
	/// An intensity vs. wavenumber (Raman shift) plot representing 
	/// a Raman analysis of an explosive or chemical substance.
	/// Raman shift is the difference in frequency between the 
	/// laser light and the scattered light from interaction 
	/// with sample molecules
	/// @param vstr Raman Spectrum
	/// @return true/false if value was set
	bool SetRamanSpectrum(const Array1D<DcsShortString>& vstr);
	/// Get Raman Spectrum
	/// @param vstr Raman Spectrum
	/// @return true/false if attribute is present
	/// @see SetRamanSpectrum
	bool GetRamanSpectrum(Array1D<DcsShortString>& vstr)const;
	/// @return Reference to attribute
	Array1D<DcsShortString>& GetRamanSpectrum();
	/// @return Reference to attribute
	const Array1D<DcsShortString>& GetRamanSpectrum()const;
	/// @return true/false if attribute is present
	bool HasRamanSpectrum()const;
	/// Delete attribute
	void DeleteRamanSpectrum();

protected:
	class Impl;
	Impl* m_pImpl; ///< Internal implementation

	Impl* GetImpl();
	const Impl* GetImpl()const;
};

}

#endif
