//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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

#ifndef _STRATOVAN_DICOS_MEMORY_POLICY_H_
#define	_STRATOVAN_DICOS_MEMORY_POLICY_H_

namespace SDICOS
{
	namespace MemoryPolicy
	{
		/// \enum VOLUME_MEMORY_POLICY
		/// Memory allocation policy for a image data
		typedef enum
		{
			DOES_NOT_OWN_SLICES = 0x0,	///< Volume is not responsible for deleting its slices.
			OWNS_SLICES = 0x1,			///< Volume is responsible for deleting its slices

			DOES_NOT_OWN_DATA = DOES_NOT_OWN_SLICES, ///< Object is not responsible for deleting its slices.
			OWNS_DATA = OWNS_SLICES,				 ///< Object is responsible for deleting its slices
								
			MEMORY_POLICY_UNKNOWN = 0xFFFFFFFF
		} VOLUME_MEMORY_POLICY;

		/// Returns true if the passed in value is a valid VOLUME_MEMORY_POLICY enumeration
		bool IsValidMemoryPolicy(const VOLUME_MEMORY_POLICY nMemoryPolicy);
	}
}

#endif	/* _STRATOVAN_DICOS_MEMORY_POLICY_H_ */

