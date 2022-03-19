FROM ubuntu:focal

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

COPY requirements-apt.txt requirements.txt
RUN apt update && xargs apt install -y < requirements.txt
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 10000 && \
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 10000 && \
	update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-9 10000
RUN pip3 install -U gcovr

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
  libboost-iostreams-dev \
  libboost-program-options-dev \
  libboost-system-dev \
  libboost-filesystem-dev \
  libunwind-dev \
  && locale-gen en_US.UTF-8


# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog

ARG USERNAME
ENV USER_NAME=${USERNAME}
ENV USER_PASSWORD password

# add a user (--disabled-password: the user won't be able to use the account until the password is set)
RUN adduser --quiet --disabled-password --shell /bin/zsh --home /home/$USER_NAME --gecos "User" $USER_NAME
# update the password
RUN echo "${USER_NAME}:${USER_PASSWORD}" | chpasswd && usermod -aG sudo $USER_NAME
RUN echo $USER_NAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER_NAME && chmod 0440 /etc/sudoers.d/$USER_NAME

# set home
ENV HOME /home/$USER_NAME

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

## install nanobench
COPY scripts/install_nanobench.sh install_nanobench.sh
RUN bash install_nanobench.sh

## install doctest
COPY scripts/install_doctest.sh install_doctest.sh
RUN bash install_doctest.sh

ENTRYPOINT []

# TODO: optional install deps for gui