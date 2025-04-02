# Or your preferred base image
ARG ubuntu_base=24.10
FROM ubuntu:${ubuntu_base} AS base

RUN apt-get update && apt-get install -y --no-install-recommends build-essential wget iperf3 git \
  gcc make python3 python3-dev python3-setuptools autoconf autotools-dev automake pkg-config libpopt-dev clang

RUN apt install -y --reinstall ca-certificates

# Expose the distcc port (3632 by default)
EXPOSE 3632
EXPOSE 5201

WORKDIR /opt/

RUN git clone https://github.com/distcc/distcc.git \
  && cd distcc \
  && ./autogen.sh && ./configure \
  && make -j `nproc` \
  && make install \
  && update-distcc-symlinks

WORKDIR /workspace

# Start distccd.  Use --no-detach and --log-stderr for proper logging.
# Set ALLOWEDNETS appropriately!

ARG jobs=32
ENV JOBS=${jobs}

RUN echo -e \
    "# Defaults for distcc initscript\n"\
    "# sourced by /etc/init.d/distcc\n"\
    "#\n"\
    "# Should distccd be started on boot?\n"\
    "STARTDISTCC=\"true\"\n"\
    "#\n"\
    "# Which networks/hosts should be allowed?\n"\
    "# *** Change this in the running container or mount a config if needed ***\n"\
    "ALLOWEDNETS=\"127.0.0.1 192.168.1.0/24\"\n"\
    "#\n"\
    "# Which interface address should distccd listen on?\n"\
    "LISTENER=\"0.0.0.0\"\n"\
    "#\n"\
    "# Nice level (higher means lower priority)\n"\
    "NICE=\"10\"\n"\
    "#\n"\
    "# Max concurrent jobs (use ARG for build-time setting)\n"\
    "JOBS=\"${jobs}\"\n"\
    "#\n"\
    "# Enable Zeroconf?\n"\
    "ZEROCONF=\"false\"\n"\
    "#\n"\
    "# Default port\n"\
    "PORT=\"3632\"" > /etc/default/distcc

ENTRYPOINT ["distccd", "--daemon", "--no-detach", "--log-stderr"]

# Or, if you want to use /etc/default/distcc (recommended):
# COPY distcc.default /etc/default/distcc
# CMD ["/usr/sbin/service", "distcc", "start"]