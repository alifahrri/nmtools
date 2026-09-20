#!/bin/bash
set -euo pipefail

version="v2.4.8"
DEST=""
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

if [[ -z "${DEST}" ]]; then
    DEST="include/"
fi

wget -4 --tries=5 --timeout=30 --wait=5 -O "${DEST}/doctest.h" "${doctest_url}"