#!/bin/bash 

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

## assuming this script is located in root/scripts & Dockerfile in root/docker
docker build -t numeric_tools -f ${DIR}/Dockerfile ${DIR}/..