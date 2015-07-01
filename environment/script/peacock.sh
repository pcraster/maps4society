#!/usr/bin/env bash
set -e


function print_usage()
{
    echo -e "\
usage: $0 [-h] <download_dir> <prefix> <source>

-h              Show (this) usage information.

download_dir    Directory to store downloaded files.
prefix          Directory to install the resulting files.
source          Directory of Peacock sources."
}


function parse_commandline()
{
    while getopts h option; do
        case $option in
            h) print_usage; exit 0;;
            *) print_usage; exit 2;;
        esac
    done
    shift $((OPTIND-1))

    if [ $# -ne 3 ]; then
        print_usage
        exit 2
    fi

    download_dir=$1
    prefix=$2
    source=$3
}


function build_software()
{
    if [[ $OSTYPE == "cygwin" ]]; then
        options+=("-GUnix Makefiles")
        options+=("-DCMAKE_MAKE_PROGRAM=mingw32-make")
    fi

    options+=("-Dpeacock_download_dir=$download_dir")
    options+=("-Dpeacock_prefix=$prefix")
    options+=("-DCMAKE_VERBOSE_MAKEFILE=OFF")


    # Boost.
    options+=("-Dbuild_boost=true")
    options+=("-Dboost_version=1.57.0")
    options+=("-Dboost_build_boost_filesystem=true")
    options+=("-Dboost_build_boost_python=true")
    options+=("-Dboost_build_boost_system=true")
    options+=("-Dboost_build_boost_test=true")
    options+=("-Dboost_build_boost_timer=true")

    # Fern.
    options+=("-Dbuild_fern=true")
    options+=("-Dfern_git_repository=https://github.com/geoneric/fern.git")
    options+=("-Dfern_git_tag=6b4e7944a65d9c16916bd8e420e6c8dd8c19ac9e")
    options+=("-Dfern_build_fern_algorithm=true")
    options+=("-Dfern_build_fern_documentation=true")
    options+=("-Dfern_build_fern_test=true")

    # GDAL.
    options+=("-Dbuild_gdal=true")
    options+=("-Dgdal_version=2.0.0")
    options+=("-Dgdal_build_ogr=true")
    options+=("-Dgdal_build_python_package=true")


    cmake "${options[@]}" $source
    cmake --build . --target all
}


parse_commandline $*
build_software
