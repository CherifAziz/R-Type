FROM ubuntu:latest

RUN apt-get update -y

RUN apt-get install -y sudo curl git make gcc g++ zip unzip nano

RUN useradd -m -s /bin/bash -G sudo ubuntu

RUN echo "ubuntu:1234" | chpasswd

USER ubuntu

WORKDIR /home/ubuntu/r-type

COPY . .

ENTRYPOINT ["tail", "-f", "/dev/null"]