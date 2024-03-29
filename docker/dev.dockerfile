FROM ubuntu:focal as dev

WORKDIR /opt/

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

## install miniconda
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-py38_4.10.3-Linux-x86_64.sh && \
    bash Miniconda3-py38_4.10.3-Linux-x86_64.sh -b -p /opt/miniconda && \
    ln -s /opt/miniconda/etc/profile.d/conda.sh /etc/profile.d/conda.sh && \
    echo ". /opt/miniconda/etc/profile.d/conda.sh" >> ~/.bashrc && \
    echo "conda activate base" >> ~/.bashrc

RUN apt-get install -y curl grep sed dpkg && \
    TINI_VERSION=`curl https://github.com/krallin/tini/releases/latest | grep -o "/v.*\"" | sed 's:^..\(.*\).$:\1:'` && \
    curl -L "https://github.com/krallin/tini/releases/download/v${TINI_VERSION}/tini_${TINI_VERSION}.deb" > tini.deb && \
    dpkg -i tini.deb && \
    rm tini.deb && \
    apt-get clean
  
ENV PATH /opt/miniconda/bin:$PATH

RUN pip3 install jupyter

## install xeus-cling
# RUN conda create -n cling \
#   && conda activate cling \
#   && conda install xeus-cling==0.10.0 -c conda-forge \
#   && conda install boost -c conda-forge

# RUN jupyter kernelspec install /opt/miniconda/envs/cling/share/jupyter/kernels/xcpp17 --sys-prefix

ENTRYPOINT [ "/usr/bin/tini", "--" ]