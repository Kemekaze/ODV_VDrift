#Hello there
###Install and run docker enviroment
```console
docker build -t kemekaze/odv_vdrift_base:latest -f Dockerfile.base .
docker build -t kemekaze/vdodv .
docker run -it -e ISPLAY=<YOUR IP ADDRESS>:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 kemekaze/vdodv
```
