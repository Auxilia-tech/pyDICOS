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
#ifndef _STRATOVAN_DICOS_TYPES_H_
#define _STRATOVAN_DICOS_TYPES_H_

#ifndef S_ASSERT			
	#ifdef _DEBUG
		#ifdef WIN32
			#include <crtdbg.h>
			#define S_ASSERT(exp)	_ASSERT(exp)				///< Assertion testing
		#else
			#include <assert.h>
			#define S_ASSERT(exp)	assert(exp)					///< Assertion testing
		#endif
		#define S_VERIFY(exp)		S_ASSERT(exp)				///< Verify an expression is true, expression IS evaluated during a release build
	#else
		#define S_ASSERT(exp)		((void)0)					///< Assertion testing
		#define S_VERIFY(exp)		exp							///< Verify an expression is true, expression IS evaluated during a release build
	#endif
#endif

#ifndef S_UNUSED
	#ifdef WIN32
		#define S_UNUSED(VAR)
	#else
		#define S_UNUSED(VAR)    UNUSED_PARAM_##VAR __attribute__((unused))
	#endif
#endif

#if defined __linux__ || defined __APPLE__ 
	#include <stdint.h>
#endif

namespace SDICOS
{

#ifdef WIN32		// Windows
	typedef signed __int8		S_INT8;		///<a signed 8-bit integer
	typedef signed __int16 		S_INT16;	///<a signed 16-bit integer
	typedef signed __int32 		S_INT32;	///<a signed 32-bit integer
	typedef signed __int64 		S_INT64;	///<a signed 64-bit integer

	typedef unsigned __int8		S_UINT8;	///<an unsigned 8-bit integer
	typedef unsigned __int16 	S_UINT16;	///<an unsigned 16-bit integer
	typedef unsigned __int32 	S_UINT32;	///<an unsigned 32-bit integer
	typedef unsigned __int64 	S_UINT64;	///<an unsigned 64-bit integer
#elif __APPLE__		// MAC
	typedef int8_t				S_INT8;		///<a signed 8-bit integer
	typedef int16_t				S_INT16;	///<a signed 16-bit integer
	typedef int32_t				S_INT32;	///<a signed 32-bit integer
	typedef int64_t				S_INT64;	///<a signed 64-bit integer
	typedef uint8_t				S_UINT8;	///<an unsigned 8-bit integer
	typedef uint16_t			S_UINT16;	///<an unsigned 16-bit integer
	typedef uint32_t			S_UINT32;	///<an unsigned 32-bit integer
	typedef uint64_t			S_UINT64;	///<an unsigned 64-bit integer
#elif __linux__ || __LINUX__
	typedef int8_t				S_INT8;		///<a signed 8-bit integer
	typedef int16_t				S_INT16;	///<a signed 16-bit integer
	typedef int32_t				S_INT32;	///<a signed 32-bit integer
	typedef int64_t				S_INT64;	///<a signed 64-bit integer
	typedef uint8_t				S_UINT8;	///<an unsigned 8-bit integer
	typedef uint16_t			S_UINT16;	///<an unsigned 16-bit integer
	typedef uint32_t			S_UINT32;	///<an unsigned 32-bit integer
	typedef uint64_t			S_UINT64;	///<an unsigned 64-bit integer
#endif

}//namespace SDICOS

#endif
