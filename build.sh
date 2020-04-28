source ~/emsdk/emsdk_env.sh
emcc -s FORCE_FILESYSTEM=1 -s EXPORTED_FUNCTIONS='["_pic"]' -std=c++11  -o ./node/img.js ./imageco/index.cpp