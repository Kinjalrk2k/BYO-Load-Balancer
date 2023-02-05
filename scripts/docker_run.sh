# in tests/docker

docker run -it --rm --platform linux/arm64/v8 --entrypoint bash -v $(pwd):/etc/opt/byolb:ro kinjalrk2k/byolb:latest