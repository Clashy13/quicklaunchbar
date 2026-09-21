FROM fedora:latest

RUN dnf install -y \
        cmake \
        gcc-c++ \
        make \
        rpm-build \
        rpmdevtools \
        glib2 \
        libglvnd-devel \
        libxkbcommon-devel \
        fontconfig-devel \
        freetype-devel \
        dbus-devel