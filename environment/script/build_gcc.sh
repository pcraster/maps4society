#!/usr/bin/env bash
set -e

# This gcc version can be used if the version currently installed is getting
# too old. Since compilers are updated to support c++11/c++14 features, there
# is a big difference between compiler versions.

# Hardwiring build and install roots. Update if necessary.
build_root=$HOME/tmp
install_root=~/tmp/opt

wget="wget --no-check-certificate"
gnu_make="make"
nr_jobs=4


build_gcc() {
    local gcc_version=4.9.2
    local gcc_base=gcc-$gcc_version
    local gcc_prefix=$install_root/$gcc_base

    cd $build_root

    if [ ! -e $gcc_base.tar.bz2 ]; then
        $wget ftp://ftp.nluug.nl/mirror/languages/gcc/releases/$gcc_base/$gcc_base.tar.bz2
    fi

    local gmp_version=4.3.2 # 5.0.4
    local gmp_base=gmp-$gmp_version
    if [ ! -e $gmp_base.tar.bz2 ]; then
        $wget ftp://ftp.gmplib.org/pub/$gmp_base/$gmp_base.tar.bz2
    fi

    local mpfr_version=2.4.2 # 3.1.0
    local mpfr_base=mpfr-$mpfr_version
    if [ ! -e $mpfr_base.tar.bz2 ]; then
        $wget http://www.mpfr.org/$mpfr_base/$mpfr_base.tar.bz2
    fi

    local mpc_version=0.8.1 # 0.9
    local mpc_base=mpc-$mpc_version
    if [ ! -e $mpc_base.tar.gz ]; then
        $wget http://www.multiprecision.org/mpc/download/$mpc_base.tar.gz
    fi

    rm -fr $gcc_base
    tar jxf $gcc_base.tar.bz2
    cd $gcc_base
    tar jxf ../$gmp_base.tar.bz2; mv $gmp_base gmp
    tar jxf ../$mpfr_base.tar.bz2; mv $mpfr_base mpfr
    tar zxf ../$mpc_base.tar.gz; mv $mpc_base mpc

    ./configure --prefix=$gcc_prefix --enable-languages="c,c++,fortran" \
        --disable-multilib
    # --host=x86_64-linux-gnu --build=x86_64-linux-gnu --target=x86_64-linux-gnu
    $gnu_make -j $nr_jobs
    $gnu_make install
}


build_gcc
