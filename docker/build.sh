#!/bin/bash 

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -i|--img)
    IMG="$2"
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

if [ -z "$IMG" -a "$IMG" != " " ]; then
        IMG="numeric_tools"
fi

## assuming this script is located in root/scripts & Dockerfile in root/docker
docker build -t $IMG -f ${DIR}/dockerfile ${DIR}/..