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

# In order to find the Emscripten build tools, we need to configure some environment variables so they are available during the build. The required environment variables are initialized by sourcing the 'emsdk_env.sh' that ships with the Emscripten SDK.
pushd thirdparty/emsdk
    echo "Configuring Emscripten environment variables"
    source ./emsdk_env.sh
popd

pushd $BUILD_DIR
    OBJ_FILES=""
    for FILE in $(find src -type f -name "*.cpp"); do
        OBJ_FILE=$OBJ_DIR/$(dirname $FILE)/$(basename $FILE .cpp).o
        mkdir -p $(dirname $OBJ_FILE)
        emcc -O2 $FILE -c -o $OBJ_FILE -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'
        OBJ_FILES+="../$FILE "
    done


    # # Start the actual build
    # echo "Building project ..."
    # # make || exit 1
    emcc -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' \
        $OBJ_FILES -o $DIST_DIR/KEEPER.html --preload-file res || exit 1
popd

# # Copy template to out folder
# cp template.html out/index.html

cp res/favicon.ico $DIST_DIR/favicon.ico

emrun $DIST_DIR/KEEPER.html


# CC = emcc
# all: main.c engine.c engine.h sprite.c sprite.h decal.c decal.h \
#  	actor.c actor.h apple_actor.c apple_actor.h snake_actor.c snake_actor.h \
# 	background_actor.c background_actor.h input_processor.c input_processor.h
# 	$(CC) main.c engine.c sprite.c decal.c actor.c apple_actor.c snake_actor.c background_actor.c input_processor.c -O2 -s TOTAL_MEMORY=67108864 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -o snake.js
