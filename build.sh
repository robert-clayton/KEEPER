#!/bin/bash

$SCRIPTROOT="$(dirname $0)"
$OUTPUTPATH="$SCRIPTROOT/dist/"
$OUTPUTNAME="KEEPER"
$SDLINCLUDEPATH="/usr/include/" # or whatever
$SDLLIBPATH="/usr/lib" # or whatever

$SOURCEPRIVATE=("/wherever"/*.cpp "/wherever/ecs/"*.cpp)
$SOURCEPUBLIC=("$SCRIPTROOT/src" "$SCRIPTROOT/src/ecs")

# Ensure output path exists
mkdir -p $OUTPUTPATH

# Construct g++ command
$COMMAND="g++ -g "
for i in "${SOURCEPRIVATE[@]}" # bash arrays are ass
do
  $COMMAND="$COMMAND'$i' " # sprinkling single quotes into $COMMAND around paths in case they have spaces
done
$COMMAND="$COMMAND-o '$OUTPUTPATH$OUTPUTNAME' "
for i in "${SOURCEPUBLIC[@]}"
do
  $COMMAND="$COMMAND-I'$i' "
done
$COMMAND="$COMMAND-I'$SDLINCLUDEPATH' -L'$SDLLIBPATH' -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -mwindows"

echo $COMMAND
eval $COMMAND
