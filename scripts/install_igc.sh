#!/usr/bin/bash

IGC_CORE_URL=https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.15985.7/intel-igc-core_1.0.15985.7_amd64.deb
IGC_URL=https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.15985.7/intel-igc-opencl_1.0.15985.7_amd64.deb
IGC_FILENAME=intel-igc-opencl_1.0.15985.7_amd64.deb
IGC_CORE_FILENAME=intel-igc-core_1.0.15985.7_amd64.deb

cd /opt/

echo "downloading package.."
if [[ -f "${IGC_FILENAME}" ]]; then
    echo "file ${IGC_FILENAME} exists, skip downloading"
else
    wget ${IGC_URL}
fi
echo "downloading package.."
if [[ -f "${IGC_CORE_FILENAME}" ]]; then
    echo "file ${IGC_CORE_FILENAME} exists, skip downloading"
else
    wget ${IGC_CORE_URL}
fi

echo "installing package.."
dpkg -i ${IGC_CORE_FILENAME} ${IGC_FILENAME}