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
#ifndef _STRATOVAN_DICOS_FILESYSTEM_H_
#define _STRATOVAN_DICOS_FILESYSTEM_H_

#include <vector>
#include <string>

namespace SDICOS
{

class IFile;

///
/// \class Filter
/// \brief Specify the file filter to various common dialogs.
///
/// This class is used to specify the file filter to various common dialogs.
/// Example of valid filters are:
///		Filter("Text Files (*.txt)",					"*.txt")							// A single text file
///		Filter("Image Files (*.bmp;*.jpg;*.tiff;...),	"*.bmp;*.jpg;*.tiff;*.png;*.gif")	// Multiple file extensions
///		Filter("All Files (*.*)",						"*.*")								// All files...
/// Stick these in a vector and pass them in to ChooseFile() or ChooseFiles() to specify the file types the dialog allows chosen...
///
class Filter : public std::pair< std::string, std::string >
{
public:
	Filter(const std::string &strDescription = "", const std::string &strExtension = "")
		: std::pair< std::string, std::string >(strDescription, strExtension)
	{
	}

	int		GetNumberOfExtensions()const;
	bool	GetExtension(int nExt, std::string &strExt)const;
};

///
/// \class Folder
/// A class that supports cross-platform folder specification and access
///
class Folder
{
public:
	Folder(const std::string &strFolder = "");
	Folder(const Folder &folderParent, const std::string &strSubFolder);

	void Set(const std::string &strFolder = "");

	/// For the windows folder	"c:\folder\subfolder", Drive() returns "c:"
	/// For the mac folder		"/folder/subfolder", Drive() returns "/"
	std::string		GetDrive()const;

	/// For the windows folder	"c:\folder\subfolder", Directory() returns "\folder\subfolder\", note that the correct slash is added to the end if one is missing
	/// For the mac folder		"/folder/subfolder", Directory() returns "folder/subfolder/", note that the correct slash is added to the end if one is missing
	std::string		GetDirectory()const;

	/// For the windows folder	"c:\folder\subfolder", GetFullFolder() returns "c:\folder\subfolder\", note that the correct slash is added to the end if one is missing
	/// For the mac folder		"/folder/subfolder", GetFullFolder() returns "/folder/subfolder/", note that the correct slash is added to the end if one is missing
	std::string		GetFullFolder()const;

	// Obtains the parent folder for this object. Returns true on success, false if this object represents the topmost folder.
	/// For the windows folder	"c:\folder\subfolder", Directory() returns "\folder\subfolder\", and GetParentFolder() returns "c:\folder\". Returns false if "\" is the current folder
	/// For the mac folder		"/folder/subfolder", Directory() returns "folder/subfolder/", and GetParentFolder() returns "/folder/". Returns false if "" is the current folder
	bool			GetParentFolder(Folder &folder)const;

	/// For the windows folder	"c:\folder\subfolder", Directory() returns "\folder\subfolder\", and GetSubFolder() returns "subfolder\".
	/// For the mac folder		"/folder/subfolder", Directory() returns "folder/subfolder/", and GetSubFolder() returns "subfolder/".
	std::string		GetSubFolder()const;

	bool operator< (const Folder &obj)const;
	bool operator> (const Folder &obj)const		{ return !operator<(obj) && operator!=(obj);}

	bool operator== (const Folder &obj)const;
	bool operator!= (const Folder &obj)const	{return !operator==(obj);}

	/// Sets the Folder to the current working directory
	void GetCurrentWorkingFolder();

	/// Sets the current working folder to the folder represented by this object
	void SetCurrentWorkingFolder()const;

	/// Get last recorded error message. Not all methods may set/reset this string.
	const std::string& GetLastError() const { return m_strLastError; }
		
protected:
	std::string		m_strDrive, m_strDirectory;
		
	/// string to store last error message from a folder operation
	/// declared as mutable for use in const error checking methods
	mutable std::string		m_strLastError;
};

///
/// \class Filename
/// A class that supports cross-platform file specification and access
///
class Filename : public Folder
{
public:
	Filename(const char * strFullPath);
	Filename(const std::string &strFullpath = "");
	Filename(const Folder &folder, const std::string &strFilename = "");

	/// This constructor appends an extension if one does not exist...based on the passed filter
	/// If multiple extensions are specified in the filter, i.e. "*.bmp;*.jpg;*.tiff", the first extension
	/// (*.bmp in this case) is appended if the file name does not have an extension...
	Filename(const std::string &strFullpath, const Filter &filter);

	void Set(const std::string &strFullpath = "");

	/// For the windows file	"c:\folder\subfolder\file.txt", Name() returns "file"
	/// For the mac file		"/folder/subfolder/file.txt", Name() returns "file"
	std::string		GetName()const;

	/// For the windows file	"c:\folder\subfolder\file.txt", Extension() returns ".txt"
	/// For the mac file		"/folder/subfolder/file.txt", Extension() returns ".txt"
	std::string		GetExtension()const;

	/// For the windows file	"c:\folder\subfolder\file.txt", Name() returns "file.txt"
	/// For the mac file		"/folder/subfolder/file.txt", Name() returns "file.txt"
	std::string		GetNameAndExtension()const;

	/// For the windows file	"c:\folder\subfolder\file.txt", FullPath() returns "c:\folder\subfolder\file.txt"
	/// For the mac file		"/folder/subfolder/file.txt", FullPath() returns "/folder/subfolder/file.txt"
	std::string		GetFullPath()const;

	/// For the windows file	"c:\folder\subfolder\file.txt", GetFolder() returns a Folder object corresponding to "c:\folder\subfolder\"
	/// For the mac file		"/folder/subfolder/file.txt", GetFolder() returns a Folder object corresponding to "/folder/subfolder/"
	Folder			GetFolder()const;

	void			SetName(const std::string &strName);
	void			SetExtension(const std::string &strExt);

	/// Compare alphabetically by Drive, Directory, Filename, Extension
	bool operator< (const Filename &obj)const;

	/// Compare alphabetically by Drive, Directory, Filename, Extension
	bool operator> (const Folder &obj)const		{ return !operator<(obj) && operator!=(obj);}

	bool operator== (const Filename &obj)const;
	bool operator!= (const Filename &obj)const	{return !operator==(obj);}

	/// Stream insertion operator
	/// Inserts the result of GetFullPath() into the stream
	friend std::ostream& operator<<(std::ostream& os, const Filename& f);
protected:
	std::string		m_strName, m_strExtension;
};

bool	FileExists(const Filename &filename);	///< Check for file existence
bool	FolderExists(const Folder &folder);		///< Check for folder existence
bool	RemoveFile(const Filename &filename);	///< Deletes the specified file
bool	CreateFolder(const Folder &folder, bool bParentToo = true);		///< Creates the folder

bool	SetCurrentWorkingDirectory(const Folder &folder);	///< Set the current working directory
Folder	GetCurrentWorkingDirectory();						///< Get the current working directory

Filename		GetExecutablePath();													///< Returns filename of the running executable...
Folder			GetExecutableFolder();													///< Returns folder of the running executable...

/// Windows: Returns the "My Documents" folder for this user 
/// Linux: Creates and returns a "MyDocuments" folder in the users home directory
/// OSX: TODO: return path to user's documents folder
Folder			GetUserFolder();

/// Windows: Returns a temporary folder c:\\tmp
/// Linux: Returns "/tmp"
/// OSX: Returns "/tmp"
Folder			GetTemporaryFolder();

/// Windows: Returns a temporary filename in c:\\tmp that starts with the given prefix
/// Linux/OSX: Returns a temporary filename in /tmp that starts with the given prefix
Filename		GetTemporaryFilename(const std::string &strPrefix = "sdcs");

/// Windows: Something similar to (XP) "C:\Documents and Settings\All Users\Documents" and (Vista) "C:\Users\Public\Documents". 
///			This folder should be "writeable" by all users even non-administrators.
/// Linux: Create and return the temporary folder "/var/tmp/AppData"
/// OSX: TODO:OSX Implementation for system wide Applocation data folder
Folder			GetApplicationDataFolderForAllUsers();

/// Windows: Something similar to (XP) "C:\Documents and Settings\User Name\Local Settings\Application Data" and (Vista) "C:\Users\UserName\AppData\Local"
/// Linux: Create and return a folder "AppData" in the user's home directory
/// OSX: TODO: determine where OSX keeps application specific data
Folder			GetApplicationDataFolderForThisUser();


}	// namespace SDICOS


#endif









