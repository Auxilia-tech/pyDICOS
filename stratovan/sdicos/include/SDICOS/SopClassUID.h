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
#ifndef _STRATOVAN_DICOS_SOP_CLASS_UID_H_
#define _STRATOVAN_DICOS_SOP_CLASS_UID_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"

namespace SDICOS
{
namespace SOPClassUID
{

// 8-16 bit pixel data
DcsString GetCT();				///< CT SOP Class UID (16bit integer pixel data)
DcsString GetCTRaw();			///< CT Raw (SDI) SOP Class UID (16bit integer pixel data)
DcsString GetCTCorrected();		///< CT Corrected (CDI) SOP Class UID (16bit integer pixel data)
DcsString GetDXProcessing();	///< DX SOP Class UID for processing (16bit integer pixel data)
DcsString GetDXPresentation();	///< DX SOP Class UID for presentation (16bit integer pixel data)
DcsString GetAIT2D();			///< AIT2D SOP Class UID (16bit integer pixel data)
DcsString GetAIT2DRaw();		///< AIT2D Raw SOP Class UID (16bit integer pixel data)
DcsString GetAIT3D();			///< AIT3D SOP Class UID (16bit integer pixel data)
DcsString GetAIT3DRaw();		///< AIT3D Raw OP Class UID (16bit integer pixel data)
DcsString GetQR();				///< QR SOP Class UID (16bit integer pixel data)
DcsString GetTDR();				///< TDR SOP Class UID (16bit integer pixel data)
DcsString GetETD();				///< ETD SOP Class UID
DcsString GetXRD();				///< XRD SOP Class UID
DcsString GetHDAIT();			///< HDAIT SOP Class UID

// 32bit pixel data
DcsString GetCT_32Bit();				///< CT SOP Class UID (32bit integer pixel data)
DcsString GetCTRaw_32Bit();				///< CT Raw (SDI) SOP Class UID (32bit integer pixel data)
DcsString GetCTCorrected_32Bit();		///< CT Corrected (CDI) SOP Class UID (32bit integer pixel data)
DcsString GetDXProcessing_32Bit();		///< DX SOP Class UID for processing (32bit integer pixel data)
DcsString GetDXPresentation_32Bit();	///< DX SOP Class UID for presentation (32bit integer pixel data)
DcsString GetAIT2D_32Bit();				///< AIT2D SOP Class UID (32bit integer pixel data)
DcsString GetAIT2DRaw_32Bit();			///< AIT2D Raw SOP Class UID (32bit integer pixel data)
DcsString GetAIT3D_32Bit();				///< AIT3D SOP Class UID (32bit integer pixel data)
DcsString GetAIT3DRaw_32Bit();			///< AIT3D Raw SOP Class UID (32bit integer pixel data)

// 64bit pixel data
DcsString GetCT_64Bit();				///< CT SOP Class UID (64bit integer pixel data)
DcsString GetCTRaw_64Bit();				///< CT Raw (SDI) SOP Class UID (64bit integer pixel data)
DcsString GetCTCorrected_64Bit();		///< CT Corrected (CDI) SOP Class UID (64bit integer pixel data)
DcsString GetDXProcessing_64Bit();		///< DX SOP Class UID for processing (64bit integer pixel data)
DcsString GetDXPresentation_64Bit();	///< DX SOP Class UID for presentation (64bit integer pixel data)
DcsString GetAIT2D_64Bit();				///< AIT2D SOP Class UID (64bit integer pixel data)
DcsString GetAIT3D_64Bit();				///< AIT3D SOP Class UID (64bit integer pixel data)

// 32 & 64 bit float pixel data
// Check Bits Allocated to determine between float and double
DcsString GetCT_Float();				///< CT SOP Class UID (32bit float pixel data)
DcsString GetCTRaw_Float();				///< CT Raw (SDI) SOP Class UID for processing (32 or 64 bit float pixel data)
DcsString GetCTCorrected_Float();		///< CT Corrected (CDI) SOP Class UID for processing (32 or 64 bit float pixel data)
DcsString GetDXProcessing_Float();		///< DX SOP Class UID for processing (32 or 64 bit float pixel data)
DcsString GetDXPresentation_Float();	///< DX SOP Class UID for presentation (32 or 64 bit float pixel data)
DcsString GetAIT2D_Float();				///< AIT2D SOP Class UID (32 or 64 bit float pixel data)
DcsString GetAIT2DRaw_Float();			///< AIT2D Raw SOP Class UID (32 or 64 bit float pixel data)
DcsString GetAIT3D_Float();				///< AIT3D SOP Class UID (32 or 64 bit float pixel data)
DcsString GetAIT3DRaw_Float();			///< AIT3D Raw SOP Class UID (32 or 64 bit float pixel data)

/// Return true if dcsSOPClassUID == GetCT() for 16, 32, 64, float
bool IsCTSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetDXProcessing() for 16, 32, 64, float
bool IsDXProcessingSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetDXPresentation() for 16, 32, 64, float
bool IsDXPresentationSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetAIT2D() for 16, 32, 64, float
bool IsAIT2DSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetAIT3D() for 16, 32, 64, float
bool IsAIT3DSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetTDR()
bool IsTDRSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetQR()
bool IsQRSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetHDAIT()
bool IsHDAITSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetXRD()
bool IsXRDSOPClassUID(const DcsString& dcsSOPClassUID);

/// Return true if dcsSOPClassUID == GetETD()
bool IsETDSOPClassUID(const DcsString& dcsSOPClassUID);

/// Returns true if SOP Class UID is for QR or TDR
bool IsNoPixelDataSOPClassUID(const DcsString& dcsSOPClassUID);
/// Returns true if SOP Class UID is for 8-16bit pixel data
bool Is16BitMaxPixelDataSOPClassUID(const DcsString& dcsSOPClassUID);
/// Returns true if SOP Class UID is for 32bit integer pixel data
bool Is32BitPixelDataSOPClassUID(const DcsString& dcsSOPClassUID);
/// Returns true if SOP Class UID is for 64bit integer pixel data
bool Is64BitPixelDataSOPClassUID(const DcsString& dcsSOPClassUID);
/// Returns true if SOP Class UID is for 32 or 64 bit float pixel data
bool IsFloatPixelDataSOPClassUID(const DcsString& dcsSOPClassUID);
/// Add SOP Class UIDs to the passed in Array for all SOP Classes that support network transmission
void GetListOfNetworkSupportedSopClassUIDs(Array1D<DcsUniqueIdentifier> &vSopClassUIDs);

}//namespace UID
}//SDICOS

#endif
