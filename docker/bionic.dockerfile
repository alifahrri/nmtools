FROM ubuntu:bionic as dev

WORKDIR /opt/

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

RUN apt update && apt install software-properties-common -y && add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt update && apt install -y \
    gcc-9 \
    g++-9 \
    build-essential  \
    git \
    wget \
    python3-minimal \
    python3-pip \
    tar \
    curl \
    clang-10 \
    libboost-dev
RUN pip3 install -U gcovr

RUN wget http://www.cmake.org/files/v3.13/cmake-3.13.3.tar.gz \
  && tar xf cmake-3.13.3.tar.gz \
  && cd cmake-3.13.3 \
  && ./configure \
  && make install -j`nproc`

# install the tooks i wish to use
RUN apt-get update && \
  apt-get install -y sudo \
  curl \
  git-core \
  gnupg \
  locales \
  zsh \
  wget \
  fonts-powerline \
  # set up locale
  && locale-gen en_US.UTF-8

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog

# generate locale for agnoster
RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && /usr/sbin/locale-gen

ENV TERM xterm

# Set the default shell to bash rather than sh
ENV SHELL /bin/zsh

 # run the installation script  
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

ADD .devcontainer/.zshrc $HOME

## install nanobench
COPY scripts/install_nanobench.sh install_nanobench.sh
RUN bash install_nanobench.sh

## install doctest
COPY scripts/install_doctest.sh install_doctest.sh
RUN bash install_doctest.sh --dest /usr/local/include

FROM dev AS build

WORKDIR /workspace/nmtools