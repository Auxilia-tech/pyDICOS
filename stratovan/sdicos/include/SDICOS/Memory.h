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
#ifndef _STRATOVAN_DICOS_MEMORY_H_
#define _STRATOVAN_DICOS_MEMORY_H_

///
/// Definition for null value
///
#ifndef S_NULL
	#define S_NULL 0
#endif

///
/// Memory leak tracking
///
#ifdef WIN32	// Windows
	#ifndef DEBUG_NEW
		#ifdef _DEBUG
		#ifndef _CRTDBG_MAP_ALLOC
			#define _CRTDBG_MAP_ALLOC
		#endif
		#include <stdlib.h>
		#include <crtdbg.h>
		#define DEBUG_NEW new(_NORMAL_BLOCK , __FILE__, __LINE__)
		#else
		#include <stdlib.h>
		#define DEBUG_NEW new
		#endif 
	#endif
#else	// Mac
	#include <stdlib.h>
	#define DEBUG_NEW new
#endif

#define SAFE_NEW(POINTER_VAR, OBJECT_TYPE)	\
	{	\
 		try	\
		{	\
			POINTER_VAR = new OBJECT_TYPE;	\
		}	\
		catch (const std::bad_alloc& e)	\
		{	\
			POINTER_VAR = S_NULL;	\
		}	\
		catch (...)	\
		{	\
			POINTER_VAR = S_NULL;	\
		}	\
	}

#define RETURN_SAFE_NEW(OBJECT_TYPE)	\
	{	\
 		try	\
		{	\
			return new OBJECT_TYPE;	\
		}	\
		catch (const std::bad_alloc& e)	\
		{	\
			return S_NULL;	\
		}	\
		catch (...)	\
		{	\
			return S_NULL;	\
		}	\
	}

///
/// \namespace SDICOS
/// Contains all class, methods, enums etc. for Stratovan DICOS implementation
///
namespace SDICOS
{

	///
	/// Delete dynamically allocated memory
	///
	/// @param pointer Pointer to memory
	///
	template< class CType >
	void DELETE_POINTER(CType * &pointer)
	{
		delete pointer;
		pointer = S_NULL;
	}

	///
	/// Delete dynamically allocated array
	///
	/// @param pointer Pointer to array
	///
	template< class CType >
	void DELETE_ARRAY(CType * &pointer)
	{
		delete [] pointer;
		pointer = S_NULL;
	}

}//namespace SDICOS

#endif