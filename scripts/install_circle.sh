#!/bin/bash

CIRCLE_VERSION=build_160

FILE=/opt/${CIRCLE_VERSION}.tgz
if [[ -f "$FILE" ]]; then
    echo "$FILE exists. skipping download"
else
    wget -P /opt https://www.circle-lang.org/linux/${CIRCLE_VERSION}.tgz
fi

tar xvf /opt/${CIRCLE_VERSION}.tgz -C /usr/bin

chmod +x /usr/bin/circle