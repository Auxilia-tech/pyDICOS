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
#include "SDICOS/DICOS.h"

const std::string exampleFilename("AttributeManagerExampleFile.dcs");

namespace ExampleAttributeManager
{
/// \page AttributeManagerExamples Attribute Manager Examples
/// \section AddFindRemove Add Find Remove
/// Example of adding, finding, and removing attributes from
/// an attribute manager.
/// \code
void Add_Find_Remove_Attributes()
{
	using namespace SDICOS;

	AttributeManager manager; ///< Attribute manager
	AttributeManager::AttributePointer<AttributeString>	attptrStr;	///< Pointer to AttributeString
	AttributeManager::AttributePointer<AttributeString>	attptrStrGet;	///< Pointer to AttributeString
	Tag tag;	///< Tag

	tag.Set(0x1000, 0x0000);	///< Set tag for attribute to create

	/* Allocate an AttributeString object in the manager with the specified tag.
	 The third parameter, which is set to <b>true<\b>, indicates to allocate the attribute
	 if it is not found. */
	manager.FindAttribute(tag, attptrStr, true); 

	/* Set the size of the string array 1 and define the string as long string.  
	 This creates an attribute with VM = 1 and VR = LO.*/
	attptrStr->SetSize(1, AttributeString::enumLongString);

	(*attptrStr)[0] = "String"; /// Set the string to a value of "String"

	/* Find the attribute using an attribute pointer
	 The third parameter is not passed and left as default, which is <b>false<\b>.
	 The function will return <b>false<\b> is the attribute is not found. */
	manager.FindAttribute(tag, attptrStrGet);

	manager.DeleteAttribute(tag); /// Delete the attribute
} // EndAdd_Find_Remove_Attributes
/// \endcode

/// \section ReadWrite
/// Example of reading and writing functions for an attribute manager
/// \code
void Read_and_Write()
{
	using namespace SDICOS;

	AttributeManager manager; ///< Attribute manager
	File file;	///< File
	Filename filename;	///< File name
	ErrorLog errorlog;	///< Error log

	/* Method 1: Read and write from and to a file using a file name */
	{
		
		filename.Set(exampleFilename);///< Set the file name
		manager.Read(filename, errorlog);	/// Read from file. All errors stored in error log.
		manager.Write(filename, errorlog);	/// Write to file. All errors stored in error log.
	}

	/* Method 2: Read and write using a File object */
	{
		filename.Set(exampleFilename); /// Set the file name

		{
			file.OpenReading(filename); /// Open the file for reading
			manager.Read(file, errorlog);	/// Read from file.  All errors stored in error log.
			file.Close(); /// Close the file
		}
		{
			file.OpenWriting(filename); /// Open the file for writing
			manager.Write(file, errorlog);	/// Write to file.  All errors stored in error log.
			file.Close(); /// Close the file
		}
	}

}///EndRead_and_Write
/// \endcode

/// \section AttributeList
/// Example of writing a file that lists all the attributes in an attribute manager.
/// \code
void Write_Attribute_List_to_File()
{
	using namespace SDICOS;

	AttributeManager manager; ///< Attribute manager
	Filename filename;	///< File name

	AttributeManager::AttributePointer<AttributeString>	attptrStr;	///< Pointer to AttributeString
	Tag tag;	///< Tag

	/* Set tag for attribute to create */
	tag.Set(0x1000, 0x0000);	

	/* 
	 Allocate an AttributeString object in the manager with the specified tag.
	 The third parameter, which is set to <b>true<\b>, indicates to allocate the attribute
	 if it is not found.
	 */
	manager.FindAttribute(tag, attptrStr, true); 

	/* 
	 Set the size of the string array to 2 and define the string as long string.  
	 This creates an attribute with VM = 2 and VR = LO.
	 */
	attptrStr->SetSize(2, AttributeString::enumLongString);

	(*attptrStr)[0] = "String";
	(*attptrStr)[1] = "String Cheese";
		
	filename.Set(exampleFilename);///< Set the file name
	manager.WriteToFileAsText(filename); ///< Write a listing of attributes to file.  Includes tag, VR, and data.
}///EndWrite_Attribute_List_to_File
/// \endcode

/// \section Sequences
/// Example of using sequences
/// \verbatim
void Sequences()
{
	using namespace SDICOS;

	AttributeManager manager; ///< Attribute manager
	AttributeManager::AttributePointer<AttributeSequence> attptrSQ;	///< Pointer to AttributeSequence
	AttributeManager::AttributePointer<AttributeSequence> attptrSQsub;	///< Pointer to AttributeSequence
	AttributeManager::AttributePointer<AttributeString> attptrStr;	///< Pointer to AttributeString
	AttributeManager::AttributePointer<AttributeString> attptrStrGet;	///< Pointer to AttributeString
	AttributeManager::AttributePointer<AttributeSignedInt16Bit> attptrSS;	///< Pointer to AttributeSignedInt16Bit
	const Tag tagSQ(0x8000, 0x0002);
	const Tag tagSQsub(0x2000, 0x0000);
	const Tag tagSH(0x8001, 0x0000);
	const Tag tagSS(0x8001, 0x0001);

	manager.FindAttribute(tagSQ, attptrSQ, true);	///< Allocate sequence

	/* Set number of sequence items to add.
	 Second parameter is the manager the sequence is allocated within.  This is 
	 only used to enable searching the the attribute manager when using <b>FindAttribute()<\b> with 
	 sequence items.*/
	attptrSQ->SetNumberOfItems(2, &manager);

	/* Each sequence item has the same functionality as an attribute manager */
	(*attptrSQ)[0].FindAttribute(tagSS, attptrSS, true);
	attptrSS->SetValue(5);	///< Set attribute value.

	/* Add attribute to the manager */
	manager.FindAttribute(tagSH, attptrStr, true);
	attptrStr->SetValue("string", AttributeString::enumShortString);

	/* Search for an attribute starting at a sequence item
	 Fourth parameter set to <b>true<\b> indicates to search parent attribute managers or parent sequence items 
	 for the attribute if it is not found in the sequence item.  In this case, it returns the attribute 
	 found in <b>manager<\b>. */
	(*attptrSQ)[0].FindAttribute(tagSH, attptrStrGet, false, true);

	/* Add a sequence to the sequence item */
	(*attptrSQ)[1].FindAttribute(tagSQsub, attptrSQsub, true);

	/* Allocate 1 item within the sequence and set the parent sequence item as the parent manager. */
	attptrSQsub->SetNumberOfItems(1, &(*attptrSQ)[1]);

	/* Finds the attribute in <b>manager<\b>. */
	(*attptrSQsub)[0].FindAttribute(tagSH, attptrStrGet, false, true);
}///EndSequences
/// \endverbatim

};

// Enable to build self contained executable
int main()
{
	ExampleAttributeManager::Write_Attribute_List_to_File();
	ExampleAttributeManager::Add_Find_Remove_Attributes();
	ExampleAttributeManager::Read_and_Write();
	ExampleAttributeManager::Sequences();
		
	std::cout << "AttributeManager Examples finished" << std::endl;
		
	return 0;
}
