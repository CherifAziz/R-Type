#!/bin/sh

if [ -d "$PWD/build" ]; then
  rm -rf $PWD/build
fi

if [ -d "$PWD/rtype-1.0-Linux" ]; then
  rm -rf $PWD/rtype-1.0-Linux
fi