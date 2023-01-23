#!/bin/sh

if [ "$EUID" -ne 0 ]; then
  echo "Veuillez lancer ce script en tant que root."
  exit 1
fi

if ! ping -q -c 1 -W 1 google.com > /dev/null; then
  echo "Aucune connexion internet détectée. Vérifiez votre connexion et réessayez."
  exit 1
fi

if ! command -v vcpkg > /dev/null; then
  echo "vcpkg n'est pas installé, installation en cours..."
  git clone https://github.com/Microsoft/vcpkg.git
  $PWD/vcpkg/bootstrap-vcpkg.sh -disableMetrics
  cp $PWD/vcpkg/vcpkg /usr//bin/vcpkg
  chmod +x /usr/bin/vcpkg
else 
  echo "vcpkg déjà installé."
fi

#installer make)

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
$PWD/vcpkg/vcpkg install openal-soft
$PWD/vcpkg/vcpkg install flac
$PWD/vcpkg/vcpkg install sfml
$PWD/vcpkg/vcpkg install boost-asio
$PWD/vcpkg/vcpkg upgrade
if ! [ -e "/root/.vcpkg" ]; then
  mkdir /root/.vcpkg
fi
if ! [ -e "/root/.vcpkg/vcpkg.path.txt" ]; then
  touch /root/.vcpkg/vcpkg.path.txt
fi

$PWD/vcpkg/vcpkg integrate install
rm -rf r-type_client r-type_server build/r-type_client build/r-type_server
cmake -B build -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
mv build/r-type_client r-type_client
mv build/r-type_server r-type_server