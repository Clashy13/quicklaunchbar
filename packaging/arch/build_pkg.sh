#!/bin/bash

set -e

echo "Building Arch package..."
echo "Source: $PWD"

sudo docker run --rm -it \
  -v "$PWD:/src" \
  -v "$HOME/Qt/6.8.3/gcc_64:/opt/qt" \
  -w /src/packaging/arch \
  pkg_builder \
  bash -c '
    set -e

    echo "==> Cleaning Arch build..."
    rm -rf /src/build-arch

    useradd -m builder
    echo "builder ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/builder
    chmod 440 /etc/sudoers.d/builder
    chown -R builder:builder /src

    echo "==> Building package..."
    runuser -u builder -- env BUILDDIR=/src/build-arch PKGDEST=/src/build-arch SRCPKGDEST=/src/build-arch SRCDEST=/src/build-arch makepkg -sf --noconfirm
  '

  
