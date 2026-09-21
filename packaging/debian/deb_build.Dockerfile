FROM debian:latest

RUN apt-get update && apt-get install -y \
        build-essential \
        cmake \
        ninja-build \
        libglib2.0-0 \
        libgl-dev \
        libxkbcommon-dev \
        libegl-dev \
        libfontconfig-dev \
        libfreetype-dev \
        libdbus-1-dev