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
#ifndef _STRATOVAN_DICOS_VR_H_
#define _STRATOVAN_DICOS_VR_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/Tag.h"

namespace SDICOS
{

///
/// Find the VR based on the group and element numbers
///
/// @param nGroup Group number
/// @param nElement Element number
/// @param strVR Output VR
/// @param attribmanager Attribute Manager
/// @return true/false
///
bool FindVR(const S_UINT16 nGroup, const S_UINT16 nElement, DcsString &strVR, const AttributeManager &attribmanager);

/// @see FindVR(const S_UINT16 nGroup, const S_UINT16 nElement, DcsString &strVR, const AttributeManager &attribmanager)
bool FindVR(const Tag& tag, DcsString &strVR, const AttributeManager &attribmanager);

/// Ask if the given (group, element) pair is a valid DICOS tag
bool IsDICOSTag(const S_UINT16 nGroup, const S_UINT16 nElement, const AttributeManager &attribmanager);

/// Ask if the given (group, element) pair is a valid DICOS tag
bool IsDICOSTag(const Tag &tag, const AttributeManager &attribmanager);

}//namespace SDICOS

#endif