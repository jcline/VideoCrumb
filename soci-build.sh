#!/bin/bash

mkdir soci/bin
cp soci/CMakeCache.txt soci/bin
cd soci/bin
cmake ../soci/src && make -j 8

