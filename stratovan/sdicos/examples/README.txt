##############################################################################
### Stratovan Corporation Copyright and Disclaimer Notice:
###
### Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
###
### Permission to use, copy, modify, and distribute this software and its
### documentation without a signed licensing agreement, is hereby granted,
### provided that this copyright notice, this paragraph and the following two
### paragraphs appear in all copies, modifications, and distributions.
###
### IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
### SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
### ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
### STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
###
### STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
### TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
### SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
### PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
### SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS UNLESS DIRECTED BY THE
### U.S. GOVERNMENT'S TRANSPORTATION SECURITY ADMINISTRATION (TSA).
###
##############################################################################
//////////////////////////////////////////////////////////////////////////////


The example code shows how to accomplish different tasks using the DICOS SDK as
well as how to use the different DICOS SDK data structures and classes. The
examples should be run in conjunction with reading the source code and
subsequently incorporated into a new application.

See the DICOS documentation for details on the examples
https://www.stratovan.com/application/dicos-docs?docsPath=examples.html



BUILDING EXAMPLES
=================
It is expected that the distribution folders examples/, lib/, and include/ all
reside under the root installation folder.

The examples/ folder has CMake files that finds all of the examples and sets up
the infrastructure to compile them with 'make' (Linux) or Visual Studios
(Windows). The examples link with the libraries under 'lib/DICOS', and their
executables are generated in the folder 'examples/bin'

Each example folder contains a *.cpp source file.



BUILDING EXAMPLES FOR LINUX
===========================
---------------------------------------------------------------------------
# Create a folder to hold the cmake output files
mkdir foo

# Change to new folder
cd foo

# Run cmake with path to the examples folder and then run make
cmake ../
make
---------------------------------------------------------------------------


LINUX DEBUG Builds
------------------
Add the following flag to the CMake command line:

-DCMAKE_BUILD_TYPE=DEBUG



BUILDING EXAMPLES FOR WINDOWS DISTRIBUTIONS
===========================================
This example creates an infrastructure for compiling VS2022 solutions. It
creates a folder 'foo' and builds the example project files. After that the
user opens the solution project to compile them.

See the list below the example for instructions on building for other versions
of Visual Studio.

---------------------------------------------------------------------------
:: Create a folder to hold the cmake output files
mkdir foo

:: Change into the new folder
cd foo

:: Run cmake identifying the version of Visual Studio and 64 bit compiles
cmake -G "Visual Studio 17 2022"  -A x64 ../

:: Open the resulting file that is generated in foo
open DICOSExamples.sln
---------------------------------------------------------------------------


Selecting The Version Of Visual Studios
---------------------------------------
The 'cmake -G [var]' variable identifies the version of Visual Studio to
generate solutions for. Below are build command examples for other versions.

    Visual Studio 2017:    cmake -G "Visual Studio 15 2017" -A x64
    Visual Studio 2019:    cmake -G "Visual Studio 16 2019" -A x64
    Visual Studio 2022:    cmake -G "Visual Studio 17 2022" -A x64

Invoke 'cmake -G' without any parameters to see a list of all the Visual Studio
versions that Cmake supports.

WARNING: You can only generate projects/solutions for versions of Visual Studio
that you have installed.


Generating A 32-Bit Solution
----------------------------
Change the parameters '-A x64' to '-A Win32' to make a 32-bit solution.


Troubleshooting
---------------
If CMake fails to start:
1. make sure CMake is installed.
2. make sure CMake is included in the PATH environment variable
3. In rare circumstances make sure that the Command Prompt or Powershell is
   started with admin rights.



EXAMPLE FOLDER OVERVIEW
========================

UserLevel:
    Examples of the User-Level API. User-Level API is the easiest of the 3
    DICOS Library interfaces to use for creating/accessing/modifying DICOS
    files.

ModuleLevel:
    Examples of the Module-Level API. Module-Level API is more difficult to
    use, but follows the module layout defined in the DICOS specification.

TagLevel:
    Examples of the Tag-Level API. Tag-Level API provides access to DICOS tags
    and is the most difficult interface to DICOS.

MemoryManager:
    Examples showing how to provide custom memory allocation and deallocation
    methods to the DICOS library for pixel data. Examples include attaching the
    custom memory manager to a DICOS server, a file loader callback interface,
    and to User-, Module-, and Tag-Level objects.

DataFiles:
    Contains all sample DICOS data

Version:
    Examples of accessing this SDK's version

VTKToDICOS:
    Example of converting from a non-DICOS format to DICOS

Converter:
    Examples of converting from older version of DICOS to latest

FileListing:
    Example showing how to list all DICOS files in a folder

Volume:
    Examples of creating and traversing image data structures

NetworkingExamples:

    The Networking Examples are split across three subfolders: Client, Host, and TLS

    Host:
        Examples of managing a DICOS server

    Client:
        Examples of communicating with an existing server from the client side

    TLS:
        Setting up TLS communications between servers and clients


V03 Updates:

    Updates new to the V03 SDK. These are split in two subfolders, API and Features

    V03_API:
        Examples showing the API changes between the V02A and V03 SDK

    V03_Features:
        Examples showing the new values added by the V03 SDK




ADDITIONAL EXAMPLE DETAILS
==========================

Client Example Code (Client/):
------------------------------------------------------
    Examples in this folder show how to use the DcsClient to send DICOS files
    or different types of commands over the network to a DICOS Host/Server that
    is listening at the correct port and IP.

    For these examples to work they need to communicate with a DcsServer.

    See the section below for instructions on how to setup a DcsServer to
    receive DICOS files and how to use the SimpleSendData example code in
    conjunction with the example in Host/MultipleConnections.


    SimpleSendData:
        This example shows how to use the User-Level API method
        SendOverNetwork() to send a CT DICOS file to a listening DcsServer.


Host Example Code (Host/):
---------------------------------------------------
    Examples in this folder show how to use the DcsServer object to receive
    DICOS files over a network connection.

    The DcsServer object listens on an IP Address and Port and waits for
    connections. These examples show how to setup DcsServer objects that listen
    for and accept connections with different criteria.

    They are not meant as standalone applications for demo purposes.

    HostDaemon:
        This example shows how to create a daemon process on Linux/Unix that
        contains a DcsServer.

        The server listens for connections and writes a message to the system
        log.

        The example contains a simple client that send a CT file to the server.


    MultipleConnections:
        This example creates a DcServer object that accepts connections from
        multiple DICOS Clients.



DcsServer Instructions to Create and Start a server that listens for DICOS
Connections:
=============================================================================
    This uses the examples in Host/MultipleConnections and Client/SimpleSendData

    1) Modify the file Host/MultipleConnections/main.cpp so
       that the DcsServer listens on the IP Address and port or your choosing.

    2) Modify the file Client/SimpleSendData/main.cpp so that
       the call to ct.SendOverNetwork() uses the same port and IP Address that
       the DcsServer from Step 1 is listening to.

    3) Compile and run the Multiple_Connections executable. It should pause and
       wait for connections.

    4) Compile and run the SimpleSendData executable and check the output from
    the DcsServer which indicates that the file was received.



SUPPORT
=======
    For questions, email DICOS Support at support@stratovan.com, or visit the
    support forum at: https://www.stratovan.com/software/security-software/dicos
