#!/bin/sh

if [ -d "$PWD/build/Release" ]; then
  rm -rf $PWD/build/Release
  echo "Release folder deleted"
fi

if [ -e "$PWD/cfg/config.hpp" ]; then
  rm $PWD/cfg/config.hpp
  echo "config.hpp deleted"
fi