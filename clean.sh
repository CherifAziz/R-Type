#!/bin/sh

if [ -d "$PWD/build" ]; then
  rm -rf $PWD/build
fi

if [ -e "$PWD/rtype-1.0-Linux.rpm" ]; then
  rm -rf $PWD/rtype-1.0-Linux.rpm
fi