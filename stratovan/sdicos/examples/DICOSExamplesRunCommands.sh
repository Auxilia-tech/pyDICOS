#!/usr/bin/env bash

##############################################################################
### Stratovan Corporation Copyright and Disclaimer Notice:
###
### Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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


# Customer used script. Do not use internal libraries.


##############################################################################
# print_help
#
#     Print the commands help
#
# PARMS:
#     * - Any error messages to display after the help
#
function print_help()
{

    cat<<EOF

NAME
    $me - Run all of the DICOS examples that are non-networking

SYNOPSIS

    $me {-h|-help|--help}
    $me --run

DESCRIPTION

    This script runs all of the non-networking DICOS examples. It uses the
    DICOSExamplesRunCommands-data.sh file to identify which tests to run. The
    data file is generated when 'cmake' is used to generate the example's
    Makefiles.

OPTIONS

    -h, -help, --help
        Print help

    --run
        Cause the script to run. Default is to print help

EOF

    if [ -n "${1}" ]; then
        printf "\nERROR: ${1}\n\n"
    fi
}




##############################################################################
# main
#
function main()
{
    local me="$(basename $0)"
    local mydir="$(cd "$(dirname $0)" && pwd)"


    parse_parms "$@" || return 1


    # Declare an array that is populated from the data file
    # Each entry of the array is the full path to the example executable
    local a_examples=()
    local data="${mydir}/DICOSExamplesRunCommands-data.sh"

    [ ! -e "${data}" ] && {
        printf "\nERROR: Cannot find data file\n"
        printf "       ${data}\n"
        printf "\n"
        printf "The data file is generated as part of the CMake command.\n"
        printf "\n"
        printf "Please cause CMake to run for the examples.\n"
        printf "\n"
        return 1
    }

    source "${data}" || return 1


    # step through each entry in the array and run the tests
    local a_failed=()
    local example
    for example in "${a_examples[@]}"; do
        local exShort="${example%;*}"        # Example is 2nd element from data
        exShort="${exShort##*/[Ee]xamples/}" # Drop the prefix
        exShort="${exShort%/*}"              # Drop the filename

        # run the test and add to failure array on failure.
        run_test "${example}" || a_failed+=("${exShort%;*}")
    done


    if ((${#a_failed[@]})); then
        printf "\n-------------\n"
        printf "The following tests failed:\n\n"
        printf -- "- %s\n" "${a_failed[@]}"
    fi

    # print the heuristics
    printf "\n-------------\n"
    printf "# Total:  %d\n" ${#a_examples[@]}
    printf "# Passed: %d\n" $(( ${#a_examples[@]} - ${#a_failed[@]} ))
    printf "# Failed: %d\n" ${#a_failed[@]}
    printf -- "-------------\n\n"


    # if any tests failed, then this command failed
    return ${#a_failed[@]}
}





##############################################################################
# parse_parms
#
# PARMS
#     * - The command line parameters to parse
#
# RETURNS
#     0 - Run parameter provided, run it
#     1 - Run parameter not provided, stop.
#
function parse_parms()
{
    case "${1,,}" in

        -h|-help|--help)
            print_help
            return 1
            ;;

        --run)
            # Fall through and run!
            ;;

        *)
            print_help "Unexpected parameter '${1}'"
            return 1
            ;;
    esac
}




##############################################################################
# run_test
#
#    Run the specified test.
#
# PARMS
#    $1 - ex_data - Data for the example to run.
#
# RETURNS
#    0  - the test ran and passed
#    !0 - a failure occurred.
function run_test()
{
    local exData="${1}"
    local exPath="${exData%;*}" # first element from ex_data ';' delim
    local exBin="${exData#*;}"  # second element from ex_data ';' delim

    local retvar=0
    local path="${exPath%/*}"       # just the path, drop the file name suffix
    local testCmd="${exBin##*/}"    # just the example exec bin, drop the path
    local testPath="${exBin%/*}"    # just the example exec path, drop the bin

    exPath="${exPath%/*}"              # just the example path
    exPath="${exPath##*/[Ee]xamples/}" # short path based on examples|Examples


    # Enter example directory
    1>/dev/null pushd "${testPath}" || return 1

    printf -- "\n\n----------------------------------------\n"
    printf "EXAMPLE: %s\n" "${exPath##*/examples/}"
    printf -- "----------------------------------------\n"

    # Execute the testCmd printing the execution line
    set -x
    0<&- ./${testCmd} # run with stdin closed, skips prompts
    {
        retvar=$?
        set +x
    } 2> /dev/null

    printf "\nResult: "

    if ((${retvar})); then
        printf " FAILED\n"
    else
        printf " PASSED\n"
    fi


    # Leave example directory
    1>/dev/null popd

    return ${retvar}
}




main "$@"
