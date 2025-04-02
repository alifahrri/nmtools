FROM ubuntu:24.04 AS base

RUN apt update && apt install -y \
    build-essential \
    cmake \
    git git-core \
    python3 python3-dev python3-pip \
    curl gnupg locales \
    zsh wget fonts-powerline \
    && locale-gen en_US.UTF-8

WORKDIR /opt/

RUN git clone --single-branch -b llvmorg-19.1.7 https://github.com/llvm/llvm-project.git \
    && cd llvm-project \
    && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DLLVM_ENABLE_PROJECTS=clang -G "Unix Makefiles" ../llvm \
    && cmake --build . --target clang clang-repl -j `nproc`

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && /usr/sbin/locale-gen

ENV TERM xterm

# Set the default shell to bash rather than sh
ENV SHELL /bin/zsh

 # run the installation script  
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

RUN cd $HOME && curl -fsSLO https://raw.githubusercontent.com/romkatv/dotfiles-public/master/.purepower

ADD .devcontainer/.zshrc $HOME

WORKDIR /workspace/