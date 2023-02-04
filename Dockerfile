FROM ubuntu:focal

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install build-essential cmake -y --no-install-recommends

WORKDIR /byolb

COPY . .

RUN ./scripts/clean.sh
RUN cmake --build ./build --target clean
RUN cmake --build ./build --target all

CMD [ "./build/src/lb" ]