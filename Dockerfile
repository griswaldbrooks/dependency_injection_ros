FROM ros:melodic
MAINTAINER Griswald Brooks griswald.brooks@gmail.com

# Prevent the interactive wizards from stopping the build
ARG DEBIAN_FRONTEND=noninteractive

ARG USER
ARG UID
ARG GID

# Get the basics
RUN apt update -y &&         \
    apt install -y           \
             build-essential \
             cmake           \
             git             \
             lsb-core        \
             python3         \
             python3-pip     \
             sudo            \
             wget

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
RUN wget http://packages.ros.org/ros.key -O - | apt-key add -

RUN apt update -y &&         \
    apt install -y           \
             python-catkin-tools

RUN /bin/bash -c '. /opt/ros/melodic/setup.bash'

RUN addgroup --gid $GID $USER
RUN adduser --disabled-password --gecos '' --uid $UID --gid $GID $USER
USER $USER
