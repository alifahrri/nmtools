#!/bin/bash
#
# Optional helper for distributed builds (see AGENTS.md "Distributed Builds").
#
# Regenerate ~/.distcc/hosts with a localhost slot cap computed from live free
# memory, instead of a hand-picked static number. This is optional: a static
# hosts file works fine, distcc has no built-in dynamic slots. It works because
# the distcc client re-reads the hosts file for every translation unit, so
# rewriting it (atomically) takes effect for subsequent compiles, even mid-build.
#
# Usage:
#   scripts/distcc_hosts.sh gcc              # 6 GB/job budget, rewrite once
#   scripts/distcc_hosts.sh clang            # 3 GB/job budget
#   scripts/distcc_hosts.sh gcc --watch      # keep refreshing alongside make
#   scripts/distcc_hosts.sh clang -j 3       # override jobs per local slot
#
# Options:
#   -r HOST    distcc server address (default $NMTOOLS_DISTCC_SERVER or 192.168.1.108)
#   -R N       remote slot cap (default 5)
#   -j N       GB of RAM per local job (default: gcc 6, clang 3)
#   -i SECS    refresh interval for --watch (default 5)
#   -o FILE    hosts file to write (default ~/.distcc/hosts)
#
# Note: a slot cap of 0 means UNLIMITED in distcc syntax, so the local cap is
# always clamped to at least 1.

set -e

SERVER="${NMTOOLS_DISTCC_SERVER:-192.168.1.108}"
REMOTE_SLOTS=5
GB_PER_JOB=""
INTERVAL=5
HOSTS_FILE="$HOME/.distcc/hosts"
WATCH=0
COMPILER=""

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -r|--remote)
    SERVER="$2"
    shift
    shift
    ;;
    -R|--remote-slots)
    REMOTE_SLOTS="$2"
    shift
    shift
    ;;
    -j|--gb-per-job)
    GB_PER_JOB="$2"
    shift
    shift
    ;;
    -i|--interval)
    INTERVAL="$2"
    shift
    shift
    ;;
    -o|--output)
    HOSTS_FILE="$2"
    shift
    shift
    ;;
    --watch)
    WATCH=1
    shift
    ;;
    gcc|clang)
    COMPILER="$1"
    shift
    ;;
    *)
    POSITIONAL+=("$1")
    shift
    ;;
esac
done

if [ -z "$COMPILER" ]; then
    echo "usage: $0 gcc|clang [--watch] [-r HOST] [-R N] [-j GB] [-i SECS] [-o FILE]" >&2
    exit 1
fi

# per-compiler default memory budget, matching AGENTS.md adaptive rule
if [ -z "$GB_PER_JOB" ]; then
    if [ "$COMPILER" = "clang" ]; then
        GB_PER_JOB=3
    else
        GB_PER_JOB=6
    fi
fi

write_hosts() {
    # MemAvailable in GiB, rounded down; matches the "available" field of free
    local free_gb local_jobs cores
    free_gb=$(awk '/MemAvailable/{printf "%d", $2/1048576}' /proc/meminfo)
    local_jobs=$(( free_gb / GB_PER_JOB ))
    # clamp: at least 1 (0 would mean unlimited), at most core count
    (( local_jobs < 1 )) && local_jobs=1
    cores=$(nproc)
    (( local_jobs > cores )) && local_jobs=$cores
    printf '%s/%s,lzo localhost/%s,lzo\n' "$SERVER" "$REMOTE_SLOTS" "$local_jobs" > "${HOSTS_FILE}.tmp"
    mv "${HOSTS_FILE}.tmp" "$HOSTS_FILE"
    echo "$COMPILER: ${free_gb}G free / ${GB_PER_JOB}G per job -> localhost/${local_jobs}, ${SERVER}/${REMOTE_SLOTS}" >&2
}

write_hosts

if [ "$WATCH" = "1" ]; then
    echo "watching: refreshing $HOSTS_FILE every ${INTERVAL}s (ctrl-c to stop)" >&2
    while :; do
        sleep "$INTERVAL"
        write_hosts
    done
fi
