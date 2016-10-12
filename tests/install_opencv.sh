#!/usr/bin/env bash

# install opencv on travis build server
# uses cache to speed up install if generated build files are available

# install opencv dependencies
sudo apt-get -qq install build-essential
sudo apt-get -qq install libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

mkdir -p opencv-cache # make cache directory if not already available

if [ "$(ls -A opencv-cache)" ]; then
    echo "installing pre-build packages"
    find opencv-cache -maxdepth 1 -type f -name "*.deb" -exec sudo dpkg -i "{}" \;
    sudo apt-get -f install -y # fix dependencies
else
    echo "no packages available, building opencv"
    git clone https://github.com/opencv/opencv.git
    cd opencv
    git checkout 2.4.13
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DCPACK_BINARY_DEB=ON ..
    make -j 2 # travis has 2 cores, so let's use them
    sudo make install
    cpack . # generate packages
    find . -maxdepth 1 -type f -name "*.deb" -exec cp "{}" ../../opencv-cache \;
fi;
