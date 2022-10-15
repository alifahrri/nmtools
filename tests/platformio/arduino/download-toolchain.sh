#!/usr/bin/bash

wget https://github.com/alifahrri/toolchain-avr-gcc/releases/download/v9.2.0/toolchain-avr-gcc.tar.bz2

if [ -d "manip" ]; then
    ln -s toolchain-avr-gcc.tar.bz2 manip/toolchain-avr-gcc.tar.bz2
fi
if [ -d "ufuncs" ]; then
    ln -s toolchain-avr-gcc.tar.bz2 ufuncs/toolchain-avr-gcc.tar.bz2
fi
if [ -d "meta" ]; then
    ln -s toolchain-avr-gcc.tar.bz2 meta/toolchain-avr-gcc.tar.bz2
fi
if [ -d "utl" ]; then
    ln -s toolchain-avr-gcc.tar.bz2 utl/toolchain-avr-gcc.tar.bz2
fi
if [ -d "constexpr" ]; then
    ln -s toolchain-avr-gcc.tar.bz2 constexpr/toolchain-avr-gcc.tar.bz2
fi