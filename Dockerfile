#docker run -it -e --cpuset-cpus 0,1 --memory 512mb DISPLAY=192.168.1.2:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 vdrift
# Use ODV runtime as a parent image
FROM ubuntu:xenial


# Set the working directory to /app
WORKDIR /app
RUN apt-get update -y \
 && apt-get install software-properties-common -y \
 && add-apt-repository ppa:roblib/ppa -y \
 && add-apt-repository ppa:chrberger/libcluon \
 && apt-get update -y \
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
    libcluon \
 && apt-get autoremove -y



ENV HOME /app
ENV USRHOME = /root
ADD ./app /app
#FIX FOR SDL2 LIB
RUN rm /usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake && mv ./config/sdl2-config.cmake /usr/lib/x86_64-linux-gnu/cmake/SDL2/.


#Compile VDrift
#RUN cd /app/lib/vdrift && scons prefix=/app/lib/vdrift datadir=data verbose=1 && cd /app

#RUN mkdir $USRHOME/.vdrift/ && mv $HOME/VDrift.config $USRHOME/.vdrift/.


RUN mkdir build \
 && cd build \
 && cmake -D CMAKE_BUILD_TYPE=debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON .. \
 && make vDODV

ADD ./tests /tests
RUN mkdir /tests/build \
 && cd /tests/build \
 && cmake -D CMAKE_BUILD_TYPE=debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ../input \
 && make vDODV-test-input



#CMD ["./build/vDODV"]
#CMD ["./lib/vdrift/build/vdrift"]
