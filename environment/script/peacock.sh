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

function copy_headers()
{
    # TODO: other architectures?
    target_dir=$prefix/linux/linux/gcc-4/x86_64/include/pcrtree2/
    source_dir=./pcraster-head-Release-prefix/src/pcraster-head-Release/source

    mkdir -p $target_dir

    cp \
        $source_dir/pcraster_model_engine/calc_spatial.h \
        $source_dir/pcraster_model_engine/calc_nonspatial.h \
        $source_dir/pcraster_model_engine/calc_cr.h \
        $source_dir/pcraster_model_engine/calc_vs.h \
        $source_dir/pcraster_model_engine/calc_types.h \
        $source_dir/pcraster_model_engine/calc_field.h \
        $source_dir/pcraster_model_engine/calc_datavalue.h \
        $source_dir/pcraster_model_engine/calc_ovs.h \
        $source_dir/pcraster_python/Globals.h \
        $source_dir/pcrgeo/geo_rasterspace.h \
        $source_dir/pcrgeo/geo_def.h \
        $source_dir/pcrgeo/geo_rasterdim.h \
        $source_dir/pcrgeo/geo_cellloc.h \
        $source_dir/pcrcom/com_mvop.h \
        $source_dir/pcrcom/com_csfcell.h \
        $source_dir/app/appargs.h \
        $source_dir/include/pcrdatatype.h \
        $source_dir/include/environ.h \
        $source_dir/include/stddefx.h \
        $source_dir/include/pcrdll.h \
        $source_dir/include/typedef.h \
        $source_dir/include/debug.h \
        $source_dir/include/dev_Compiler.h \
        $source_dir/pcraster_dal/dal_Client.h \
        $source_dir/pcraster_dal/dal_Configure.h \
        $target_dir
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
    options+=("-Dboost_build_boost_date_time=true")
    options+=("-Dboost_build_boost_filesystem=true")
    options+=("-Dboost_build_boost_math=true")
    options+=("-Dboost_build_boost_program_options=true")
    options+=("-Dboost_build_boost_python=true")
    options+=("-Dboost_build_boost_regex=true")
    options+=("-Dboost_build_boost_system=true")
    options+=("-Dboost_build_boost_test=true")
    options+=("-Dboost_build_boost_timer=true")

    # Fern.
    options+=("-Dbuild_fern=true")
    options+=("-Dfern_git_repository=https://github.com/geoneric/fern.git")
    # options+=("-Dfern_git_tag=d90ececdcaf365e608009aaa3c4c7a30027e0249")
    options+=("-Dfern_git_tag=47cd1676bcbef67b04fe3cb0fd310366764571ad")
    options+=("-Dfern_build_fern_algorithm=true")
    options+=("-Dfern_build_fern_documentation=true")
    options+=("-Dfern_build_fern_test=true")

    # GDAL.
    options+=("-Dbuild_gdal=true")
    options+=("-Dgdal_version=1.11.1")
    options+=("-Dgdal_build_ogr=true")
    options+=("-Dgdal_build_python_package=true")

    # PCRaster raster format.
    options+=("-Dbuild_pcraster_raster_format=true")
    options+=("-Dpcraster_raster_format_version=1.3.1")

    # Qt
    options+=("-Dbuild_qt=true")
    options+=("-Dqt_version=4.8.6")

    # Qwt
    options+=("-Dbuild_qwt=true")
    options+=("-Dqwt_version=6.0.2")

    # PCRaster.
    options+=("-Dbuild_pcraster=true")
    options+=(
        "-Dpcraster_git_repository=https://github.com/pcraster/pcraster.git")
    options+=("-Dpcraster_git_tag=f1b54c6b5d6b0006543b05978bb0b4abc5bf5ad1")
    # CMake Error at source/modflow/documentation/cmake_install.cmake:36 (file):
    #   file INSTALL cannot find
    #     "/home/shared1/builder/tmp/peacock/pcraster-head-Release-prefix/src/pcraster-head-Release-build/source/modflow/documentation/_build/html".
    # options+=("-Dpcraster_git_tag=9d73caee948454aac8f923d1013c7ee4e0afd539")
    options+=("-Dpcraster_build_pcraster_documentation=true")
    options+=("-Dpcraster_build_pcraster_test=true")


    cmake "${options[@]}" $source
    cmake --build . --target all

    copy_headers
}


parse_commandline $*
build_software
