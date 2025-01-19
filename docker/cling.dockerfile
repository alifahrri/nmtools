ARG BASE=ubuntu:22.04
FROM ${BASE} AS dev

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

RUN \
    apt update \
    && apt install build-essential git curl -y

WORKDIR /workspace/

COPY scripts/run_cling.sh /run_cling.sh

ENTRYPOINT ["bash", "/run_cling.sh"]