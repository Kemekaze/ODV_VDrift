#docker run -it -e --cpuset-cpus 0,1 --memory 512mb DISPLAY=192.168.1.2:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 vdrift
# Use ODV runtime as a parent image
FROM kemekaze/odv_vdrift_base:latest


# Set the working directory to /app
WORKDIR /app

ENV HOME /app
#ENV USR vDODV
ENV USRHOME = /root
ADD ./app /app

#RUN useradd --home-dir $HOME $USR \
# && chown -R $USR:$USR $HOME

#USER $USR

#Compile VDrift
#RUN cd /app/lib/vdrift && scons prefix=/app/lib/vdrift datadir=data && cd /app

RUN mkdir $USRHOME/.vdrift/ \
 && mv $HOME/VDrift.config $USRHOME/.vdrift/.

#RUN mkdir -p /opt/od \
# && chown $USER:$USER /opt/od \
# && cd OpenDaVINCI && mkdir build \
# && cd build \
# && cmake -D CMAKE_INSTALL_PREFIX=/opt/od .. \
# && make

RUN mkdir build \
 && cd build \
 && cmake -D CMAKE_BUILD_TYPE=Release .. \
 && make vDODV



CMD ["./lib/vdrift/build/vdrift"]
