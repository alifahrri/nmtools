from nvidia/cuda:12.1.1-devel-ubuntu20.04 as dev

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

run apt update && apt install -y \
    build-essential cmake clang \
    curl git-core gnupg locales \
    zsh wget fonts-powerline \
    && locale-gen en_US.UTF-8

ENV DEBIAN_FRONTEND=dialog

# generate locale for agnoster
RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && /usr/sbin/locale-gen

ENV TERM xterm

# Set the default shell to bash rather than sh
ENV SHELL /bin/zsh

 # run the installation script  
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

# install powerlevel10k
RUN git clone https://github.com/romkatv/powerlevel10k.git ~/.oh-my-zsh/custom/themes/powerlevel10k

RUN cd $HOME && curl -fsSLO https://raw.githubusercontent.com/romkatv/dotfiles-public/master/.purepower

ADD .devcontainer/.zshrc $HOME

## install doctest
COPY scripts/install_doctest.sh install_doctest.sh
RUN bash install_doctest.sh

from dev as build

WORKDIR /workspace/nmtools

COPY cmake cmake
COPY scripts scripts
COPY include include
COPY tests tests
COPY CMakeLists.txt CMakeLists.txt
COPY nmtools.pc.in nmtools.pc.in
COPY nmtoolsConfig.cmake.in nmtoolsConfig.cmake.in

RUN mkdir -p build && cd build \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/cuda-clang.cmake \
        -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_CUDA_TESTS=ON \
        ../ \
    && make -j2 VERBOSE=1
