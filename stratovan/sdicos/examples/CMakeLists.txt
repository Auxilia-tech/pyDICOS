##############################################################################
#
# Stratovan Corporation Copyright and Disclaimer Notice:
#
# Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation without a signed licensing agreement, is hereby granted,
# provided that this copyright notice, this paragraph and the following two
# paragraphs appear in all copies, modifications, and distributions.
#
# IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
# SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
# ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
# STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
# SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
# PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
# SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
#
##############################################################################

#
# This CMakeLists.txt is used to create a VS solution
# or a unix makefile for building DICOS examples
#
cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0011 NEW)

project(DUMMY) # needed to avoid project name warning

set(CMAKE_CONFIGURATION_TYPES Debug Release)

if(CMAKE_HOST_WIN32)
	include("CMakeListsWindows.cmake")	
elseif(CMAKE_HOST_UNIX)
	include("CMakeListsUnix.cmake")
endif()
