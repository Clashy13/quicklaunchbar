FROM archlinux:latest

RUN pacman -Syu --noconfirm && pacman -S --needed --noconfirm \
        base-devel \ 
        cmake \ 
        ninja \
        glib2 \
        libglvnd \
        libxkbcommon \
        fontconfig \
        freetype2 \
        dbus