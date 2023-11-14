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
#ifndef _STRATOVAN_DICOS_DCSSTRING_H_
#define _STRATOVAN_DICOS_DCSSTRING_H_

#include <ostream>

#include "SDICOS/Types.h"

#ifdef WIN32
	#define SPRINTF_S	sprintf_s
	#define SWPRINTF_S	swprintf_s
#else
	#define SPRINTF_S 	snprintf
	#define SWPRINTF_S	swprintf
#endif

namespace SDICOS
{

//////////////////////////////////////////////
///
/// \class DcsString
/// \brief String class for char or wide char
///
class DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsString();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsString(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsString(const wchar_t* pstr);

	///
	/// Initialize with a DcsString object
	///
	/// @param str DcsString object
	///
	DcsString(const DcsString& str);

	///
	/// Destructor
	///
	virtual ~DcsString();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Get a copy of the char string
	///
	/// @param pstr char string output.  Must be allocated to same size as string.
	///	@return true/false
	///
	bool Copy(char *pstr)const;

	///
	/// Get a copy of the char string
	///
	/// @param pstr wide char string output.  Must be allocated to same size as string.
	///	@return true/false
	///
	bool Copy(wchar_t *pstr)const;

	///
	/// Get the string
	///
	/// @return char Returns the char string
	///
	const char* Get()const;

	///
	/// Get the string
	///
	/// @return Returns the wide char string
	///
	const wchar_t* GetWide()const;

	///
	/// Get the character at the specified index
	///
	/// @param str char character
	/// @param nIndex index to string
	///	@return true/false
	///
	bool Get(char &str, const S_UINT32 nIndex)const;

	///
	/// Get the character at the specified index
	///
	/// @param str wide char character
	/// @param nIndex index to string
	///	@return true/false
	///
	bool Get(wchar_t &str, const S_UINT32 nIndex)const;

	///
	/// Copy char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsString& operator=(const char* pstr);

	///
	/// Copy wide char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsString& operator=(const wchar_t* pstr);

	///
	/// Copy another DcsString object
	///
	/// @param str DcsString object to copy
	///	@return DcsString reference to this object
	///
	DcsString& operator=(const DcsString& str);

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const wchar_t* pstr)const;

	///
	/// Compare DcsString object
	///
	/// @param str DcsString object to compare
	///	@return true/false
	///
	bool operator==(const DcsString& str)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare DcsString object
	///
	/// @param str DcsString object to compare
	///	@return true/false
	///
	bool operator!=(const DcsString& str)const;

	///
	/// Less-than operator for DcsString object
	///
	/// @param str DcsString object to compare
	///	@return true/false
	///
	bool operator<(const DcsString &str)const;

	///
	/// Append operator for DcsString object
	///
	/// @param strAppend DcsString object to append to this object
	///	@return true/false
	///
	DcsString& operator+=(const DcsString &strAppend);

	///
	/// Print DcsString object to an output stream
	/// If the string is NULL, "(NULL)" is printed to the output stream.
	///
	/// @param os output stream to send the string to
	/// @param str DcsString object to print
	/// @return ostream
	///
	friend std::ostream& operator<<(std::ostream& os, const DcsString& str);
	
	///
	/// Compare char string with no case sensitivity
	///
	/// @param pstr string to compare without case
	///	@return true/false
	///
	bool IsEqualNoCase(const char* pstr)const;

	///
	/// Compare wide char string with no case sensitivity
	///
	/// @param pstr string to compare without case
	///	@return true/false
	///
	bool IsEqualNoCase(const wchar_t* pstr)const;

	///
	/// Compare DcsString object with no case sensitivity
	///
	/// @param str DcsString string to compare without case
	///	@return true/false
	///
	bool IsEqualNoCase(const DcsString& str)const;

	///
	/// Convert string to unsigned 8 bit integer
	///
	/// @param nInt8 Unsigned integer output
	///	@return true/false.  Returns false if number is negative
	///
	bool AsInt(S_UINT8 &nInt8)const;
	
	///
	/// Convert string to signed 8 bit integer
	///
	/// @param nInt8 Signed integer output
	///	@return true/false
	///
	bool AsInt(S_INT8 &nInt8)const;

	///
	/// Convert string to unsigned 16 bit integer
	///
	/// @param nInt16 Unsigned integer output
	///	@return true/false.  Returns false if number is negative
	///
	bool AsInt(S_UINT16 &nInt16)const;
	
	///
	/// Convert string to signed 16 bit integer
	///
	/// @param nInt16 Signed integer output
	///	@return true/false
	///
	bool AsInt(S_INT16 &nInt16)const;

	///
	/// Convert string to unsigned 32 bit integer
	///
	/// @param nInt32 Unsigned integer output
	///	@return true/false.  Returns false if number is negative
	///
	bool AsInt(S_UINT32 &nInt32)const;
	
	///
	/// Convert string to signed 32 bit integer
	///
	/// @param nInt32 Signed integer output
	///	@return true/false
	///
	bool AsInt(S_INT32 &nInt32)const;

	///
	/// Convert string to float
	///
	/// @param fFloat float output
	///	@return true/false
	///
	bool AsFloat(float &fFloat)const;

	///
	/// Convert string to double
	///
	/// @param fDouble double output
	///	@return true/false
	///
	bool AsDouble(double &fDouble)const;

	///
	/// Convert string to boolean.
	/// Boolean conversions: 
	///		case-insensitive compare against 'true' and 'false'.
	///		zero and non-zero numbers (integer and float)
	///		all other strings are considered false.
	/// @param bBool boolean output
	/// @return true/false true if the strings represents a boolean value, false if it does not
	///
	bool AsBool(bool & bBool)const;
		
	/// Check if the string is valid
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Get the string's length
	///
	///	@return Length of string
	///
	S_UINT32 GetLength()const;

	///
	/// Check if the string is empty
	///
	/// @return true/false
	///
	bool Empty()const;

	///
	/// Get the string's size in bytes
	///
	///	@return Size of string in bytes
	///
	S_UINT64 GetSizeInBytes()const;

	///
	/// Check if using char
	///
	///	@return true/false
	///
	bool IsChar()const;

	///
	/// Check if using wide char
	///
	///	@return true/false
	///
	bool IsWideChar()const;

	///
	/// Check string contains a specific character
	///
	///	@param cCharacter Character to check
	///	@return true/false
	///
	bool HasCharacter(const char cCharacter)const;

	///
	/// Check string contains a specific character
	///
	///	@param cCharacter Character to check
	///	@return true/false
	///
	bool HasCharacter(const wchar_t cCharacter)const;

	///
	/// Get the number of times a specific character is found
	///
	///	@param cCharacter Character to check
	///	@return true/false
	///
	S_UINT16 InstancesOfCharacter(const char cCharacter)const;

	///
	/// Get the number of times a specific character is found
	///
	///	@param cCharacter Character to check
	///	@return
	S_UINT16 InstancesOfCharacter(const wchar_t cCharacter)const;

	///
	/// Find a character and its index in the string
	///
	/// @param nStart Index of where to start search
	/// @param nFound Index of where character is found
	/// @param cFind Character to find
	///	@return true/false
	///
	bool Find(const S_UINT32 nStart, S_UINT32 &nFound, const char cFind)const;

	///
	/// Find a character and its index in the string
	///
	/// @param nStart Index of where to start search
	/// @param nFound Index of where character is found
	/// @param cFind Character to find
	///	@return true/false
	///
	bool Find(const S_UINT32 nStart, S_UINT32 &nFound, const wchar_t cFind)const;

	///
	/// Find a character and its index in the string. Searches from start index to start of string.
	///
	/// @param nStart Index of where to start search
	/// @param nFound Index of where character is found
	/// @param cFind Character to find
	///	@return true/false
	///
	bool FindReverse(const S_UINT32 nStart, S_UINT32 &nFound, const char cFind)const;

	///
	/// Find a character and its index in the string. Searches from start index to start of string.
	///
	/// @param nStart Index of where to start search
	/// @param nFound Index of where character is found
	/// @param cFind Character to find
	///	@return true/false
	///
	bool FindReverse(const S_UINT32 nStart, S_UINT32 &nFound, const wchar_t cFind)const;

	///
	/// Get a sub string
	///
	/// @param nStart Index of where to start sub string
	/// @param nLength Length of sub string
	/// @param str Sub string
	///	@return true/false
	///
	bool GetSubString(const S_UINT32 nStart, const S_UINT32 nLength, DcsString &str)const;

	///
	/// Append a string to this object
	///
	/// @param pstr String to append
	///	@return true/false
	///
	bool Append(const char *pstr);

	///
	/// Append a string to this object
	///
	/// @param pstr String to append
	///	@return true/false
	///
	bool Append(const wchar_t *pstr);

	///
	/// Append a string to this object
	///
	/// @param str String to append
	///	@return true/false
	///
	bool Append(const DcsString &str);

	///
	/// Removes trailing spaces
	///
	/// @return true/false
	///
	bool RemoveTrailingSpaces();

	///
	/// Removes leading spaces
	///
	/// @return true/false
	///
	bool RemoveLeadingSpaces();

	///
	/// Removes trailing and leading spaces
	///
	/// @return true/false
	///
	bool RemoveTrailingAndLeadingSpaces();

	///
	/// Appends a trailing space (" ") to the string
	///
	/// @return true/false
	///
	virtual bool AddTrailingSpace(const S_UINT32 nSpacesToAdd = 1);
	
	/// Case insensitive comparison between two strings
	static bool IsEqualNoCase(const char* pStr0, const char* pStr1);
protected:

	class	ImplDcsString;
	ImplDcsString	*m_pImplDcsString;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsApplicationEntity
/// \brief	This type of string has the following restrictions:
///			-16 byte maximum
///			-Only allows the default character repertoire ISO-IR 6 excluding "\" and control characters LF (Line Feed 0x0A), FF (Form Feed 0x0C), CR (Carriage Return 0x0D), and ESC (Escape 0x1B)
///
class DcsApplicationEntity : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsApplicationEntity();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsApplicationEntity(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsApplicationEntity(const wchar_t* pstr);

	///
	/// Initialize with a DcsString object
	///
	/// @param str DcsString object
	///
	DcsApplicationEntity(const DcsString& str);

	///
	/// Initialize with a DcsApplicationEntity object
	///
	DcsApplicationEntity(const DcsApplicationEntity &dcsapplicationentity);

	///
	/// Copy char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsApplicationEntity& operator=(const char* pstr);

	///
	/// Copy wide char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsApplicationEntity& operator=(const wchar_t* pstr);

	///
	/// Copy another DcsApplicationEntity object
	///
	/// @param dcsapplicationentity DcsApplicationEntity object to copy
	///	@return DcsApplicationEntity reference to this object
	///
	DcsApplicationEntity& operator=(const DcsApplicationEntity &dcsapplicationentity);

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const wchar_t* pstr)const;

	///
	/// Compare DcsApplicationEntity object
	///
	/// @param dcsapplicationentity DcsApplicationEntity object to compare
	///	@return true/false
	///
	bool operator==(const DcsApplicationEntity &dcsapplicationentity)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare DcsApplicationEntity object
	///
	/// @param dcsapplicationentity DcsApplicationEntity object to compare
	///	@return true/false
	///
	bool operator!=(const DcsApplicationEntity &dcsapplicationentity)const;

	///
	/// Check if the string follows VR = AE restrictions:
	/// (16 byte maximum) Default Character Repertoire ISO-IR 6 excluding "\" and control charcaters LF (Line Feed 0x0A), FF (Form Feed 0x0C), CR (Carriage Return 0x0D), and ESC (Escape 0x1B)
	///
	///	@return true/false
	///
	virtual bool IsValid()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsDate
/// \brief This string represents a date.  The string has the format "YYYYMMDD", where YYYY = Year,
///			MM = Month, and DD = Day.
///			The string also supports date ranges in the following formats:
///			"YYYYMMDD-" = Specifies start time
///			"-YYYYMMDD" = Specifies end time
///			"YYYYMMDD-YYYYMMDD" = Specifies start and end time
///
class DcsDate : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsDate();

	///
	/// Set the date
	///
	/// @param nYear Year
	/// @param nMonth Month. Set to zero to exclude.
	/// @param nDay Day. Set to zero to exclude.
	/// @return true/false
	///
	DcsDate(const S_UINT32 nYear, const S_UINT32 nMonth, const S_UINT32 nDay);
	
	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsDate(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsDate(const wchar_t* pstr);

	///
	/// Initialize with a DcsDate object
	///
	DcsDate(const DcsDate &dcsdate);

	///
	/// Initialize with a DcsString object
	///
	DcsDate(const DcsString &dcsstring);

	///
	/// Copy char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsDate& operator=(const char* pstr);

	///
	/// Copy wide char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsDate& operator=(const wchar_t* pstr);

	///
	/// Copy another DcsDate object
	///
	/// @param dcsdate DcsDate object to copy
	///	@return DcsDate reference to this object
	///
	DcsDate& operator=(const DcsDate &dcsdate);

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const wchar_t* pstr)const;

	///
	/// Compare DcsString object
	///
	/// @param str DcsString object to compare
	///	@return true/false
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare DcsString object
	///
	/// @param str DcsString object to compare
	///	@return true/false
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare DcsDate object
	///
	/// @param dcsdate DcsDate object to compare
	///	@return true/false
	///
	bool operator==(const DcsDate &dcsdate)const;

	///
	/// Compare DcsDate object
	///
	/// @param dcsdate DcsDate object to compare
	///	@return true/false
	///
	bool operator!=(const DcsDate &dcsdate)const;

	/// Set the date to today's date in UTC
	bool SetToday();

	///
	/// Set the date
	///
	/// @param nYear Year
	/// @param nMonth Month. Set to zero to exclude.
	/// @param nDay Day. Set to zero to exclude.
	/// @return true/false
	///
	bool Set(const S_UINT32 nYear, const S_UINT32 nMonth, const S_UINT32 nDay);

	///
	/// Get the date
	///
	/// @param nYear Year.  Set to zero if not present
	/// @param nMonth Month.  Set to zero if not present
	/// @param nDay Day.  Set to zero if not present
	/// @return true/false Returns false if the date is a range or is not set
	///
	bool Get(S_UINT32 &nYear, S_UINT32 &nMonth, S_UINT32 &nDay)const;

	///
	/// Set the start date of a range
	///
	/// @param nYear Year
	/// @param nMonth Month. Set to zero to exclude
	/// @param nDay Day. Set to zero to exclude
	/// @return true/false
	///
	bool SetStart(const S_UINT32 nYear, const S_UINT32 nMonth, const S_UINT32 nDay);

	///
	/// Get the start date of a range
	///
	/// @param nYear Year.  Set to zero if not present
	/// @param nMonth Month.  Set to zero if not present
	/// @param nDay Day.  Set to zero if not present
	/// @return true/false Returns false if not present
	///
	bool GetStart(S_UINT32 &nYear, S_UINT32 &nMonth, S_UINT32 &nDay)const;

	///
	/// Set the end date of a range
	///
	/// @param nYear Year
	/// @param nMonth Month. Set to zero to exclude
	/// @param nDay Day. Set to zero to exclude
	/// @return true/false
	///
	bool SetEnd(const S_UINT32 nYear, const S_UINT32 nMonth, const S_UINT32 nDay);

	///
	/// Get the end date of a range
	///
	/// @param nYear Year
	/// @param nMonth Month
	/// @param nDay Day
	/// @return true/false
	///
	bool GetEnd(S_UINT32 &nYear, S_UINT32 &nMonth, S_UINT32 &nDay)const;

	///
	/// Check if the string follows VR = DA restrictions
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Check if the string's current components are valid (ex. If date only has year and month, the function checks if they are valid)
	///
	///	@return true/false
	///
	bool IsValidAvailableComponents()const;

	///
	/// Checks if the string needs a space character appended
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;

	///
	/// Create a DcsDate object with today's date
	///
	static DcsDate Today();
	
protected:

	///
	/// Check if the char string follows VR = DA restrictions
	///
	///	@return true/false
	///
	bool IsValidString()const;

	///
	/// Check if the wide char string follows VR = DA restrictions
	///
	///	@return true/false
	///
	bool IsValidStringWide()const;

	///
	/// Check if dates are valid
	///
	/// @param pcstr 	String to check
	/// @param nStart 	Index to start checking from
	/// @param nLength 	Length of string
	/// @return true/false
	///
	bool VerifyDateComponents(const char *pcstr, const S_UINT32 nStart, const S_UINT32 nLength)const;

	///
	/// Check if dates are valid
	///
	/// @param pcstr 	String to check
	/// @param nStart 	Index to start checking from
	/// @param nLength 	Length of string
	/// @return true/false
	///
	bool VerifyDateComponents(const wchar_t *pcstr, const S_UINT32 nStart, const S_UINT32 nLength)const;

	///
	/// Get the year, month, and day from the provided string
	///
	/// @param strDate String to extract date from
	/// @param nYear Year
	/// @param nMonth Month
	/// @param nDay Day
	/// @return true/false
	///
	bool Get(const DcsString &strDate, S_UINT32 &nYear, S_UINT32 &nMonth, S_UINT32 &nDay)const;

};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsTime
/// \brief This string represents a time.  The string follows the format "HHMMSS.FFFFFF", where HH = Hours,
///			MM = Minutes, SS = Seconds, and FFFFFF = Fractional Seconds
///			The string also supports time ranges in the following formats:
///			"HHMMSS.FFFFFF-" = Specifies start time
///			"-HHMMSS.FFFFFF" = Specifies end time
///			"HHMMSS.FFFFFF-HHMMSS.FFFFFF" = Specifies start and end time
///
class DcsTime : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsTime();

	///
	/// Set the time
	///
	/// @param nHour Range: 00-23
	/// @param nMinute Range: 00-59
	/// @param nSecond Range: 00-60
	/// @param nSecondFraction Range: 000000-999999. A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	DcsTime(const S_UINT32 nHour, const S_UINT32 nMinute, const S_UINT32 nSecond, const S_UINT32 nSecondFraction);
	
	///
	/// Initialize with a char string
	///
	DcsTime(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	DcsTime(const wchar_t* pstr);

	///
	/// Initialize with a DcsTime object
	///
	DcsTime(const DcsTime &dcstime);

	///
	/// Initialize with a DcsString object
	///
	DcsTime(const DcsString &dcsstring);

	///
	/// Copy char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsTime& operator=(const char* pstr);

	///
	/// Copy wide char string
	///
	/// @param pstr char string to copy
	///	@return DcsString reference to this object
	///
	DcsTime& operator=(const wchar_t* pstr);

	///
	/// Copy another DcsTime object
	///
	/// @param dcstime DcsTime object to copy
	///	@return DcsTime reference to this object
	///
	DcsTime& operator=(const DcsTime &dcstime);

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const wchar_t* pstr)const;

	///
	/// Compare string
	///
	/// @param str String to compare
	///	@return true/false
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare DcsTime object
	///
	/// @param dcstime DcsTime object to compare
	///	@return true/false
	///
	bool operator==(const DcsTime &dcstime)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare string
	///
	/// @param str String to compare
	///	@return true/false
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare DcsTime object
	///
	/// @param dcstime DcsTime object to compare
	///	@return true/false
	///
	bool operator!=(const DcsTime &dcstime)const;

	/// Set to current time in UTC.
	bool SetNow();

	///
	/// Check if the string follows VR = TM restrictions
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a space character appended
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;

	///
	/// Set the time
	///
	/// @param nHour Range: 00-23
	/// @param nMinute Range: 00-59
	/// @param nSecond Range: 00-60
	/// @param nSecondFraction Range: 000000-999999. A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool Set(const S_UINT32 nHour, const S_UINT32 nMinute, const S_UINT32 nSecond, const S_UINT32 nSecondFraction);

	///
	/// Get the time
	///
	/// @param nHour
	/// @param nMinute
	/// @param nSecond
	/// @param nSecondFraction A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool Get(S_UINT32 &nHour, S_UINT32 &nMinute, S_UINT32 &nSecond, S_UINT32 &nSecondFraction)const;

	///
	/// Set the starting time for a range
	///
	/// @param nHour Range: 00-23
	/// @param nMinute Range: 00-59
	/// @param nSecond Range: 00-60
	/// @param nSecondFraction Range: 000000-999999. A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool SetStart(const S_UINT32 nHour, const S_UINT32 nMinute, const S_UINT32 nSecond, const S_UINT32 nSecondFraction);

	///
	/// Get the starting time for a range
	///
	/// @param nHour
	/// @param nMinute
	/// @param nSecond
	/// @param nSecondFraction A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool GetStart(S_UINT32 &nHour, S_UINT32 &nMinute, S_UINT32 &nSecond, S_UINT32 &nSecondFraction)const;

	///
	/// Set the ending time for a range
	///
	/// @param nHour Range: 00-23
	/// @param nMinute Range: 00-59
	/// @param nSecond Range: 00-60
	/// @param nSecondFraction Range: 000000-999999. A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool SetEnd(const S_UINT32 nHour, const S_UINT32 nMinute, const S_UINT32 nSecond, const S_UINT32 nSecondFraction);

	///
	/// Get the ending time for a range
	///
	/// @param nHour
	/// @param nMinute
	/// @param nSecond
	/// @param nSecondFraction A value of '1' is '0.000001' seconds
	/// @return true/false
	///
	bool GetEnd(S_UINT32 &nHour, S_UINT32 &nMinute, S_UINT32 &nSecond, S_UINT32 &nSecondFraction)const;

	///
	/// Check if start range is open "-HHMMSS.FFFFFF"
	///
	/// @return true/false
	///
	bool HasOpenStartRange()const;

	///
	/// Check if end range is open "HHMMSS.FFFFFF-"
	///
	/// @return true/false
	///
	bool HasOpenEndRange()const;

	///
	/// Check if range is set "HHMMSS.FFFFFF-HHMMSS.FFFFFF"
	///
	/// @return true/false
	///
	bool HasSetRange()const;

	///
	/// Checks if time is a range
	///
	/// @return true/false
	///
	bool IsRange()const;

	///
	/// Checks if hour is set
	///
	/// @return true/false
	///
	bool HasHour()const;

	///
	/// Checks if minute is set
	///
	/// @return true/false
	///
	bool HasMinute()const;

	///
	/// Checks if second is set
	///
	/// @return true/false
	///
	bool HasSecond()const;

	///
	/// Checks if second fraction is set
	///
	/// @return true/false
	///
	bool HasSecondFraction()const;

	///
	/// Create a DcsTime object set to the current time
	///
	static DcsTime Now();
	
protected:

	///
	/// Check if the char string follows the "HHMMSS.FFFFFF" format
	///
	///	@return true/false
	///
	bool IsValidString()const;

	///
	/// Check if the wide char string follows the "HHMMSS.FFFFFF" format
	///
	///	@return true/false
	///
	bool IsValidStringWide()const;

	///
	/// Check if the string follows the "HHMMSS.FFFFFF" format
	///
	/// @param pstr String to check
	/// @param nStart Index to start checking from
	/// @param nLength Length of string
	///	@return true/false
	///
	bool VerfyTimeComponents(const char *pstr, const S_UINT32 nStart, const S_UINT32 nLength)const;

	///
	/// Check if the string follows the "HHMMSS.FFFFFF" format
	///
	/// @param pstr String to check
	/// @param nStart Index to start checking from
	/// @param nLength Length of string
	///	@return true/false
	///
	bool VerfyTimeComponents(const wchar_t *pstr, const S_UINT32 nStart, const S_UINT32 nLength)const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsPersonName
/// \brief This string represents a person's or animal's name.
///			The format for a person's name is "Family Name^Given Name^Middle Name^Prefix^Suffix".
///			The format for an animal's name is "Caretaker Name^Animal Name".
///
class DcsPersonName
{
public:

	///
	/// Initialize with default values
	///
	DcsPersonName();

	///
	/// Initialize by calling SetCombinedString()
	///
	DcsPersonName(const char * strCombined);

	///
	/// Initialize by called SetCombinedString()
	///
	DcsPersonName(const DcsString &strCombined);

	///
	/// Initialize a DcsPersonName object
	///
	DcsPersonName(const DcsPersonName &dcspersonname);

	///
	/// Destructor
	///
	~DcsPersonName();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy another DcsPersonName object
	///
	/// @param dcspersonname DcsPersonName object to copy
	///	@return DcsPersonName reference to this object
	///
	DcsPersonName& operator=(const DcsPersonName &dcspersonname);

	///
	/// Compare DcsPersonName object
	///
	/// @param dcspersonname DcsPersonName object to compare
	///	@return true/false
	///
	bool operator==(const DcsPersonName &dcspersonname)const;

	///
	/// Compare DcsPersonName object
	///
	/// @param dcspersonname DcsPersonName object to compare
	///	@return true/false
	///
	bool operator!=(const DcsPersonName &dcspersonname)const;

	///
	/// Set a person's name
	///
	/// @param pcFamilyName Family name (64 characters max)
	/// @param pcGivenName Given name (64 characters max)
	/// @param pcMiddleName Middle name (64 characters max)
	/// @param pcPrefix Prefix (64 characters max)
	/// @param pSuffix Suffix (64 characters max)
	/// @return true/false
	///
	bool SetName(	const char *pcFamilyName, const char *pcGivenName, const char *pcMiddleName, 
					const char *pcPrefix, const char *pSuffix);

	///
	/// Set a person's name.  Each parameter can be "" or S_NULL to keep it blank.
	///
	/// @param pcFamilyName Family name (64 characters max)
	/// @param pcGivenName Given name (64 characters max)
	/// @param pcMiddleName Middle name (64 characters max)
	/// @param pcPrefix Prefix (64 characters max)
	/// @param pSuffix Suffix (64 characters max)
	/// @return true/false
	///
	bool SetName(	const wchar_t *pcFamilyName, const wchar_t *pcGivenName, const wchar_t *pcMiddleName, 
					const wchar_t *pcPrefix, const wchar_t *pSuffix);

	///
	/// Set a animal's and caretaker's name
	///
	/// @param pcAnimalName Animal's name (64 characters max)
	/// @param pcCaretakerName Caretaker's name (64 characters max)
	/// @return true/false
	///
	bool SetAnimalAndCaretakerName(const char *pcAnimalName, const char *pcCaretakerName);

	///
	/// Set a animal's and caretaker's name
	///
	/// @param pcAnimalName Animal's name (64 characters max)
	/// @param pcCaretakerName Caretaker's name (64 characters max)
	/// @return true/false
	///
	bool SetAnimalAndCaretakerName(const wchar_t *pcAnimalName, const wchar_t *pcCaretakerName);

	///
	/// Get the family name
	///
	/// @return true/false
	///
	bool GetFamilyName(DcsString &str)const;

	///
	/// Get the given name
	///
	/// @return true/false
	///
	bool GetGivenName(DcsString &str)const;

	///
	/// Get the middle name
	///
	/// @return true/false
	///
	bool GetMiddleName(DcsString &str)const;

	///
	/// Get the prefix name
	///
	/// @return true/false
	///
	bool GetPrefix(DcsString &str)const;

	///
	/// Get the suffix
	///
	/// @return true/false
	///
	bool GetSuffix(DcsString &str)const;

	///
	/// Get the animal's name
	///
	/// @return true/false
	///
	bool GetAnimalName(DcsString &str)const;

	///
	/// Get the caretaker's name
	///
	/// @return true/false
	///
	bool GetCaretakerName(DcsString &str)const;

	///
	/// Order for person : "Family Name^Given Name^Middle Name^Prefix^Suffix". Unset strings are excluded (i.e. If only family name is set, then the combined string is "Family Name")
	/// Order for animal : "Caretaker Name^Animal Name"
	///
	/// @param strCombined Combined string
	/// @return true/false
	///
	bool SetCombinedString(const DcsString &strCombined);

	///
	/// Order for person : "Family Name^Given Name^Middle Name^Prefix^Suffix". Unset strings are excluded (i.e. If only family name is set, then the combined string is "Family Name")
	/// Order for animal : "Caretaker Name^Animal Name"
	///
	/// @param strCombined Combined string
	/// @return true/false
	///
	bool GetCombinedString(DcsString &strCombined)const;

	///
	/// Check if the string follows VR = PN restrictions
	///
	///	@return true/false
	///
	bool IsValid()const;

	///
	/// Get max characters allowed per string
	///
	/// @return 64
	///
	S_UINT32 GetMaxCharacters()const;
private:

	class ImplDcsPersonName;
	ImplDcsPersonName	*m_pImplDcsPersonName; ///< Internal implementation
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsDecimal
/// \brief This string represents a decimal number.  The string has the following restrictions:
///			-16 bytes max
///			-Allows the characters '+', '-', '.', 'e', 'E', and '0'-'9'
///
class DcsDecimal : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsDecimal();

	///
	/// Initialize with a float
	///
	/// @param fValue Float to convert to string
	///
	DcsDecimal(const float fValue);

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsDecimal(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsDecimal(const wchar_t* pstr);

	///
	/// Initialize with DcsString object
	///
	/// @param str DcsString object to copy
	///
	DcsDecimal(const DcsString &str);

	///
	/// Initialize with another DcsDecimal object
	///
	/// @param dcsdecimal DcsDecimal object to copy
	///
	DcsDecimal(const DcsDecimal &dcsdecimal);

	///
	/// Destructor
	///
	virtual ~DcsDecimal();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy a float
	///
	/// @param fValue float to copy
	///	@return DcsDecimal reference to this object
	///
	DcsDecimal& operator=(const float fValue);

	///
	/// Copy a string
	///
	/// @param pstr string to copy
	///	@return DcsDecimal reference to this object
	///
	DcsDecimal& operator=(const char *pstr);

	///
	/// Copy a string
	///
	/// @param pstr string to copy
	///	@return DcsDecimal reference to this object
	///
	DcsDecimal& operator=(const wchar_t *pstr);

	///
	/// Copy a DcString object
	///
	/// @param str string to copy
	///	@return DcsDecimal reference to this object
	///
	DcsDecimal& operator=(const DcsString &str);

	///
	/// Copy another DcsDecimal object
	///
	/// @param dcsdecimal DcsDecimal object to copy
	///	@return DcsDecimal reference to this object
	///
	DcsDecimal& operator=(const DcsDecimal &dcsdecimal);

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator==(const wchar_t* pstr)const;

	///
	/// Compare DcsDecimal object
	///
	/// @param dcsdecimal DcsDecimal object to compare
	///	@return true/false
	///
	bool operator==(const DcsDecimal &dcsdecimal)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare DcsDecimal object
	///
	/// @param dcsdecimal DcsDecimal object to compare
	///	@return true/false
	///
	bool operator!=(const DcsDecimal &dcsdecimal)const;

	///
	/// Get a copy of the char string
	///
	/// @param pstr char string output.  Must be allocated to same size as string.
	///	@return true/false
	///
	bool Copy(char *pstr)const;

	///
	/// Get a copy of the char string
	///
	/// @param pstr wide char string output.  Must be allocated to same size as string.
	///	@return true/false
	///
	bool Copy(wchar_t *pstr)const;

	///
	/// Get a copy of the string
	///
	/// @param str string output
	///	@return true/false
	///
	bool Copy(DcsString &str)const;

	///
	/// Convert string to float
	///
	/// @param fFloat float output
	///	@return true/false
	///
	bool AsFloat(float &fFloat)const;

	///
	/// Check if the string follows VR = DS restrictions
	/// 16 bytes max. Only allows '+', '-', '.', 'e', 'E', and '0'-'9'
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a padding
	///
	/// @return true/false
	///
	bool NeedsPadding()const;

	///
	/// Adds a leading zero
	///
	/// @return true/false
	///
	bool AddPadding();
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsInteger
/// \brief This string represents an integer.  The string has the following restrictions:
///			-12 bytes max
///			-Allows the characters '+', '-', and '0'-'9'
///
class DcsInteger : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsInteger();

	///
	/// Initialize with an integer
	///
	/// @param nInt integer
	///
	DcsInteger(const S_INT32 nInt);

	///
	/// Initialize with an integer
	///
	/// @param nInt integer
	///
	DcsInteger(const S_UINT32 nInt);

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsInteger(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsInteger(const wchar_t* pstr);

	///
	/// Initialize with another DcsInteger object
	///
	/// @param dcsinteger DcsInteger object to copy
	///
	DcsInteger(const DcsInteger &dcsinteger);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsInteger(const DcsString &dcsstring);

	///
	/// Destructor
	///
	virtual ~DcsInteger();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy an integer
	///
	/// @param nInt Integer to copy
	///	@return DcsInteger reference to this object
	///
	DcsInteger& operator=(const S_INT32 nInt);

	///
	/// Copy an integer
	///
	/// @param nInt Integer to copy
	///	@return DcsInteger reference to this object
	///
	DcsInteger& operator=(const S_UINT32 nInt);

	///
	/// Copy a string
	///
	/// @param pstr string to copy
	///	@return DcsInteger reference to this object
	///
	DcsInteger& operator=(const char *pstr);

	///
	/// Copy a string
	///
	/// @param pstr string to copy
	///	@return DcsInteger reference to this object
	///
	DcsInteger& operator=(const wchar_t *pstr);

	///
	/// Copy another DcsInteger object
	///
	/// @param dcsinteger DcsInteger object to copy
	///	@return DcsInteger reference to this object
	///
	DcsInteger& operator=(const DcsInteger &dcsinteger);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str string to compare
	///	@return true/false
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsinteger string to compare
	///	@return true/false
	///
	bool operator==(const DcsInteger &dcsinteger)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator!=(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str string to compare
	///	@return true/false
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsinteger string to compare
	///	@return true/false
	///
	bool operator!=(const DcsInteger &dcsinteger)const;

	///
	/// Get a copy of the string
	///
	/// @param str string output
	///	@return true/false
	///
	bool Copy(DcsString &str)const;
	
	///
	/// Convert string to signed 32 bit integer
	///
	/// @param nInt32 Signed integer output
	///	@return true/false
	///
	bool AsInt(S_INT32 &nInt32)const;
	
	///
	/// Convert string to unsigned 32 bit integer
	///
	/// @param nInt32 Unsigned integer output
	///	@return true/false
	///
	bool AsInt(S_UINT32 &nInt32)const;

	///
	/// Check if the string follows VR = IS restrictions
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a padding
	/// 12 bytes max. Only includes '+', '-', and '0'-'9'
	/// @return true/false
	///
	bool NeedsPadding()const;

	///
	/// Adds a leading zero
	///
	/// @return true/false
	///
	bool AddPadding();
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsUnlimitedText
/// \brief This string has a 2^32-2 character maximum
///
class DcsUnlimitedText : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsUnlimitedText();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsUnlimitedText(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsUnlimitedText(const wchar_t* pstr);

	///
	/// Initialize with another DcsUnlimitedText object
	///
	/// @param dcsunlimitedtext DcsUnlimitedText object to copy
	///
	DcsUnlimitedText(const DcsUnlimitedText &dcsunlimitedtext);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsUnlimitedText(const DcsString &dcsstring);

	///
	/// Copy another DcsUnlimitedText object
	///
	/// @param dcsunlimitedtext DcsUnlimitedText object to copy
	///	@return DcsUnlimitedText reference to this object
	///
	DcsUnlimitedText& operator=(const DcsUnlimitedText &dcsunlimitedtext);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str string to compare
	///	@return true/false
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsunlimitedtext string to compare
	///	@return true/false
	///
	bool operator==(const DcsUnlimitedText &dcsunlimitedtext)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str string to compare
	///	@return true/false
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsunlimitedtext string to compare
	///	@return true/false
	///
	bool operator!=(const DcsUnlimitedText &dcsunlimitedtext)const;

	///
	/// Check if the string follows VR = UT restrictions
	/// 2^32-2 characters max
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsShortText
/// \brief This string has a 1024 character maximum
///
class DcsShortText : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsShortText();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsShortText(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsShortText(const wchar_t* pstr);

	///
	/// Initialize with another DcsShortText object
	///
	/// @param dcsshorttext DcsShortText object to copy
	///
	DcsShortText(const DcsShortText &dcsshorttext);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsShortText(const DcsString &dcsstring);

	///
	/// Copy another DcsShortText object
	///
	/// @param dcsshorttext DcsShortText object to copy
	///	@return DcsShortText reference to this object
	///
	DcsShortText& operator=(const DcsShortText &dcsshorttext);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param dcsshorttext string to compare
	///	@return true/false
	///
	bool operator==(const DcsShortText &dcsshorttext)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param dcsshorttext string to compare
	///	@return true/false
	///
	bool operator!=(const DcsShortText &dcsshorttext)const;

	///
	/// Check if the string follows VR = ST restrictions
	/// 1024 characters max
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsLongText
/// \brief This string has a 10240 character maximum
///
class DcsLongText : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsLongText();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsLongText(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsLongText(const wchar_t* pstr);

	///
	/// Initialize with another DcsLongText object
	///
	/// @param dcslongtext DcsLongText object to copy
	///
	DcsLongText(const DcsLongText &dcslongtext);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsLongText(const DcsString &dcsstring);

	///
	/// Copy another DcsLongText object
	///
	/// @param dcslongtext DcsLongText object to copy
	///
	DcsLongText& operator=(const DcsLongText &dcslongtext);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcslongtext String to compare
	///
	bool operator==(const DcsLongText &dcslongtext)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcslongtext String to compare
	///
	bool operator!=(const DcsLongText &dcslongtext)const;

	///
	/// Check if the string follows VR = LT restrictions
	/// 10240 characters max
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsShortString
/// \brief This string has the following restrictions:
///			-16 character maximum
///			-Excludes all control characters, except ESC
///
class DcsShortString : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsShortString();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsShortString(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsShortString(const wchar_t* pstr);

	///
	/// Initialize with another DcsShortString object
	///
	/// @param dcsshortstring DcsShortString object to copy
	///
	DcsShortString(const DcsShortString &dcsshortstring);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsShortString(const DcsString &dcsstring);

	///
	/// Copy another DcsShortString object
	///
	/// @param dcsshortstring DcsShortString object to copy
	///
	DcsShortString& operator=(const DcsShortString &dcsshortstring);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsshortstring String to compare
	///
	bool operator==(const DcsShortString &dcsshortstring)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsshortstring String to compare
	///
	bool operator!=(const DcsShortString &dcsshortstring)const;

	///
	/// Check if the string follows VR = SH restrictions
	/// 16 characters max, excludes control characters, except ESC
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsLongString
/// \brief This string has a 64 character maximum
///
class DcsLongString : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsLongString();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsLongString(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsLongString(const wchar_t* pstr);

	///
	/// Initialize with another DcsLongString object
	///
	/// @param dcslongstring DcsLongString object to copy
	///
	DcsLongString(const DcsLongString &dcslongstring);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsLongString(const DcsString &dcsstring);

	///
	/// Copy another DcsLongString object
	///
	/// @param dcslongstring DcsLongString object to copy
	///
	DcsLongString& operator=(const DcsLongString &dcslongstring);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcslongstring String to compare
	///
	bool operator==(const DcsLongString &dcslongstring)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcslongstring String to compare
	///
	bool operator!=(const DcsLongString &dcslongstring)const;

	///
	/// Check if the string follows VR = LO restrictions
	/// 64 characters max
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsCodeString
/// \brief This string has the following restrictions:
///		-16 bytes maximum
///		-Only allows uppercase letters, '0'-'9', space (' '), and underscore ('_')
///
class DcsCodeString : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsCodeString();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsCodeString(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsCodeString(const wchar_t* pstr);

	///
	/// Initialize with another DcsCodeString object
	///
	/// @param dcscodestring DcsCodeString object to copy
	///
	DcsCodeString(const DcsCodeString &dcscodestring);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsCodeString(const DcsString &dcsstring);

	///
	/// Copy another DcsCodeString object
	///
	/// @param dcscodestring DcsCodeString object to copy
	///
	DcsCodeString& operator=(const DcsCodeString &dcscodestring);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcscodestring String to compare
	///
	bool operator==(const DcsCodeString &dcscodestring)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcscodestring String to compare
	///
	bool operator!=(const DcsCodeString &dcscodestring)const;

	///
	/// Check if the string follows VR = CS restrictions
	/// 16 bytes max
	/// Only allows uppercase letters, '0'-'9', space (' '), and underscore ('_')
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing space
	///
	/// @return true/false
	///
	bool NeedsTrailingSpace()const;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsUniqueIdentifier
/// \brief This string contains the following restrictions:
///			-64 bytes maximum
///			-Allows the characters '0'-'9' and '.'
///
class DcsUniqueIdentifier : public DcsString
{
public:
	///
	/// Initialize with default values
	///
	DcsUniqueIdentifier();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsUniqueIdentifier(const char* pstr);

	///
	/// Initialize with a wide char string
	///
	/// @param pstr wide char string
	///
	DcsUniqueIdentifier(const wchar_t* pstr);

	///
	/// Initialize with another DcsUniqueIdentifier object
	///
	/// @param dcsuniqueidentifier DcsUniqueIdentifier object to copy
	///
	DcsUniqueIdentifier(const DcsUniqueIdentifier &dcsuniqueidentifier);

	///
	/// Initialize with a DcsString object
	///
	/// @param dcsstring DcsString object to copy
	///
	DcsUniqueIdentifier(const DcsString &dcsstring);

	///
	/// Copy another DcsUniqueIdentifier object
	///
	/// @param dcsuniqueidentifier DcsUniqueIdentifier object to copy
	///
	DcsUniqueIdentifier& operator=(const DcsUniqueIdentifier &dcsuniqueidentifier);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator==(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsuniqueidentifier String to compare
	///
	bool operator==(const DcsUniqueIdentifier &dcsuniqueidentifier)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param str String to compare
	///
	bool operator!=(const DcsString &str)const;

	///
	/// Compare a string
	///
	/// @param dcsuniqueidentifier String to compare
	///
	bool operator!=(const DcsUniqueIdentifier &dcsuniqueidentifier)const;

	///
	/// Automatically sets a Globally Unique ID
	///
	void SetGUID();

	///
	/// Check if the string follows VR = UI restrictions
	/// 64 bytes max
	/// Only allows '0'-'9', and '.'
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Checks if the string needs a trailing null (0x00) character
	///
	/// @return true/false
	///
	bool NeedsPadding()const;

	///
	/// Generate a new unique identifier with SetGUID()
	/// @return DcsUniqueIdentifier
	///
	static DcsUniqueIdentifier CreateGUID();
	
protected:

	virtual bool AddTrailingSpace(const S_UINT32 nSpacesToAdd = 1);
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsDateTime
/// \brief This string combines date and time into a single string.  The string has the
///			format "YYYYMMDDHHNNSS.FFFFFF&ZZXX", where YYYY = Year, MM = Month, 
///			DD = Day, HH = Hours, NN = Minutes, SS = Seconds, & = '+' or '-', 
///			ZZ = Hour offset, and XX = Minute Offset
///			The string has the following range formats:
///				"-YYYYMMDDHHNNSS.FFFFFF&ZZXX"
///				"YYYYMMDDHHNNSS.FFFFFF&ZZXX-"
///				"YYYYMMDDHHNNSS.FFFFFF&ZZXX-YYYYMMDDHHNNSS.FFFFFF&ZZXX"
///
class DcsDateTime
{
public:

	///
	/// Initialize with default values
	///
	DcsDateTime();

	///
	/// Initialize with DcsDate and DcsTime
	///
	DcsDateTime(const DcsDate& dcsDate, const DcsTime& dcsTime);
	
	///
	/// Initialize with another DcsDateTime object
	///
	/// @param dcsdatetime DcsDateTime object to copy
	///
	DcsDateTime(const DcsDateTime &dcsdatetime);

	///
	/// Copy another DcsDateTime object
	///
	/// @param dcsdatetime DcsDateTime object to copy
	///
	DcsDateTime& operator=(const DcsDateTime &dcsdatetime);

	///
	/// Destructor
	///
	virtual ~DcsDateTime();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Compare DcsDateTime objects
	///
	/// @param dcsdatetime DcsDateTime object to copy
	///
	bool operator==(const DcsDateTime &dcsdatetime)const;

	///
	/// Compare DcsDateTime objects
	///
	/// @param dcsdatetime DcsDateTime object to copy
	///
	bool operator!=(const DcsDateTime &dcsdatetime)const;

	/// Set to the current time and date in UTC
	bool SetNow();

	///
	/// Set the date and time and hour/minute offset from UTC
	///
	/// @param dcsdate Date
	/// @param dcsTime Time
	/// @param nOffset Offset from UTC. Range from -1200 to +1400.
	/// @return true/false
	///
	bool Set(const DcsDate &dcsdate, const DcsTime &dcsTime, const S_INT16 nOffset);

	///
	/// Set the date and time
	///
	/// @param dcsdate Date
	/// @param dcsTime Time
	/// @return true/false
	///
	bool Set(const DcsDate &dcsdate, const DcsTime &dcsTime);

	///
	/// Set the date and hour/minute offset from UTC
	///
	/// @param dcsdate Date
	/// @param nOffset Offset from UTC. Range from -1200 to +1400
	/// @return true/false
	///
	bool Set(const DcsDate &dcsdate, const S_INT16 nOffset);

	///
	/// Set the date
	///
	/// @param dcsdate Date
	/// @return true/false
	///
	bool Set(const DcsDate &dcsdate);

	///
	/// Set the starting date and time and hour/minute offset from UTC
	///
	/// @param dcsDateStart Date
	/// @param dcsTimeStart Time
	/// @param nOffsetStart Offset from UTC. Range from -1200 to +1400.
	/// @return true/false
	///
	bool SetRangeStart(const DcsDate &dcsDateStart, const DcsTime &dcsTimeStart, const S_INT16 nOffsetStart);

	///
	/// Set the starting date and time
	///
	/// @param dcsDateStart Date
	/// @param dcsTimeStart Time
	/// @return true/false
	///
	bool SetRangeStart(const DcsDate &dcsDateStart, const DcsTime &dcsTimeStart);

	///
	/// Set the ending date and time and hour/minute offset from UTC
	///
	/// @param dcsDateEnd Date
	/// @param dcsTimeEnd Time
	/// @param nOffsetEnd Offset from UTC. Range from -1200 to +1400.
	/// @return true/false
	///
	bool SetRangeEnd(const DcsDate &dcsDateEnd, const DcsTime &dcsTimeEnd, const S_INT16 nOffsetEnd);

	///
	/// Set the ending date and time
	///
	/// @param dcsdateEnd Date
	/// @param dcsTimeEnd Time
	/// @return true/false
	///
	bool SetRangeEnd(const DcsDate &dcsdateEnd, const DcsTime &dcsTimeEnd);

	///
	/// Get the string in "YYYYMMDDHHMMSS.FFFFFF&ZZXX", "-YYYYMMDDHHMMSS.FFFFFF&ZZXX", "YYYYMMDDHHMMSS.FFFFFF&ZZXX-", or "YYYYMMDDHHMMSS.FFFFFF&ZZXX-YYYYMMDDHHMMSS.FFFFFF&ZZXX" format
	/// "YYYYMMDD": Same as DcsDate
	/// "HHMMSS.FFFFFF": Same as DcsTime
	/// "&ZZXX": & = '+' or '-', ZZ = Hour offset, XX = Minute Offset
	///
	/// @param strCombined Combined string
	/// @return true/false
	///
	bool GetCombinedString(DcsString &strCombined)const;

	/// @see  GetCombinedString(DcsString &strCombined)const
	DcsString GetCombinedString()const;
	
	///
	/// Get the Date, Time and offset set via a call to Set(const DcsDate &dcsdate, const DcsTime &dcsTime, const S_INT16 nOffset);
	/// @return true/false
	///
	bool Get(DcsDate &strDate, DcsTime &strTime, S_INT16 &strOffsetFromUTC)const;

	///
	/// Set with combined string in "YYYYMMDDHHMMSS.FFFFFF&ZZXX", "-YYYYMMDDHHMMSS.FFFFFF&ZZXX", "YYYYMMDDHHMMSS.FFFFFF&ZZXX-", or "YYYYMMDDHHMMSS.FFFFFF&ZZXX-YYYYMMDDHHMMSS.FFFFFF&ZZXX" format
	/// "YYYYMMDD": Same as DcsDate
	/// "HHMMSS.FFFFFF": Same as DcsTime
	/// "&ZZXX": & = '+' or '-', ZZ = Hour offset, XX = Minute Offset
	///
	/// @param strCombined Combined string
	/// @return true/false
	///
	bool SetCombinedString(const DcsString &strCombined);

	///
	/// Check if the string follows VR = DT restrictions
	///
	///	@return true/false
	///
	virtual bool IsValid()const;

	///
	/// Returns the minimum offset value (-1200)
	///
	/// @return Minimum offset value
	///
	S_INT16 GetMinOffset()const;

	///
	/// Returns the maximum offset value (1400)
	///
	/// @return Maximum offset value
	///
	S_INT16 GetMaxOffset()const;

	///
	/// Determine if the DcsDateTime object has no contents
	/// @return true/false
	///
	bool Empty() const;
	
protected:

	class	ImplDcsDateTime;
	ImplDcsDateTime	*m_pImplDcsDateTime;
};
//////////////////////////////////////////////

//////////////////////////////////////////////
///
/// \class DcsAge
/// \brief This string represents an age. The string has the format "NNNT", where N is a number '0'-'9' and
///			T is 'D' for days, 'M' for months, or 'Y' for years.
///
class DcsAge : public DcsString
{
public:

	///
	/// Initialize with default values
	///
	DcsAge();

	///
	/// Initialize with a char string
	///
	/// @param pstr char string
	///
	DcsAge(const char* pstr);

	///
	/// Initialize with a DcsString object
	///
	/// @param str DcsString object
	///
	DcsAge(const DcsString& str);

	DcsAge(const DcsAge&); ///< Copy constructor

	///
	/// Copy a string
	///
	/// @param pstr string to compare
	///
	DcsAge& operator=(const char *pstr);

	///
	/// Copy a DcsString object
	///
	/// @param str DcsString object to copy
	///
	DcsAge& operator=(const DcsString &str);

	///
	/// Copy another DcsAge object
	///
	/// @param dcsage DcsAge object to copy
	///
	DcsAge& operator=(const DcsAge &dcsage);

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const char *pstr)const;

	///
	/// Compare a string
	///
	/// @param pstr string to compare
	///	@return true/false
	///
	bool operator==(const wchar_t *pstr)const;

	///
	/// Compare a string
	///
	/// @param dcsage String to compare
	///
	bool operator==(const DcsAge &dcsage)const;

	///
	/// Compare char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const char* pstr)const;

	///
	/// Compare wide char string
	///
	/// @param pstr String to compare
	///	@return true/false
	///
	bool operator!=(const wchar_t* pstr)const;

	///
	/// Compare a string
	///
	/// @param dcsage String to compare
	///
	bool operator!=(const DcsAge &dcsage)const;

	///
	/// Set age in days.  Must be no larger than 999.
	///
	/// @param nAge nAge in days
	///
	bool SetAgeInDays(const S_UINT16 nAge);

	///
	/// Set age in months.  Must be no larger than 999.
	///
	/// @param nAge nAge in months
	///
	bool SetAgeInMonths(const S_UINT16 nAge);

	///
	/// Set age in years.  Must be no larger than 999.
	///
	/// @param nAge Age in years
	///
	bool SetAgeInYears(const S_UINT16 nAge);

	///
	/// Check if the string follows VR = AS restrictions
	/// String must be 4 characters.
	/// First 3 characters must be in the range '0'-'9'
	/// Last character must be 'D', 'M', or 'Y'
	///	@return true/false
	///
	virtual bool IsValid()const;
};
//////////////////////////////////////////////

}//namespace SDICOS

#endif
