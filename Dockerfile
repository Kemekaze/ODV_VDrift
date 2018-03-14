#docker run -it -e --cpuset-cpus 0,1 --memory 512mb DISPLAY=192.168.1.2:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 vdrift
# Use ODV runtime as a parent image
FROM kemekaze/odv_vdrift_base:latest


# Set the working directory to /app
WORKDIR /app

ENV HOME /app
ENV USR vdrift

# Copy the app directory contents into the container at /app
ADD ./app /app

RUN useradd --home-dir $HOME $USR \
	&& chown -R $USR:$USR $HOME

USER vdrift

#Compile VDrift
RUN cd /app/vdrift && scons prefix=/app/vdrift datadir=data && cd /app

RUN mkdir $HOME/.vdrift/ \
 && mv $HOME/VDrift.config $HOME/.vdrift/.
RUN ls -la /app/.vdrift




CMD ["bash", "main.sh"]
