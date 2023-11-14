##############################################################################
#
# Stratovan Corporation Copyright and Disclaimer Notice:
#
# Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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

cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0011 NEW)


include(CMakePrintHelpers RESULT_VARIABLE INCLUDE_SUCCESS)
if(NOT INCLUDE_SUCCESS)
    message(FATAL_ERROR "\nERROR: Could not load/find include file\n")
endif()


include(testInstallerExamples.cmake RESULT_VARIABLE INCLUDE_SUCCESS)
if(NOT INCLUDE_SUCCESS)
    message(FATAL_ERROR "\nERROR: Could not load/find include file\n")
endif()


if(NOT ${CMAKE_HOST_UNIX})
    message(FATAL_ERROR
        "Unexpected/unsupported CMake System Name ${CMAKE_SYSTEM_NAME}")
endif()



#
# This CMakeLists.txt file is meant to be included as part of the DICOS Toolkit distribution
# It assumes the location of libs and include folders in the following format
#
# <installation-root>/
#   +--examples/
#   |    +--CMakeListsUnix.txt (this file)
#   +--lib
#   +--include

project(DICOSExamples)


#
# Add compilers flags for release and debug builds
#
if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    MESSAGE("Setting compiler flags for DEBUG")
    set(CMAKE_C_FLAGS "-g -Wextra -Wall -D_DEBUG -DDEBUG -D__DEBUG__")
    set(CMAKE_CXX_FLAGS "-g -Wextra -Wall -D_DEBUG -DDEBUG -D__DEBUG__")
elseif (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
    MESSAGE("Setting compiler flags for RELEASE")
    set(CMAKE_C_FLAGS "-O3 -Wextra -Wall")
    set(CMAKE_CXX_FLAGS "-O3 -fpermissive -Wextra -Wall")
endif ()


option(ENABLE_32_BIT_BUILD "Do a 32B compile" OFF)

if (ENABLE_32_BIT_BUILD)
    set(ARCH 32)
else()
    set(ARCH 64)    
endif()


set(EXAMPLES_DIR ${CMAKE_CURRENT_LIST_DIR})
get_filename_component(DICOS_ROOT_DIR "${EXAMPLES_DIR}/.." REALPATH)

cmake_print_variables(DICOS_ROOT_DIR)
cmake_print_variables(EXAMPLES_DIR)


if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_definitions( -D__LINUX__ -DC_INLINE=inline)
else()
    add_definitions( -D__APPLE__ -DC_INLINE=inline)
endif()


# Create Importated target for DICOS Library
add_library(libDICOS STATIC IMPORTED)
set_target_properties(libDICOS PROPERTIES
    IMPORTED_LOCATION "${DICOS_ROOT_DIR}/lib/libDICOS_${ARCH}R.a"
    IMPORTED_LINK_INTERFACE_LIBRARIES "-lpthread;-ldl")
target_include_directories(libDICOS INTERFACE "${DICOS_ROOT_DIR}/include")




##############################################################################
#
# Build the DICOS Examples
#
# Each example is expected to be fully contained in a single .cpp file. A new
# target is created for each .cpp file found.
#
stvn_add_dicos_examples("${EXAMPLES_DIR}" "libDICOS")
