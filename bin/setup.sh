#!/bin/bash

pushd thirdparty/emsdk
    git pull
    ./emsdk install latest
    ./emsdk activate latest
popd