##############################################################################
#
# Stratovan Corporation Copyright and Disclaimer Notice:
#
# Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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
# Set the ENABLE_32_BIT_BUILD flag to on if compiling on a 32B architecture
#

cmake_minimum_required (VERSION 3.10)
include_guard()
message(STATUS "Including ${CMAKE_CURRENT_LIST_FILE}")

include(CMakePrintHelpers RESULT_VARIABLE INCLUDE_SUCCESS)
if(NOT INCLUDE_SUCCESS)
    MESSAGE(FATAL_ERROR "\nERROR: Could not load/find include file\n")
endif()





##############################################################################
# Create a script data file to run all non-networking examples:
#
# The following stvn_run_cmd_ABC() functions defines and builds up the
# EXAMPLES_RUN_COMMANDS string with bash logic to initialize an array,
# a_examples() with all of the example executables to be run.
#
# stvn_run_cmd_init() - Initializes the EXAMPLES_RUN_COMMANDS string with the
#          prefix comments
#
# stvn_run_cmd_add() - Will add the example pathname to the
#          EXAMPLES_RUN_COMMANDS string if it is not a Client, Host or
#          Networking example.
#
# stvn_run_cmd_write() - Will write the EXAMPLES_RUN_COMMANDS string to the
#          script file.
#
##############################################################################


##############################################################################
# Set/Init EXAMPLES_RUN_COMMANDS global to an appropriate preamble for the
# Linux/Windows data file.
#
function(stvn_run_cmd_init)
    set(EXAMPLES_RUN_COMMANDS "#
# Copyright (c) 2022 by Stratovan Corporation. All Rights Reserved.
#
# This file is generated when CMake is run for DICOS examples, it is used with
# the script DICOSExamplesRunCommands script. It identifies all of the
# non-networking examples to be run.
")

    if(CMAKE_HOST_UNIX)
        # Bash specific comment
        string(APPEND EXAMPLES_RUN_COMMANDS "#
# Each line adds an element to the a_examples array, where each element is the
# full path to the example executable.
#
")
    ELSE()
        # BAT/CMD specific comment
        string(APPEND EXAMPLES_RUN_COMMANDS "#
# Define a set of array entries for the example source path and example binary
# path for 'Example X'
#
")
        # Windows uses :: instead of #
        string(REPLACE "#" "::"
            EXAMPLES_RUN_COMMANDS "${EXAMPLES_RUN_COMMANDS}")
    endif()

    set(EXAMPLES_RUN_COMMANDS "${EXAMPLES_RUN_COMMANDS}" PARENT_SCOPE)
    set(EXAMPLE_RUN_COUNT 0 PARENT_SCOPE) # initialize
endfunction(stvn_run_cmd_init)




##############################################################################
# Uses EXAMPLES_RUN_COMMANDS global
#
# EXAMPLE_PATH - Path to the example code
#
# BIN_PATH - Path to the example executable to run
function(stvn_run_cmd_add EXAMPLE_PATH BIN_PATHNAME)
    set(NW_TEST) # clear it
    string(REGEX
           MATCH "[E|e]xamples/(Client|Host|TLS)"
           NW_TEST "${EXAMPLE_PATH}")

    # Return if a network test
    if(NW_TEST)
        RETURN()
    endif()

    if(CMAKE_HOST_UNIX)
        list(APPEND EXAMPLES_RUN_COMMANDS
            "a_examples+=(\"${EXAMPLE_PATH}\;${BIN_PATHNAME}\")\n")
    else()
        math(EXPR EXAMPLE_RUN_COUNT "${EXAMPLE_RUN_COUNT} + 1")
        set(EXAMPLE_RUN_PREFIX "EX-${EXAMPLE_RUN_COUNT}")
        list(APPEND EXAMPLES_RUN_COMMANDS
            "SET \"DATA[${EXAMPLE_RUN_PREFIX}-ExPath]=${EXAMPLE_PATH}\"\n")
        list(APPEND EXAMPLES_RUN_COMMANDS
            "SET \"DATA[${EXAMPLE_RUN_PREFIX}-ExBin]=${BIN_PATHNAME}\"\n")
        list(APPEND EXAMPLES_RUN_COMMANDS
            "\n")
    endif()

    # push local value into parent
    set(EXAMPLES_RUN_COMMANDS "${EXAMPLES_RUN_COMMANDS}" PARENT_SCOPE)
    set(EXAMPLE_RUN_COUNT "${EXAMPLE_RUN_COUNT}" PARENT_SCOPE)
endfunction(stvn_run_cmd_add EXAMPLE_PATH)



##############################################################################
# Uses EXAMPLES_RUN_COMMANDS global
function(stvn_run_cmd_write EXAMPLES_DIR)

    # Only create the file for Linux
    if(CMAKE_HOST_UNIX)
        set(EXAMPLE_RUN_SUFFIX ".sh")
    else()
        set(EXAMPLE_RUN_SUFFIX ".bat")
    endif()

    set(SCRIPTCMD
        "${EXAMPLES_DIR}/DICOSExamplesRunCommands-data${EXAMPLE_RUN_SUFFIX}")
    
    message(STATUS "Creating '${SCRIPTCMD}'")
    file(WRITE "${SCRIPTCMD}" ${EXAMPLES_RUN_COMMANDS})
    set(SCRIPTCMD)
endfunction(stvn_run_cmd_write)





##############################################################################
# Add rules for building DICOS Examples.
#
# Each example is expected to be fully contained in a single .cpp file. A
# target is created for each .cpp file found. And a mega-target is created to
# build all of them.
#
# Example binaries are placed in the examples/bin folder, because some examples
# expect their datafiles in ../DataFiles.
#


##############################################################################
#
# EXAMPLE_SOURCE_DIR - path to the Example folder
#
function(stvn_add_dicos_examples EXAMPLE_SOURCE_DIR DICOS_LIB_TARGET)
    stvn_run_cmd_init() # Initialize EXAMPLES_RUN_COMMANDS (see above)


    set(ALL_EXAMPLES_TARGETS) # init var for mega-target to build all examples.
    set(EXAMPLE_OUT_DIR "${EXAMPLE_SOURCE_DIR}/bin")


    cmake_print_variables(EXAMPLE_SOURCE_DIR)


    # Find all CPP files
    file(GLOB_RECURSE EXAMPLE_SOURCE_FILES ${EXAMPLE_SOURCE_DIR}/*.cpp)
    foreach(EXAMPLE_PATH IN ITEMS ${EXAMPLE_SOURCE_FILES})

        # Ignore the build/CMakeFiles folder.
        set(HAS_CMAKEFILES)
        string(REGEX MATCH "CMakeFiles" HAS_CMAKEFILES "${EXAMPLE_PATH}")
        if(HAS_CMAKEFILES)
            message(STATUS "Ignoring CMAKEFiles [${EXAMPLE_PATH}]")
            continue()
        endif()

        # Use the example's pathname name to create the example name
        # `../examples/foo/bar/baz/main.cpp` maps to the example named
        # `foo_bar_baz`
        get_filename_component(EXAMPLE_DIRECTORY ${EXAMPLE_PATH} DIRECTORY)
        file(
            RELATIVE_PATH RELATIVE_DIRECTORY
            "${CMAKE_CURRENT_LIST_DIR}" "${EXAMPLE_DIRECTORY}"
        )

        # Convert relative path to executable name and clean any extra information
        string(REGEX REPLACE "[E|e]xamples/" "" EXE_NAME "${RELATIVE_DIRECTORY}")
        string(REGEX REPLACE "/" "_" EXE_NAME "${EXE_NAME}")


        message(STATUS "Adding example: ${EXE_NAME}")
        add_executable(${EXE_NAME} ${EXAMPLE_PATH})

        # set the 32b flag as needed
        if(ENABLE_32_BIT_BUILD)
            message(STATUS
                "32B build requested. Updating compile and link flags.")
            target_compile_options("${EXE_NAME}" PRIVATE -m32)
            target_link_options("${EXE_NAME}" PRIVATE -m32)
        endif()


        target_compile_definitions(
            ${EXE_NAME} PRIVATE -D__BUILD_STANDALONE_EXAMPLES__
        )
        target_link_libraries(${EXE_NAME} PRIVATE ${DICOS_LIB_TARGET})


        # enact the commands for the general and config variants of the property
        set(SUFFIX_LIST "" "_DEBUG" "_RELEASE" "_RELWITHDEBINFO")
        foreach(SUFFIX IN LISTS SUFFIX_LIST)

            # Set the output directory to 'examples/bin'. Some binaries expect
            # testData to be one level above.
            set_target_properties(${EXE_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY${SUFFIX} ${EXAMPLE_OUT_DIR})
        endforeach()


        stvn_run_cmd_add("${EXAMPLE_PATH}" "${EXAMPLE_OUT_DIR}/${EXE_NAME}")

        list(APPEND ALL_EXAMPLES_TARGETS ${EXE_NAME})

    endforeach(EXAMPLE_PATH)


    stvn_run_cmd_write("${EXAMPLE_SOURCE_DIR}")


    # custom target to build just the examples.
    add_custom_target(examples DEPENDS "${ALL_EXAMPLES_TARGETS}")

endfunction(stvn_add_dicos_examples)

