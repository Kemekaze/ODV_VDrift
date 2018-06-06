## Requirments
.env file containing 
```console
CID=[1-254]
WIN_DISPLAY=[YOUR IP ADDRESS]:0.0 (Windows only)
```
## Install
```console
docker build -t kemekaze/vdodv .
```
## Get Current Version
```console
docker pull kemekaze/vdodv
```
## RUN (Windows)
``` console
docker-compose up
```
## RUN (Ubuntu)
``` console
xhost +local:docker
OR xhost +
docker-compose up -f docker-compose-ubuntu.yml
```
