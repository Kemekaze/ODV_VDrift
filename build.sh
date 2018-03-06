$BASE_NAME=odv_vdrift_base
$NAME=odv_vdrift
docker build -t ${BASE_NAME} -f Dockerfile.base
docker build -t ${NAME} -f Dockerfile
