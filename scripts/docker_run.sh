# in tests/docker

docker run -it --rm --platform linux/arm64/v8 --entrypoint bash -p 2000:2209 -v $(pwd):/etc/opt/byolb:ro kinjalrk2k/byolb:latest