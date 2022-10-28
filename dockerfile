FROM ubuntu:latest

RUN apt-get update
RUN apt install sudo
RUN apt-get update
RUN apt-get install -y g++ bash doxygen clang cmake valgrind python3-pip sudo iproute2
RUN sudo apt-get update
RUN sudo apt update && sudo apt install -y cmake
RUN sudo apt-get install -y xorg-dev libudev-dev 

RUN pip3 install conan \
    && conan profile new default --detect

COPY . /usr/src/docker_comp

WORKDIR /usr/src/docker_comp

CMD [ "./docker_exec_script.sh" ]