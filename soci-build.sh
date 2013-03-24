#!/bin/bash

mkdir soci/bin
cp soci/CMakeCache.txt soci/bin
cd soci/bin
cmake -DCMAKE_INSTALL_PREFIX:PATH=`pwd`/../lib ../soci/src && make all install -j 8

