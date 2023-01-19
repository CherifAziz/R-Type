#!/bin/sh

if [ "$EUID" -ne 0 ]; then
  echo "Veuillez lancer ce script en tant que root."
  exit 1
fi

# supprime les binaires
rm -rf r-type_client r-type_server build/r-type_client build/r-type_server

# supprime les packets de vcpkg
if command -v vcpkg > /dev/null; then
  echo "Désinstallation des paquets vcpkg en cours..."
  packages=$($PWD/vcpkg/vcpkg list)
  for package in $packages; do
    $PWD/vcpkg/vcpkg remove $package --recurse
  done
  echo "Tous les paquets vcpkg ont été désinstallés."
  $PWD/vcpkg/vcpkg integrate remove
else
  echo "vcpkg n'est pas installé."
  exit 0
fi

# supprime vcpkg
if command -v vcpkg > /dev/null; then
  echo "Désinstallation de vcpkg en cours..."
  rm -rf /usr/bin/vcpkg
  $PWD/vcpkg/vcpkg remove --outdated --purge
  rm -rf ~/.vcpkg
  rm -rf $PWD/vcpkg
  echo "vcpkg désinstallé."
else
  echo "vcpkg n'est pas installé."
fi