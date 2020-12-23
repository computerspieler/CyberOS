#!/bin/bash

export BINUTILS_VERSION=2.34
export GCC_VERSION=9.3.0
export PREFIX=$PWD/toolchain
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir tmp
mkdir toolchain
cd tmp

echo Download tarballs
if [ ! -f binutils-$BINUTILS_VERSION.tar.gz ]; then
	wget https://gcc.gnu.org/pub/binutils/releases/binutils-$BINUTILS_VERSION.tar.gz
	rm -rfd binutils
fi
if [ ! -f gcc-$GCC_VERSION.tar.gz ]; then
	wget https://gcc.gnu.org/pub/gcc/releases/gcc-9.3.0/gcc-$GCC_VERSION.tar.gz
	rm -rfd gcc
fi

echo Extract tarballs
if [ ! -f binutils ]; then
	tar xvf binutils-$BINUTILS_VERSION.tar.gz
	mv binutils-$BINUTILS_VERSION binutils
fi
if [ ! -f gcc ]; then
	tar xvf gcc-$GCC_VERSION.tar.gz
	mv gcc-$GCC_VERSION gcc
fi

echo Create build directories
mkdir build-binutils build-gcc
mkdir $TOOLCHAIN_DIR

echo Build binutils
cd build-binutils
../binutils/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

echo Build GCC
cd build-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..

cd ..