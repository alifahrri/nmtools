#!/bin/bash

CWD=$pwd
version="v2.4.8"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
doctest_url="https://raw.githubusercontent.com/onqtam/doctest/${version}/doctest/doctest.h"

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -d|--dest)
    DEST="$2"
    shift # past argument
    shift # past value
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

if [ -z "$DEST" -a "$DEST" != " " ]; then
    DEST="include/"
fi

wget --no-check-certificate -O $DEST/doctest.h $doctest_url