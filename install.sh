#!/bin/sh

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
  cd /usr/local
  sudo curl -L https://github.com/Kitware/CMake/releases/download/v3.25.0-rc1/cmake-3.25.0-rc1-linux-x86_64.sh -o cmake-install.sh
  sudo chmod +x cmake-install.sh
  sudo ./cmake-install.sh --skip-license
  sudo rm /usr/local/cmake-install.sh
  echo "cmake installé."
  cd -
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
  sudo apt-get install -y autoconf libtool pkg-config libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libudev-dev libasound2-dev
fi
if command -v apt > /dev/null; then
  echo "apt est disponible, installation des dépendances via apt."
  sudo apt install -y autoconf libtool pkg-config libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libudev-dev libasound2-dev
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