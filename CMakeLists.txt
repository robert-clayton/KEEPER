cmake_minimum_required(VERSION 3.4.1)
project(KEEPER)
# We are using C++ 17 and will make use of C++ exceptions.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

set(MAIN_SOURCE_DIR "src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)


file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.h)
file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)

# The 'KEEPER' executable is the output target for our Emscripten application and is why we end up with 'KEEPER.js' in the output folder. Note that it will use the C++ source code from the shared 'main' folder through the collated sources.
add_executable(
    KEEPER
    ${CPP_HEADERS}
    ${CPP_SOURCES}
)

# These properties specify what kind of Emscripten build to perform and are assigned to our 'KEEPER' executable target.
set_target_properties(
    KEEPER
    PROPERTIES
    LINK_FLAGS
    "-O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' -s USE_WEBGL2=1 -s ASSERTIONS=1 -sSINGLE_FILE"
)
