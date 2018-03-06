# Use ODV runtime as a parent image
FROM ubuntu:xenial

# Variables
#ARG VDRIFT_URL=https://jaist.dl.sourceforge.net/project/vdrift/vdrift/vdrift-2014-10-20/vdrift-2014-10-20.tar.bz2
ARG VDRIFT_URL=http://192.168.0.237:8000/vdrift-2014-10-20.tar.bz2
ARG VDRIFT_FILE=vdrift-2014-10-20.tar.bz2


# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD . /app


# Install base packages
RUN cd /app \
 && apt-get update -y \
 #&& apt-get upgrade -y \
 && apt-get install -y \
    wget \
    git \
    tar


#Install VDrift
RUN apt-get update -y \
 && apt-get install software-properties-common -y \
 && add-apt-repository ppa:roblib/ppa -y \
 && add-apt-repository ppa:zoogie/sdl2-snapshots -y \
 && apt-get install -y \
    g++ \
    scons \
    libsdl2-dev \
    libsdl2-image-dev \
    libbullet-dev \
    libvorbis-dev \
    libcurl4-gnutls-dev \
 && wget ${VDRIFT_URL} \
 && tar -jxf ${VDRIFT_FILE} \
 && cd ./vdrift \
 && scons

#install OpenDaVINCHI needed?
RUN wget -O - -q \
    http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key \
    | apt-key add - \
 && echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ xenial main" \
    | tee -a /etc/apt/sources.list \
 && apt-get update -y \
 && apt-get install -y \
    opendavinci-lib \
    opendavinci-odtools \
    opendavinci-odsupercomponent


# Make port 80 available to the world outside this container
#EXPOSE 80

# Define environment variable
#ENV NAME World
#if behind proxy
#ENV http_proxy host:port
#ENV https_proxy host:port

# Run app.py when the container launches
CMD ["bash", "init.sh"]
