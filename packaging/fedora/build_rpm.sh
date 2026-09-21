#!/bin/bash

set -e

echo "Building Fedora package..."
echo "Source: $PWD"

sudo docker run --rm -it \
  -v "$PWD:/src" \
  -v "$HOME/Qt/6.8.3/gcc_64:/opt/qt" \
  -w /src \
  rpm_builder \
  bash -c '
    set -e

    echo "==> Cleaning Fedora build..."
    rm -rf /src/build-fedora

    echo "==> Configuring..."
    cmake -S /src -B /src/build-fedora -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/opt/qt -DQUICKLAUNCHBAR_QT_DEPLOY=OFF -DCMAKE_INSTALL_PREFIX=/opt/quicklaunchbar

    echo "==> Building..."
    cmake --build /src/build-fedora

    echo "==> Creating RPM..."
    cd /src/build-fedora
    cpack -G RPM
  '
