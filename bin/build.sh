#!/bin/bash

BUILD_DIR=$(pwd)/build
SRC_DIR=$(pwd)/src
ASSETS_DIR=$(pwd)/res
OBJ_DIR=$BUILD_DIR/obj
DIST_DIR=$(pwd)/dist

rm -rf $BUILD_DIR
rm -rf $DIST_DIR
mkdir -p $BUILD_DIR
mkdir -p $DIST_DIR

cp -r $ASSETS_DIR $BUILD_DIR/res
cp -r $SRC_DIR $BUILD_DIR/src

# pushd thirdparty/emsdk
#     echo "Configuring Emscripten environment variables"
#     source ./emsdk_env.sh
# popd

pushd $BUILD_DIR
    OBJ_FILES=""
    for FILE in $(find src -type f -name "*.cpp"); do
        OBJ_FILE=$OBJ_DIR/$(dirname $FILE)/$(basename $FILE .cpp).o
        mkdir -p $(dirname $OBJ_FILE)
        emcc -O2 $FILE -c -o $OBJ_FILE -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' \
            -sUSE_PTHREADS=1 -pthread
        OBJ_FILES+="$OBJ_FILE "
    done

    emcc -sWASM=1 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS='["png"]' \
        -sLLD_REPORT_UNDEFINED -sALLOW_MEMORY_GROWTH \
        $OBJ_FILES -o $DIST_DIR/KEEPER.js --preload-file res || exit 1
popd

cp res/favicon.ico $DIST_DIR/favicon.ico
cp template.html $DIST_DIR/index.html
