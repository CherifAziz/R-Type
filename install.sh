#!/bin/sh

if [ "$EUID" -ne 0 ]; then
  echo "Veuillez lancer ce script en tant que root."
  exit 1
fi

if ! ping -q -c 1 -W 1 google.com > /dev/null; then
  echo "Aucune connexion internet détectée. Vérifiez votre connexion et réessayez."
  exit 1
fi

if [ -d "$PWD/vcpkg"]; then
  echo "vcpkg n'est pas installé, installation en cours..."
  git clone https://github.com/Microsoft/vcpkg.git
  $PWD/vcpkg/bootstrap-vcpkg.sh -disableMetrics
  cp $PWD/vcpkg/vcpkg /usr//bin/vcpkg
  chmod +x /usr/bin/vcpkg
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
  chmod +x cmake-install.sh
  $PWD/cmake-install.sh --skip-license
  rm cmake-install.sh
  echo "cmake installé."
else
  echo "cmake déjà installé."
fi

cd $PWD/vcpkg
git pull
./bootstrap-vcpkg.sh -disableMetrics
cd ..
$PWD/vcpkg/vcpkg install sfml
$PWD/vcpkg/vcpkg install boost-system
$PWD/vcpkg/vcpkg install boost-serialization
$PWD/vcpkg/vcpkg upgrade
if ! [ -e "/root/.vcpkg" ]; then
  mkdir /root/.vcpkg
fi
if ! [ -e "/root/.vcpkg/vcpkg.path.txt" ]; then
  touch /root/.vcpkg/vcpkg.path.txt
fi

$PWD/vcpkg/vcpkg integrate install
rm -rf build
cmake -B build -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --config Release
mv build/bin/* $PWD/