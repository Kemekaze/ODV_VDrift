
##Install
```console
docker build -t kemekaze/vdodv .
```

## RUN docker Windows
``` console
docker run -it -e DISPLAY=<YOUR IP ADDRESS>:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 kemekaze/vdodv

```
## RUN docker Ubuntu
``` console
xhost +local:docker
docker run -it --rm -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY kemekaze/vdodv

```
