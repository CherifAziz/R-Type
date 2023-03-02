#!/bin/sh

if ! command -v zip > /dev/null; then
  echo "zip n'est pas installé, installation en cours..."
  curl -L https://sourceforge.net/projects/infozip/files/Zip%203.x%20%28latest%29/3.0/zip30.tar.gz/download -o zip.tar.gz
  sudo tar -xzf zip.tar.gz
  cd zip30
  make
  sudo make install
  cd ..
  sudo rm zip.tar.gz
else
  echo "zip déjà installé."
fi

if ! command -v unzip > /dev/null; then
  echo "unzip n'est pas installé, installation en cours..."
  curl -L https://sourceforge.net/projects/infozip/files/UnZip%206.x%20%28Latest%29/UnZip%206.0/unzip60.tar.gz/download -o unzip.tar.gz
  sudo tar -xzf unzip.tar.gz
  cd unzip60
  make
  sudo make install
  cd ..
  sudo rm unzip.tar.gz
else
  echo "unzip déjà installé."
fi

if ! command -v g++ > /dev/null; then
  echo "g++ n'est pas installé, installation en cours..."
  curl -L https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz -o gcc.tar.gz
  sudo tar -xzf gcc.tar.gz
  cd gcc-12.2.0
  ./configure
  make
  make install
  cd ..
  sudo rm gcc.tar.gz
else
  echo "g++ déjà installé."
fi

if ! [ -d "$PWD/vcpkg" ]; then
  echo "vcpkg n'est pas installé, installation en cours..."
  git clone https://github.com/Microsoft/vcpkg.git
  sudo $PWD/vcpkg/bootstrap-vcpkg.sh -disableMetrics
  sudo cp $PWD/vcpkg/vcpkg /usr//bin/vcpkg
  sudo chmod +x /usr/bin/vcpkg
else 
  echo "vcpkg déjà installé."
fi

if ! command -v cmake > /dev/null; then
  echo "cmake n'est pas installé, installation en cours..."
  curl -L https://github.com/Kitware/CMake/releases/download/v3.25.0-rc1/cmake-3.25.0-rc1-linux-x86_64.sh -o cmake-install.sh
  sudo chmod +x cmake-install.sh
  sudo $PWD/cmake-install.sh --skip-license
  sudo rm cmake-install.sh
  echo "cmake installé."
else
  echo "cmake déjà installé."
fi
cd $PWD/vcpkg
sudo git pull
sudo ./bootstrap-vcpkg.sh -disableMetrics
cd ..
# autoconf and libtool pkg-config via apt-get if apt-get is available
if command -v apt-get > /dev/null; then
  echo "apt-get est disponible, installation des dépendances via apt-get."
  apt-get install autoconf libtool pkg-config libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libudev-dev
fi
sudo $PWD/vcpkg/vcpkg install sfml
sudo $PWD/vcpkg/vcpkg install boost-system
sudo $PWD/vcpkg/vcpkg install boost-uuid
sudo $PWD/vcpkg/vcpkg install boost-asio
sudo $PWD/vcpkg/vcpkg install boost-serialization
sudo $PWD/vcpkg/vcpkg upgrade

if sudo [ -e "/root/.vcpkg" ]; then
  echo "/root/.vcpkg existe déjà."
else
  sudo mkdir /root/.vcpkg
fi

if sudo [ -e "/root/.vcpkg/vcpkg.path.txt" ]; then
  echo "/root/.vcpkg/vcpkg.path.txt existe déjà."
else
  sudo touch /root/.vcpkg/vcpkg.path.txt
fi

sudo $PWD/vcpkg/vcpkg integrate install

echo "executing build.sh"
./build.sh