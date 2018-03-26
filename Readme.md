#Hello there
###Install and run docker enviroment
```console
docker build -t kemekaze/odv_vdrift_base:latest -f Dockerfile.base .
docker build -t vdrift .
docker run -it -e --cpuset-cpus 0,1 --memory 512mb DISPLAY=<YOUR IP ADDRESS>:0.0 -e SDL_VIDEO_X11_VISUALID=0x022 vdrift
```
