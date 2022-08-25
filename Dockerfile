FROM debian:latest
MAINTAINER NULL@grayfox.dev

RUN apt update  -y && \
    apt upgrade -y && \
    apt install -y cmake git gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential python3
RUN echo 'alias ..="cd .."' >> ~/.bashrc
RUN echo 'alias ll="ls --color=auto -lah"' >> ~/.bashrc
RUN echo 'alias ls="ls --color=auto"' >> ~/.bashrc

