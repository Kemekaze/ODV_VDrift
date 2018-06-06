## Requirments
.env file containing 
CID=[1-254]

## Install
```console
docker build -t kemekaze/vdodv .
```
## Current version
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
if that does not work use 
xhost +
docker-compose up -f docker-compose-ubuntu.yml

```
