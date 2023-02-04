#!/bin/sh

if [ "$EUID" -ne 0 ]; then
  echo "Veuillez lancer ce script en tant que root."
  exit 1
fi

rm -rf r-type_server r-type_client tcpclient tcpserver udpserver