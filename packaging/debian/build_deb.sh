# #!/bin/bash

set -e

echo "Building Debian package..."
echo "Source: $PWD"

sudo docker run --rm -it \
  -v "$PWD:/src" \
  -v "$HOME/Qt/6.8.3/gcc_64:/opt/qt" \
  -w /src \
  deb_builder \
  bash -c '
    set -e

    echo "==> Cleaning Debian build..."
    rm -rf /src/build-debian

    echo "==> Configuring..."
    cmake -S /src -B /src/build-debian -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/opt/qt -DQUICKLAUNCHBAR_QT_DEPLOY=ON

    echo "==> Building..."
    cmake --build /src/build-debian

    echo "==> Creating DEB..."
    cd /src/build-debian
    cpack -G DEB
  '
