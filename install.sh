#!/bin/sh

if [ -d "$PWD/build" ]; then
  rm -rf $PWD/build
fi

if [ -e "$PWD/rtype" ]; then
  rm -rf $PWD/rtype
fi

if [ -e "$PWD/rtype-1.0.zip" ]; then
  rm -rf $PWD/rtype-1.0.zip
fi

if [ -e "$PWD/rtype-1.0-Source.zip" ]; then
  rm -rf $PWD/rtype-1.0-Source.zip
fi

if ! command -v ping > /dev/null; then
  echo "ping n'est pas installé, installation en cours..."
  sudo yum update -y
  sudo yum install -y iputils
else
  echo "ping déjà installé."
fi

if ! ping -q -c 1 -W 1 google.com > /dev/null; then
  echo "Aucune connexion internet détectée. Vérifiez votre connexion et réessayez."
  exit 1
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

if ! command -v make > /dev/null; then
  echo "make n'est pas installé, installation en cours..."
else
  echo "make déjà installé."
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
sudo $PWD/vcpkg/vcpkg install sfml
sudo $PWD/vcpkg/vcpkg install boost-system
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
cmake -B build -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MODULE_PATH=$PWD/build/
cmake --build ./build --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP
cpack --config CPackSourceConfig.cmake -G ZIP
cd ..
mv build/*.zip $PWD