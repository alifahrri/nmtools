#!/bin/bash 

docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --rm --name numeric_tools -it numeric_tools bash scripts/debug_tests.sh