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
#ifndef _STRATOVAN_DICOS_ERROR_LOG_H_
#define _STRATOVAN_DICOS_ERROR_LOG_H_

#include <ostream>

#include "SDICOS/String.h"
#include "SDICOS/Tag.h"
#include "SDICOS/Array1D.h"

namespace SDICOS
{

namespace Redirect
{
	/// Enumerations for message identification in redirected error log messages
	typedef enum
	{
		enumRedirect_Warning,
		enumRedirect_Error,
	}REDIRECT_LOG_TYPE;

	/// Typedef for error log's redirect function
	typedef void(*PFN_REDIRECT_LOG_MESSAGES)(const REDIRECT_LOG_TYPE nRedirectLogType, const char *pcMessage);

}//namespace Redirect

///
/// \class ErrorLog
/// \brief Implements ErrorLog
///
class ErrorLog
{
public:

	/// Redirect all all error log messages to the specified function.
	/// @param pfnRedirect All messages redirected to this function 
	static void SetErrorLogRedirect(Redirect::PFN_REDIRECT_LOG_MESSAGES pfnRedirect);

	/// @see SetErrorLogRedirect
	static bool HasRedirect();

	/// Don't call the error log redirect function for this ErrorLog instance
	/// @see SetErrorLogRedirect
	void IgnoreErrorLogRedirect();
	/// Default Behavior: Call the error log redirect function for this ErrorLog instance
	/// @see SetErrorLogRedirect
	void UseErrorLogRedirect();

	///
	/// \class LogItem
	/// \brief Implements LogItem
	///
	class LogItem
	{
	public:
		///
		/// Initialize with default values
		///
		LogItem();

		///
		/// Initialize with a LogItem object
		///
		LogItem(const LogItem &logitem);

		///
		/// Destructor
		///
		virtual ~LogItem();

		///
		/// Copy a LogItem object
		///
		/// @param logitem Object to copy
		/// @return Reference to this object
		///
		LogItem& operator=(const LogItem &logitem);

		///
		/// Delete all data
		///
		virtual void FreeMemory();

		///
		/// Set log as an error
		///
		virtual void SetAsError();

		///
		/// Check if log is an error
		///
		/// @return true/false
		///
		virtual bool IsError()const;

		///
		/// Set log as a warning
		///
		virtual void SetAsWarning();

		///
		/// Check if log is a warning
		///
		/// @return true/false
		///
		virtual bool IsWarning()const;

		///
		/// Save the log message
		/// 
		/// @param strMessage Log message
		///
		virtual void SetMessage(const DcsString strMessage);

		///
		/// Get the log message
		///
		/// @param strMessage Log message
		///
		virtual void GetMessage(DcsString &strMessage)const;

		///
		/// Set tag identified with this error/warning
		///
		/// @param strVR VR of attribute
		/// @param nGroup Tag group number
		/// @param nElement Tag element number
		/// @return true/false
		///
		virtual bool SetTag(const DcsString &strVR, const S_UINT16 nGroup, const S_UINT16 nElement);

		///
		/// Set tag identified with this error/warning
		///
		/// @param strVR VR of attribute
		/// @param tag DICOS Tag
		/// @return true/false
		///
		virtual bool SetTag(const DcsString &strVR, const Tag &tag);

		///
		/// Get the tag in string format : "[VR] ([group], [element])"
		///
		/// @param strTag Tag as string
		/// @return true/false
		///
		virtual bool GetTagAsString(DcsString &strTag)const;

	private:
		class ImplLogItem;
		ImplLogItem	*m_pImplLogItem; ///< Internal implementation
	};

	///
	/// \class Warning
	/// \brief Implements Warning
	///
	class Warning : public LogItem
	{
	public:
		///
		/// Initialize with default values
		///
		Warning();

		///
		/// Initualize Warning object
		///
		Warning(const Warning &warning);

		///
		/// Copy a Warning object
		///
		/// @param logitem Object to copy
		/// @return Reference to this object
		///
		Warning& operator=(const Warning &logitem);

	private:

		///
		/// Disabled
		///
		virtual void SetAsError();

		///
		/// Disabled
		///
		virtual bool IsError() const;

		///
		/// Automatically set as a warning during initialization
		///
		virtual void SetAsWarning();
	};

	///
	/// \class Error
	/// \brief Implements Error
	///
	class Error : public LogItem
	{
	public:
		///
		/// Initialize with default values
		///
		Error();

		///
		/// Initualize error object
		///
		Error(const Error &error);

		///
		/// Copy a Error object
		///
		/// @param logitem Object to copy
		/// @return Reference to this object
		///
		Error& operator=(const Error &logitem);

	private:

		///
		/// Disabled
		///
		virtual void SetAsWarning();

		///
		/// Disabled
		///
		virtual bool IsWarning() const;

		///
		/// Automatically set as a warning during initialization
		///
		virtual void SetAsError();
	};

	///
	/// Initialize with default values
	///
	ErrorLog();

	///
	/// Initialize with an ErrorLog object
	///
	ErrorLog(const ErrorLog &errorlog);

	///
	/// Destructor
	///
	~ErrorLog();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy an ErrorLog object
	///
	ErrorLog& operator=(const ErrorLog &errorlog);

	///
	/// Print Errors and then Warnings to the given ostream.
	///
	friend std::ostream& operator<<(std::ostream& os, const ErrorLog &errorlog);

	///
	/// Set the current sequence associated with added errors and warnings.  
	/// All added errors and warnings will base their reported hierarchy path from the sequences on this stack.
	///
	/// @param nGroup Group number of sequence
	/// @param nElement Element number of sequence
	/// @return true/false
	///
	bool PushSequence(const S_UINT16 nGroup, const S_UINT16 nElement);

	///
	/// Set the current sequence associated with added errors and warnings.  
	/// All added errors and warnings will base their reported hierarchy path from the sequences on this stack.
	///
	/// @param tag Tag of sequence
	/// @return true/false
	///
	bool PushSequence(const Tag &tag);

	///
	/// Returns the depth of the sequence stack
	///
	S_UINT32 GetSequenceDepth()const;

	///
	/// Pop the current sequence
	///
	/// @return Sequence in string format "SQ ([group], [element])"
	///
	DcsString PopSequence();

	///
	/// Add warning
	///
	/// @param warning Warning to add
	/// @return true/false
	///
	bool AddWarning(const Warning &warning);

	///
	/// Add warning with the given tag and message
	///
	/// @param strVR VR String
	/// @param nGroup DICOS Tag Group
	/// @param nElement DICOS Tag Element
	/// @param message Warning message
	/// @return true/false
	///
	bool AddWarning(const DcsString &strVR, const S_UINT16 nGroup, const S_UINT16 nElement, const DcsString &message);

	///
	/// Add warning with the given tag and message
	///
	/// @param strVR VR String
	/// @param tag DICOS Tag
	/// @param message Warning message
	/// @return true/false
	///
	bool AddWarning(const DcsString &strVR, const Tag& tag, const DcsString &message);

	///
	/// Add warning with the given message
	///
	/// @param message Warning message
	/// @return true/false
	///
	bool AddWarning(const DcsString &message);

	///
	/// Add error
	///
	/// @param error Error to add
	/// @return true/false
	///
	bool AddError(const Error &error);

	///
	/// Add error with the given tag and message
	///
	/// @param strVR VR String
	/// @param nGroup DICOS Tag Group
	/// @param nElement DICOS Tag Element
	/// @param message Error message
	/// @return true/false
	///
	bool AddError(const DcsString &strVR, const S_UINT16 nGroup, const S_UINT16 nElement, const DcsString &message);

	///
	/// Add error with the given tag and message
	///
	/// @param strVR VR String
	/// @param tag DICOS Tag
	/// @param message Error message
	/// @return true/false
	///
	bool AddError(const DcsString &strVR, const Tag& tag, const DcsString &message);

	///
	/// Add error with the given message
	///
	/// @param strMessage Error message
	/// @return true/false
	///
	bool AddError(const DcsString &strMessage);

	///
	/// Get array of all errors and warnings in the format "[Error/Warning]: [Message] [Path: [Sequence Hierarchy] -> [VR] [Tag]]"
	///	Example: "Error: Required tag missing. [SQ (1234, 5678) -> SQ (4321, 8765) -> SH (8523, 9632)]"
	///
	/// @param arrayErrors Array of errors
	/// @param arrayWarnings Array of warnings
	/// @return true/false
	///
	bool GetErrorLog(Array1D<DcsString> &arrayErrors, Array1D<DcsString> &arrayWarnings)const;

	/// Return the error log as a string. If there are no errors or warnings, an empty string is returned.
	DcsString GetErrorLog()const;

	/// Return the indexed error. If the index is greater than NumErrors()-1, an empty string is returned.
	DcsString GetError(const S_UINT32 n)const;
	/// Return the indexed warning. If the index is outside the bounds [0, NumWarnings()-1], an empty string is returned.
	DcsString GetWarning(const S_UINT32 n)const;

	///
	/// Return number of errors
	///
	S_UINT32 NumErrors() const;

	///
	/// Return the number of warnings
	///
	S_UINT32 NumWarnings() const;

	///
	/// Returns true if errors are in the log
	///
	bool HasErrors()const;

	///
	/// Returns true if warnings are in the log
	///
	bool HasWarnings()const;

	///
	/// Write errors and warnings to file as text
	///
	bool WriteLog(const Filename &filename)const;

	///
	/// Write errors and warnings to file as text
	///
	bool WriteLog(IFile &file)const;

private:
	class ImplErrorLog;
	ImplErrorLog *m_pImplErrorLog; ///< Internal implementation

	friend std::ostream& operator<<(std::ostream& os, const ErrorLog::ImplErrorLog &errorlog);
};

}//namespace SDICOS

#endif
