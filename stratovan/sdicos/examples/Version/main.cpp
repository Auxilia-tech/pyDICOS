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
// StartDICOSVersionExample

#include "SDICOS/DICOS.h"	//DICOS include header
#include <iostream>
#include <ctime>

//
// Print DICOS Library Version Information
// This information is used to identify the DICOS Library Version when reporting bugs.
//
void PrintDICOSVersionInformation()
{
	std::cout << "Build Version " << SDICOS::GetBuildVersion() << std::endl;
	std::cout << "Build Operating System " << SDICOS::GetBuildOperatingSystem() << std::endl;
	std::cout << "Build Type " << SDICOS::GetBuildType() << std::endl;
	std::cout << "Build Bit Depth " << SDICOS::GetBuildBit() << std::endl;
	std::cout << "Build Date " << SDICOS::GetBuildYear() << "-" << SDICOS::GetBuildMonth() << "-" << SDICOS::GetBuildDay() << std::endl;
	std::cout << "Build Time (HH:MM) " << SDICOS::GetBuildTime() << std::endl;
}

int main() 
{
	PrintDICOSVersionInformation();
	return 0;
}
// EndDICOSVersionExample
