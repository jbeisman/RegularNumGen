#!/bin/bash

if [ -d "build" ]; then 
  rm -rf "build"
fi
if [ -d "install" ]; then 
  rm -rf "install"
fi
ORIGIN_DIR=${pwd}
mkdir "install" ; mkdir "build" ; cd "build"
cmake ..\
    -DBUILD_SHARED_LIBS:BOOL=true \
    -DCMAKE_INSTALL_PREFIX:FILEPATH=`pwd`/../install \
    -DCMAKE_BUILD_TYPE:STRING=Release
make -j6 VERBOSE=1
make install
cd $ORIGIN_DIR
