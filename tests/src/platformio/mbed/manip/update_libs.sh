#!/usr/bin/bash

# update nmtools libs used for this tests

src=${PWD}

set +e

cd ../../../../../

pio package pack --output nmtools.tar.gz

cp nmtools.tar.gz ${src}
cd ${src}
mkdir -p lib
cd lib
tar -zxvf ../nmtools.tar.gz