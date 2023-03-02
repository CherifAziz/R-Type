FROM ubuntu:latest

RUN apt-get update -y

RUN apt-get install -y sudo curl git make gcc g++ zip unzip nano

RUN useradd -m -s /bin/bash -G sudo -p 1234 ubuntu

USER ubuntu

WORKDIR /home/ubuntu/r-type

COPY . .
