#docker run -it -e --cpuset-cpus 0,1 --memory 512mb DISPLAY=192.168.1.2:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 vdrift
# Use ODV runtime as a parent image
FROM ubuntu:xenial
#FROM seresearch/opendlv-on-opendlv-core-on-opendavinci-on-base:latest

# Set the working directory to /app
WORKDIR /app
RUN apt-get update \
 && apt-get install -y wget \
 && wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | apt-key add - \
 && echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ xenial main" | tee -a /etc/apt/sources.list \
 && apt-get install software-properties-common -y \
 && add-apt-repository ppa:roblib/ppa -y \
 && add-apt-repository ppa:chrberger/libcluon \
 && apt-get update \
 && apt-get install -y \
    wget \
    git \
    tar \
    ant \
    build-essential \
    cmake \
    make \
    g++ \
    scons \
    libsdl2-dev \
    libsdl2-image-dev \
    libbullet-dev \
    libvorbis-dev \
    libcurl4-gnutls-dev \
    default-jre \
    default-jdk \
    libopencv-dev \
    python-opencv \
    libcluon \
    opendavinci-* \
#    opendavinci-lib \
#    opendavinci-odtools \
#    opendavinci-odsupercomponent \
#    opendavinci-oddatastructuregenerator \
#    opendavinci-odcandatastructuregenerator \
 && apt-get autoremove -y
 ADD ./config /config

 #FIX FOR SDL2 LIB
 RUN rm /usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake && mv /config/sdl2-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2/.

 ADD ./opendlv.core/ /opendlv.core
 RUN mkdir /opendlv.core/build \
   && cd /opendlv.core/build \
   && cmake -D OPENDAVINCI_DIR=/opt/od4 -D CMAKE_INSTALL_PREFIX=/opt/opendlv.core .. \
   && make

ENV HOME /app
ENV USRHOME = /root

ADD ./app /app
RUN mkdir build \
 && cd build \
 && cmake -D CMAKE_BUILD_TYPE=debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON .. \
 && make vDODV


ADD ./model/opendlv.lynx/ /model
RUN mkdir /model/build \
 && cd /model/build \
 && cmake \
    -D CMAKE_BUILD_TYPE=debug \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    #-D CXXTEST_INCLUDE_DIR=/opt/opendlv.lynx.sources/thirdparty/cxxtest \
    -D OPENDAVINCI_DIR=/opt/od4 \
    #-D PACKAGING_ENABLED=$PACKAGING_ENABLED \
    -D ODVDOPENDLVSTANDARDMESSAGESET_DIR=/opt/opendlv.core \
    -D CMAKE_INSTALL_PREFIX=/opt/opendlv.lynx .. \
 && make

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/opendlv.lynx/lib

ADD ./tests /tests
RUN mkdir /tests/build
# && mkdir /tests/build/input \
# && cd /tests/build/input \
# && cmake -D CMAKE_BUILD_TYPE=debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ../../input \
# && make vDODV-test-input

 RUN mkdir /tests/build/path \
  && cd /tests/build/path \
  && cmake -D CMAKE_BUILD_TYPE=debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ../../path \
  && make vDODV-test-path

#CMD ["./build/vDODV"]
#CMD ["./lib/vdrift/build/vdrift"]
